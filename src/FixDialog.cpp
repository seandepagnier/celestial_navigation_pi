/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Celestial Navigation Support
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2016 by Sean D'Epagnier                                 *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *
 */

#include <wx/wx.h>
#include "CelestialNavigationDialog.h"
#include "FixDialog.h"

#include "ocpn_plugin.h"
#include "Sight.h"

#include <vector>
using namespace std;

FixDialog::FixDialog(wxWindow *parent) :
    FixDialogBase(parent),
    m_fixlat(NAN),
    m_fixlon(NAN),
    m_fixerror(NAN)
{
}

double dist(wxRealPoint a, wxRealPoint b)
{
    double x = a.x - b.x;
    double y = a.y - b.y;
   if(y > 180)
        y -= 360;
    if(y < -180)
        y += 360;

    return x*x + y*y;
}

/* find smallest circle that fits set of points */
double MinCircle(double &x, double &y, std::vector<wxRealPoint> points)
{
    if(points.size() < 2)
        return NAN;

    double maxdist = 0;
    /* find farthest points */
    wxRealPoint maxa, maxb;
    for(unsigned int i = 1; i<points.size(); i++) {
        for(unsigned int j = 0; j < i;  j++) {
            wxRealPoint a = points[i], b = points[j];
            double d = dist(a, b);
            if(d > maxdist)
                maxa = a, maxb = b, maxdist = d;
        }
    }

    /* now we should expand to include any points not bounded */

    x = (maxa.x + maxb.x) / 2;
    y = (maxa.y + maxb.y) / 2;
    return maxdist / 4;
}

double MinCirclePoints(double &mincx, double &mincy,
                       std::list <std::list<wxRealPoint> > &all_points,
                       std::vector<wxRealPoint> &points)
{
    if(all_points.size() == 0)
        return MinCircle(mincx, mincy, points);

    std::list<wxRealPoint> cpoints = all_points.front();
    all_points.pop_front();

    int s =  points.size();
    points.push_back(wxRealPoint());
    double mind = INFINITY;
    for(std::list<wxRealPoint>::iterator it = cpoints.begin();
        it != cpoints.end(); it++) {
        points[s] = *it;

        double cx, cy, cd;
        cd = MinCirclePoints(cx, cy, all_points, points);
        if(cd < mind) {
            mind = cd;
            mincx = cx;
            mincy = cy;
        }
    }
    points.pop_back();
    all_points.push_front(cpoints);

    if(isinf(mind))
        return NAN;
    return mind;
}

/* this algorithm works for any size, but c++ is sadly not supporting
   pointers to variable size arrays like gcc does for c */
int matrix_invert3(double a[3][3])
{
    int n = 3;

   int i, j, k;
   // main cycle for columns of A matrix
   for ( k = 0; k < n; k++ ) {

      // make current element 1
      double aa = a[k][k];
      if ( aa == 0.0f )
         return 0;

      double aainv = 1.0f/aa;

      a[k][k] = 1.0f;
      for ( i = 0; i < n; i++ )
         a[k][i] *= aainv;

      // make all rows zero
      for ( j = 0; j < n; j++ ) {
         if ( j == k )
            continue;

         aa = a[j][k];
         a[j][k] = 0.0f;

         for ( i = 0; i < n; i++ )
            a[j][i] -= a[k][i]*aa;
      }
   }
   return 1;
}

double deg2rad(double degrees)
{
  return M_PI * degrees / 180.0;
}

double rad2deg(double radians)
{
  return 180.0 * radians / M_PI;
}

extern "C" int geomag_calc(double latitude, double longitude, double alt,
                           int day, int month, double year,
                           double results[14]);

void FixDialog::Update(int clock_offset, bool warnings)
{
    std::list<std::vector<double> > J;
    std::list<double> R;

    double X[3]; /* result */

    double initiallat = m_sInitialLatitude->GetValue(), initiallon = m_sInitialLongitude->GetValue();
    X[0] = cos(deg2rad(initiallat))*cos(deg2rad(initiallon));
    X[1] = cos(deg2rad(initiallat))*sin(deg2rad(initiallon));
    X[2] = sin(deg2rad(initiallat));

    m_clock_offset = clock_offset;
    int iterations = 0;
    wxListCtrl *lSights = ((CelestialNavigationDialog*)GetParent())->m_lSights;
again:
    for(int i = 0; i<lSights->GetItemCount(); i++) {
        Sight *s = (Sight*)wxUIntToPtr(lSights->GetItemData(i));
        if(!s->IsVisible() || s->m_Type != Sight::ALTITUDE)
            continue;
    
        if(s->m_ShiftNm) {
            static bool seenwarning = false;
            if(!seenwarning && warnings) {
                wxMessageDialog mdlg(this, _("Shifted sights are not used to compute a fix, \
determine fix visually instead.\n"), wxString(_("Fix Position"), wxID_OK | wxICON_WARNING));
                mdlg.ShowModal();
                seenwarning = true;
            }
            continue;
        }

        double lat, lon;
        s->BodyLocation(s->m_DateTime + wxTimeSpan::Seconds(clock_offset), &lat, &lon, 0, 0);

        /* take vector from body location of length equal to
           normalized measurement (so the plane this vector
           describes intersects the unit sphere along the positions
           the sight is valid) */
        std::vector<double> v;
        double x = cos(deg2rad(lat))*cos(deg2rad(lon));
        double y = cos(deg2rad(lat))*sin(deg2rad(lon));
        double z = sin(deg2rad(lat));

        double sm = sin(deg2rad(s->m_ObservedAltitude));
        double cm = cos(deg2rad(s->m_ObservedAltitude));

        double d = NAN;

        switch(m_cbFixAlgorithm->GetSelection()) {
        case 0: /* plane */
        plane:
            /* plane */
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            d = sm - (X[0]*x + X[1]*y + X[2]*z);
            break;
        case 1: /* sphere */
        {
            double xc = X[0] - x, yc = X[1] - y, zc = X[2] - z;
            v.push_back(2*xc);
            v.push_back(2*yc);
            v.push_back(2*zc);
            d = cm*cm + (1-sm)*(1-sm) - xc*xc - yc*yc - zc*zc;
        } break;
        case 2: /* cone */
        {
            double t2 = X[0]*X[0] + X[1]*X[1] + X[2]*X[2], t = sqrt(t2);
            if(t < .1) goto plane;
            v.push_back(x);
            v.push_back(y);
            v.push_back(z);
            d = sm - (X[0]*x + X[1]*y + X[2]*z)/t;
        } break;
        case 3: /* cone 2 */
        {
            double t2 = X[0]*X[0] + X[1]*X[1] + X[2]*X[2], t = sqrt(t2);
            if(t < .1) goto plane;
            v.push_back(x/t - x*X[0]*X[0]/(t*t2));
            v.push_back(y/t - y*X[1]*X[1]/(t*t2));
            v.push_back(z/t - z*X[2]*X[2]/(t*t2));
            d = sm - (X[0]*x + X[1]*y + X[2]*z)/t;
        } break;
        }

        J.push_back(v);
        R.push_back(d);
    }

    /* fit to unit sphere (keep results on surface of earth) */
    {
        std::vector<double> v;
        v.push_back(2*X[0]);
        v.push_back(2*X[1]);
        v.push_back(2*X[2]);
        J.push_back(v);
        double d = 1 - X[0]*X[0] - X[1]*X[1] - X[2]*X[2];
        R.push_back(d);
    }

    /* now use least squares to find the point where all these planes
       intersect, it is our fix */

    /* least squares all the great_circles to find fix
       JtJ^-1 * JtRt */

    double S[3][3]; /* S = Jt*J */
    std::list<std::vector<double> >::iterator it;
    std::list<double >::iterator it2;
    for(int i=0; i<3; i++)
        for(int j=0; j<3; j++) {
            S[i][j] = 0;
            for (it = J.begin(); it != J.end(); it++)
                S[i][j] += (*it)[i]*(*it)[j];
        }

    double N[3]; /* N = (JtRt)t  R is all 1's since this is linear */
    for(int i=0; i<3; i++) {
        N[i] = 0;
        for (it = J.begin(), it2 = R.begin(); it != J.end(); it++, it2++)
            N[i] += (*it)[i]*(*it2);
    }

    /* invert S */
    double d, err;
    if(!matrix_invert3(S))
        goto fail;

    for(int i = 0; i<3; i++)
        for(int j = 0; j<3; j++)
            X[i] += S[i][j]*N[j];
    
    d = sqrt(X[0]*X[0] + X[1]*X[1] + X[2]*X[2]);
    err = fabs(d-1);
    
    /* 20 is overkill to converge. there are better ways to determine the number
       of iterations, but this routine runs so fast it doesn't matter */
    if(iterations++ < 20) {
        if(err > 100) /* we are diverging */
            goto fail;
        J.clear();
        R.clear();
        goto again;
    }
    
    /* normalize */
    X[0] /= d, X[1] /= d, X[2] /= d;
    
    m_fixlat = rad2deg(asin(X[2]));
    m_fixlon = rad2deg(atan2(X[1], X[0]));
    
    if(err <= .1) {   
        m_fixerror = 0;
        for (it2 = R.begin(); it2 != R.end(); it2++)
            m_fixerror += (*it2)*(*it2);
        m_fixerror = sqrt(m_fixerror);
    
        double lat = trunc(m_fixlat);
        double latmin = 60*(m_fixlat - lat);
        double lon = trunc(m_fixlon);
        double lonmin = 60*(m_fixlon - lon);
    
        m_stLatitude->SetLabel(wxString::Format(_T("%.0f %.1f'"), lat, latmin));
        m_stLongitude->SetLabel(wxString::Format(_T("%.0f %.1f'"), lon, lonmin));
        m_stFixError->SetLabel(wxString::Format(_T("%.3g"), m_fixerror));
        m_bGo->Enable();
    } else {
fail:
        m_fixerror = NAN;
        m_stLatitude->SetLabel(_("   N/A   "));
        m_stLongitude->SetLabel(_("   N/A   "));
        m_stFixError->SetLabel(_("   N/A   "));
        m_bGo->Disable();
    }

    RequestRefresh( GetParent()->GetParent() );
}

void FixDialog::OnGo( wxCommandEvent& event )
{
    double scale = 1e-5/m_fixerror;
    if(scale < 1e-4)
        scale = 1e-4;

    if(scale > 1e-3)
        scale = 1e-3;

    JumpToPosition(m_fixlat, m_fixlon, scale);
}
