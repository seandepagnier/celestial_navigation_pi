/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Celestial Navigation Support
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2013 by Sean D'Epagnier                                 *
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


// For compilers that support precompilation, includes "wx/wx.h".
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/imaglist.h>

#include <iostream>

#include "../../../include/ocpn_plugin.h"

#include "Sight.h"
#include "SightDialog.h"
#include "CelestialNavigationDialog.h"

/* XPM */
static const char *eye[]={
"20 20 7 1",
". c none",
"# c #000000",
"a c #333333",
"b c #666666",
"c c #999999",
"d c #cccccc",
"e c #ffffff",
"....................",
"....................",
"....................",
"....................",
".......######.......",
".....#aabccb#a#.....",
"....#deeeddeebcb#...",
"..#aeeeec##aceaec#..",
".#bedaeee####dbcec#.",
"#aeedbdabc###bcceea#",
".#bedad######abcec#.",
"..#be#d######dadb#..",
"...#abac####abba#...",
".....##acbaca##.....",
".......######.......",
"....................",
"....................",
"....................",
"....................",
"...................."};

enum { rmVISIBLE = 0, rmTYPE, rmBODY, rmTIME, rmMEASUREMENT, rmCOLOR };// RMColumns;

// sort callback. Sort by body.
#if wxCHECK_VERSION(2, 9, 0)
int wxCALLBACK SortSights(long item1, long item2, wxIntPtr list)
#else
int wxCALLBACK SortSights(long item1, long item2, long list)
#endif            
{
    wxListCtrl *lc = (wxListCtrl*)list;

    wxListItem it1, it2;
    it1.SetId(lc->FindItem(-1, item1));
    it1.SetColumn(1);
    
    it2.SetId(lc->FindItem(-1, item2));
    it2.SetColumn(1);
    
    lc->GetItem(it1);
    lc->GetItem(it2);
    
    return it1.GetText().Cmp(it2.GetText());
}

CelestialNavigationDialog::CelestialNavigationDialog(wxWindow *parent)
    : CelestialNavigationDialogBase(parent)
{
    // create a image list for the list with just the eye icon
    wxImageList *imglist = new wxImageList(20, 20, true, 1);
    imglist->Add(wxBitmap(eye));
    m_lSights->AssignImageList(imglist, wxIMAGE_LIST_SMALL);

    m_lSights->InsertColumn(rmVISIBLE, wxT(""));
    m_lSights->SetColumnWidth(0, 28);

    m_lSights->InsertColumn(rmTYPE, _("Type"));
    m_lSights->InsertColumn(rmBODY, _("Body"));
    m_lSights->InsertColumn(rmTIME, _("Time (UTC)"));
    m_lSights->InsertColumn(rmMEASUREMENT, _("Measurement"));
    m_lSights->InsertColumn(rmCOLOR, _("Color"));
    
    UpdateSights();
}

CelestialNavigationDialog::~CelestialNavigationDialog()
{
}

void CelestialNavigationDialog::UpdateSights()
{
    // if an item was selected, make it selected again if it still exist
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    long selected_id = -1;
    if (selected_index > -1)
        selected_id = m_lSights->GetItemData(selected_index);

    // Delete existing items
    m_lSights->DeleteAllItems();

    // then add sights to the listctrl
    SightList::iterator it;
    wxListItem item;
    int index = 0;

    for (it = m_SightList.begin(); it != m_SightList.end(); ++it, ++index)
    {
        item.SetId(index);
        item.SetImage((*it)->IsVisible() ? 0 : -1);
        item.SetData(index);
        
        long idx = m_lSights->InsertItem(item);
        m_lSights->SetItemImage(index, (*it)->IsVisible() ? 0 : -1);
        m_lSights->SetItem(idx, rmTYPE, (*it)->m_Type ? _("Azimuth") : _("Altitude"));
        m_lSights->SetItem(idx, rmBODY, (*it)->m_Body);
        wxDateTime dt = (*it)->m_DateTime.ToUTC();
        m_lSights->SetItem(idx, rmTIME, dt.FormatISODate() + _T(" ") + dt.FormatISOTime());
        m_lSights->SetItem(idx, rmMEASUREMENT, wxString::Format(_T("%.4f"), (*it)->m_Measurement));
        m_lSights->SetItem(idx, rmCOLOR, (*it)->m_ColourName);
    }
    
    m_lSights->SetColumnWidth(rmTYPE, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmBODY, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmTIME, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmCOLOR, wxLIST_AUTOSIZE);
    
    if(m_lSights->GetColumnWidth(1) < 20)
        m_lSights->SetColumnWidth(1, 50);

    if(m_lSights->GetColumnWidth(2) < 20)
        m_lSights->SetColumnWidth(2, 50);
    
    m_lSights->SortItems(SortSights, (long)m_lSights);
    
    // restore selection if possible
    // NOTE this will select a different item, if one is deleted
    // (the next sight will get that index).
    if (selected_id > -1)
    {
        selected_index = m_lSights->FindItem(-1, selected_id);
        m_lSights->SetItemState(selected_index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    
    UpdateButtons();
    UpdateFix();
}

void CelestialNavigationDialog::UpdateButtons()
{
    // enable/disable buttons
    long selected_index_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    bool enable = !(selected_index_index < 0);
    
    m_bEditSight->Enable(enable);
    m_bDeleteSight->Enable(enable);
    m_bDeleteAllSights->Enable(m_SightList.GetCount() > 0);
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
#include <vector>

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

void CelestialNavigationDialog::UpdateFix()
{
    std::list<std::vector<double> > J;
    std::list<double> R;

    double X[3]; /* result */

    double initiallat = m_sInitialLatitude->GetValue(), initiallon = m_sInitialLongitude->GetValue();
    X[0] = cos(deg2rad(initiallat))*cos(deg2rad(initiallon));
    X[1] = cos(deg2rad(initiallat))*sin(deg2rad(initiallon));
    X[2] = sin(deg2rad(initiallat));

    int iterations = 0;
again:

    for (SightList::iterator it = m_SightList.begin(); it != m_SightList.end(); it++) {
        Sight *s = *it;
        if(!s->IsVisible() || s->m_Type != Sight::ALTITUDE)
            continue;
    
        if(s->m_ShiftNm) {
            static bool seenwarning = false;
            if(!seenwarning) {
                wxMessageDialog mdlg(this, _("Shifted sights are not used to compute a fix, \
determine fix visually instead.\n"), wxString(_("Fix Position"), wxID_OK | wxICON_WARNING));
                mdlg.ShowModal();
                seenwarning = true;
            }
            continue;
        }

        double lat, lon;
        s->BodyLocation(s->m_DateTime, &lat, &lon, 0, 0);

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

        double d;

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

    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnNew(wxCommandEvent &event)
{
    wxDateTime now = wxDateTime::Now();
    now.MakeUTC();

    Sight s(Sight::ALTITUDE, _("Sun"), Sight::LOWER, now, 1, 0, .25);
    SightDialog dialog(GetParent(), s);
      
    if( dialog.ShowModal() == wxID_OK ) {
        Sight *ns = new Sight(s);

        dialog.RecomputeSight();
        ns->RebuildPolygons();
        m_SightList.Append(ns);
        UpdateSights();
        RequestRefresh( GetParent() );
    }
}

void CelestialNavigationDialog::OnEdit(wxCommandEvent &event)
{
    // Manipulate selected_index sight/track
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;

    Sight *psight = m_SightList.Item(m_lSights->GetItemData(selected_index))->GetData();
    Sight originalsight = *psight; /* in case of cancel */
    
    SightDialog dialog(GetParent(), *psight);
    
    if( dialog.ShowModal() == wxID_OK ) {
        psight->RebuildPolygons();
        UpdateSights();
    } else
        *psight = originalsight;
    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnDelete(wxCommandEvent &event)
{
    // Delete selected_index sight/track
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;
    
    Sight *psight_to_delete = m_SightList.Item(m_lSights->GetItemData(selected_index))->GetData();
    m_SightList.DeleteObject(psight_to_delete);

    UpdateSights();
    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnDeleteAll(wxCommandEvent &event)
{
    wxMessageDialog mdlg(this, _("Are you sure you want to delete all sights?"),
                         _("Celestial Navigation"), wxYES_NO);
    if(mdlg.ShowModal() == wxID_YES) {
        m_SightList.Clear();
    
        UpdateSights();
        RequestRefresh( GetParent() );
    }
}

void CelestialNavigationDialog::OnInformation( wxCommandEvent& event )
{
    wxString infolocation = *GetpSharedDataLocation()
        + _T("plugins/celestial_navigation/data/Celestial_Navigation_Information.html");
#if 0
    InformationDialog dlg(this);
    if(dlg.m_htmlInformation->LoadFile(infolocation))
        dlg.ShowModal();
    else {
        wxMessageDialog mdlg(this, _("Failed to load file:\n") + infolocation,
                             wxString(_("Celestial Navigation"), wxOK | wxICON_ERROR));
        mdlg.ShowModal();
    }
#endif
    wxLaunchDefaultBrowser(_T("file://") + infolocation);
}

void CelestialNavigationDialog::OnGoFix( wxCommandEvent& event )
{
    double scale = 1e-5/m_fixerror;
    if(scale < 1e-4)
        scale = 1e-4;

    if(scale > 1e-3)
        scale = 1e-3;

    JumpToPosition(m_fixlat, m_fixlon, scale);
}

void CelestialNavigationDialog::OnSightListLeftDown(wxMouseEvent &event)
{
    wxPoint pos = event.GetPosition();
    int flags = 0;
    long clicked_index = m_lSights->HitTest(pos, flags);
    
    //    Clicking Visibility column?
    if (clicked_index > -1 && event.GetX() < m_lSights->GetColumnWidth(0))
    {
        // Process the clicked item
        Sight *sight = m_SightList.Item(m_lSights->GetItemData(clicked_index))->GetData();
        sight->SetVisible(!sight->IsVisible());
        m_lSights->SetItemImage(clicked_index, sight->IsVisible() ? 0 : -1);

        UpdateFix();
        RequestRefresh( GetParent() );
    }

    // Allow wx to process...
    event.Skip();
}

void CelestialNavigationDialog::OnSightSelected(wxListEvent &event)
{
    UpdateButtons();
}
