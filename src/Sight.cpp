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

#include "wx/wxprec.h"

#ifndef  WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

#include <wx/tokenzr.h>
#include <wx/sstream.h>
#include <wx/image.h>
#include <wx/filename.h>
#include <wx/graphics.h>


#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <wx/listimpl.cpp>


#include "../../../include/ocpn_plugin.h"

#include "Sight.h"


WX_DEFINE_LIST ( SightList );
WX_DEFINE_LIST ( wxRealPointList );

void resolve_heading(double &heading)
{
   while(heading < -180)
      heading += 360;
   while(heading >= 180)
      heading -= 360;   
}

void resolve_heading_positive(double &heading)
{
   while(heading < 0)
      heading += 360;
   while(heading >= 360)
      heading -= 360;   
}

//-----------------------------------------------------------------------------
//          Sight Implementation
//-----------------------------------------------------------------------------

double Sight::default_eye_height=2;
double Sight::default_temperature=25;
double Sight::default_pressure=1000;

int Sight::s_lastsightcolor = 0;

Sight::Sight(Type type, wxString body, BodyLimb bodylimb, wxDateTime datetime,
             double timecertainty, double measurement, double measurementcertainty)
    : m_bVisible(true), m_Type(type), m_Body(body), m_BodyLimb(bodylimb),
     m_DateTime(datetime), m_TimeCertainty(timecertainty),
     m_Measurement(measurement), m_MeasurementCertainty(measurementcertainty),
      m_EyeHeight(default_eye_height),
      m_Temperature(default_temperature),
      m_Pressure(default_pressure),
      m_ShiftNm(0), m_ShiftBearing(0), m_bMagneticShiftBearing(0),
      m_bMagneticNorth(false)
{
    const wxColour sightcolors[] = {
        wxColour(_("MEDIUM VIOLET RED")), wxColour(_("MIDNIGHT BLUE")), wxColour(_("ORANGE")),
        wxColour(_("TAN")), wxColour(_("THISTLE")), wxColour(_("TURQUOISE")), wxColour(_("VIOLET")),
        wxColour(_("ORANGE RED")), wxColour(_("ORCHID")), wxColour(_("PALE GREEN")), wxColour(_("PINK")),
        wxColour(_("PLUM")), wxColour(_("PURPLE")), wxColour(_("RED")), wxColour(_("SALMON")),
        wxColour(_("SEA GREEN")), wxColour(_("SIENNA")), wxColour(_("SKY BLUE")),
        wxColour(_("SLATE BLUE")), wxColour(_("SPRING GREEN")), wxColour(_("STEEL BLUE")),
        wxColour(_("BROWN")), wxColour(_("BLUE")), wxColour(_("BLUE VIOLET")),
        wxColour(_("AQUAMARINE")), wxColour(_("CADET BLUE")), wxColour(_("CORAL")),
        wxColour(_("CORNFLOWER BLUE")), wxColour(_("FOREST GREEN")), wxColour(_("GOLD")),
        wxColour(_("GOLDENROD")), wxColour(_("GREY")), wxColour(_("GREEN YELLOW")),
        wxColour(_("INDIAN RED")), wxColour(_("LIGHT BLUE")), wxColour(_("LIGHT STEEL BLUE")),
        wxColour(_("LIME GREEN")), wxColour(_("MAGENTA")), wxColour(_("MAROON")),
        wxColour(_("MEDIUM AQUAMARINE")), wxColour(_("MEDIUM BLUE")), wxColour(_("MEDIUM FOREST GREEN")),
        wxColour(_("MEDIUM GOLDENROD")), wxColour(_("MEDIUM ORCHID")), wxColour(_("MEDIUM SEA GREEN")),
        wxColour(_("MEDIUM SLATE BLUE")), wxColour(_("MEDIUM SPRING GREEN")), wxColour(_("MEDIUM TURQUOISE")),
        wxColour(_("VIOLET RED")), wxColour(_("WHEAT")), wxColour(_("YELLOW")), wxColour(_("YELLOW GREEN"))};

    m_Colour = sightcolors[s_lastsightcolor];

    m_Colour.Set(m_Colour.Red(), m_Colour.Green(), m_Colour.Blue(), 150);

    if(++s_lastsightcolor == (sizeof sightcolors) / (sizeof *sightcolors))
       s_lastsightcolor=0;
}

Sight::~Sight ( )
{
}

void Sight::SetVisible(bool visible)
{
      m_bVisible = visible;
}

#include "astrolabe/astrolabe.hpp"

using namespace astrolabe;

using namespace astrolabe::calendar;
using namespace astrolabe::constants;
using namespace astrolabe::dynamical;
using namespace astrolabe::elp2000;
using namespace astrolabe::nutation;
using namespace astrolabe::sun;
using namespace astrolabe::util;
using namespace astrolabe::vsop87d;

/* calculate what position the body for this sight is directly over at a given time */ 
void Sight::BodyLocation(wxDateTime time, double *lat, double *lon, double *ghaast, double *rad)
{
    astrolabe::globals::vsop87d_text_path = (const char *)GetpSharedDataLocation()->mb_str();
    astrolabe::globals::vsop87d_text_path.append("plugins/celestial_navigation/data/");
    astrolabe::globals::vsop87d_text_path.append("vsop87d.txt");

    time.MakeFromUTC();
    double jdu = time.GetJulianDayNumber();
    // julian day dynamic
    double jdd = ut_to_dt(jdu);              
   
    double l, b, r;
    double ra, dec;
    // nutation in longitude
    const double deltaPsi = nut_in_lon(jdd);
    
    // apparent obliquity
    const double eps = obliquity(jdd) + nut_in_obl(jdd);

    Sun sun;
    sun.dimension3(jdd, l, b, r);

    // correct vsop coordinates    
    vsop_to_fk5(jdd, l, b);
    
    // nutation in longitude
    l += deltaPsi;
    
    // aberration
    l += aberration_low(r);

    if(!m_Body.Cmp(_T("Sun"))) {
       // equatorial coordinates
       ecl_to_equ(l, b, eps, ra, dec);

    } else
    if(!m_Body.Cmp(_T("Moon"))) {
          ELP2000 moon;
          moon.dimension3(jdd, l, b, r);

          // nutation in longitude
          l += deltaPsi;

          // equatorial coordinates
          ecl_to_equ(l, b, eps, ra, dec);
       }
    else {
       vPlanets planet;
       if(!m_Body.Cmp(_T("Mercury")))
          planet = vMercury;
       else if(!m_Body.Cmp(_T("Venus")))
          planet = vVenus;
       else if(!m_Body.Cmp(_T("Mars")))
          planet = vMars;
       else if(!m_Body.Cmp(_T("Jupiter")))
          planet = vJupiter;
       else if(!m_Body.Cmp(_T("Saturn")))
          planet = vSaturn;
       else { /* star maybe */
          if(!m_Body.Cmp(_T("Alpheratz"))) ra = 0.0365979981624047, dec = 0.508585349622516;
          else if(!m_Body.Cmp(_T("Ankaa"))) ra = 0.289219237568502, dec = -0.738378993348721;
          else if(!m_Body.Cmp(_T("Schedar"))) ra = 0.176746620828405, dec = 0.986762578179113;
          else if(!m_Body.Cmp(_T("Diphda"))) ra = 0.190182710825649, dec = -0.284027125450659;
          else if(!m_Body.Cmp(_T("Achernar"))) ra = 0.426358483543957, dec = -0.998969740640864;
          else if(!m_Body.Cmp(_T("Hamal"))) ra = 0.554898863177301, dec = 0.409496532815273;
          else if(!m_Body.Cmp(_T("Polaris"))) ra = 0.662403356568365, dec = 1.55795361238231;
          else if(!m_Body.Cmp(_T("Acamar"))) ra = 0.777812962468281, dec = -0.703449961435399;
          else if(!m_Body.Cmp(_T("Menkar"))) ra = 0.795346540133816, dec = 0.071379118269757;
          else if(!m_Body.Cmp(_T("Mirfak"))) ra = 0.891528726329137, dec = 0.870240557591617;
          else if(!m_Body.Cmp(_T("Aldebaran"))) ra = 1.20393095418572, dec = 0.288141690680868;
          else if(!m_Body.Cmp(_T("Rigel"))) ra = 1.37243034888306, dec = -0.143145651152089;
          else if(!m_Body.Cmp(_T("Capella"))) ra = 1.38181782770328, dec = 0.802816394191974;
          else if(!m_Body.Cmp(_T("Bellatrix"))) ra = 1.41865452145751, dec = 0.110823559364829;
          else if(!m_Body.Cmp(_T("Elnath"))) ra = 1.42371695076379, dec = 0.499297460743863;
          else if(!m_Body.Cmp(_T("Alnilam"))) ra = 1.46700741394297, dec = -0.0209774031679285;
          else if(!m_Body.Cmp(_T("Betelgeuse"))) ra = 1.54972913370916, dec = 0.129277633374139;
          else if(!m_Body.Cmp(_T("Canopus"))) ra = 1.67530590791159, dec = -0.919712778207749;
          else if(!m_Body.Cmp(_T("Sirius"))) ra = 1.76779435200004, dec = -0.291751259436422;
          else if(!m_Body.Cmp(_T("Adhara"))) ra = 1.82660341749553, dec = -0.505655821260435;
          else if(!m_Body.Cmp(_T("Procyon"))) ra = 2.00406704139727, dec = 0.0911692127326482;
          else if(!m_Body.Cmp(_T("Pollux"))) ra = 2.03035606325544, dec = 0.489152763555466;
          else if(!m_Body.Cmp(_T("Avior"))) ra = 2.19262805045961, dec = -1.03864058972501;
          else if(!m_Body.Cmp(_T("Suhail"))) ra = 2.3910865308218, dec = -0.758040127372437;
          else if(!m_Body.Cmp(_T("Miaplacidus"))) ra = 2.41379035550816, dec = -1.21679507312234;
          else if(!m_Body.Cmp(_T("Alphard"))) ra = 2.47656717980308, dec = -0.151121122246412;
          else if(!m_Body.Cmp(_T("Regulus"))) ra = 2.65435490407471, dec = 0.20886743009561;
          else if(!m_Body.Cmp(_T("Dubhe"))) ra = 2.65435490407471, dec = 0.20886743009561;
          else if(!m_Body.Cmp(_T("Denebola"))) ra = 3.09385626957378, dec = 0.254330430646302;
          else if(!m_Body.Cmp(_T("Gienah"))) ra = 3.21056008074728, dec = -0.306164425958095;
          else if(!m_Body.Cmp(_T("Acrux"))) ra = 3.25764947120958, dec = -1.10128690460105;
          else if(!m_Body.Cmp(_T("Gacrux"))) ra = 3.2775756189358, dec = -0.996815713455695;
          else if(!m_Body.Cmp(_T("Alioth"))) ra = 3.37732845789249, dec = 0.97668334053394;
          else if(!m_Body.Cmp(_T("Spica"))) ra = 3.51331719009724, dec = -0.194801816805651;
          else if(!m_Body.Cmp(_T("Alkaid"))) ra = 3.61082442298847, dec = 0.860680031800137;
          else if(!m_Body.Cmp(_T("Hadar"))) ra = 3.68187386795507, dec = -1.0537085989339;
          else if(!m_Body.Cmp(_T("Menkent"))) ra = 3.69437478872248, dec = -0.634753462707325;
          else if(!m_Body.Cmp(_T("Arcturus"))) ra = 3.73352834160889, dec = 0.334792935627001;
          else if(!m_Body.Cmp(_T("Rigil"))) ra = 3.83801502982356, dec = -1.06175315112964;
          else if(!m_Body.Cmp(_T("Zubenelgenubi"))) ra = 3.88635809755977, dec = -0.279201774882576;
          else if(!m_Body.Cmp(_T("Kochab"))) ra = 3.88643372849402, dec = 1.29425860309002;
          else if(!m_Body.Cmp(_T("Alphecca"))) ra = 4.07834490432777, dec = 0.466259352479109;
          else if(!m_Body.Cmp(_T("Antares"))) ra = 4.31707190480797, dec = -0.461324458259779;
          else if(!m_Body.Cmp(_T("Atria"))) ra = 4.40113132490715, dec = -1.2047619975572;
          else if(!m_Body.Cmp(_T("Sabik"))) ra = 4.49587361446958, dec = -0.274451570435065;
          else if(!m_Body.Cmp(_T("Shaula"))) ra = 4.59724088298436, dec = 0.647730470509584;
          else if(!m_Body.Cmp(_T("Rasalhague"))) ra = 4.6030222861316, dec = 0.219213354050488;
          else if(!m_Body.Cmp(_T("Eltanin"))) ra = 4.6975827705636, dec = 0.898652093745679;
          else if(!m_Body.Cmp(_T("Kaus Australis"))) ra = 4.81785922708271, dec = -0.600124675906715;
          else if(!m_Body.Cmp(_T("Vega"))) ra = 4.87356551168385, dec = 0.676903120509757;
          else if(!m_Body.Cmp(_T("Nunki"))) ra = 4.95353021482492, dec = -0.458964385260138;
          else if(!m_Body.Cmp(_T("Altair"))) ra = 5.1957723884129, dec = 0.154781417057421;
          else if(!m_Body.Cmp(_T("Peacock"))) ra = 5.34789972206191, dec = -0.964556211114666;
          else if(!m_Body.Cmp(_T("Deneb"))) ra = 5.41676750546352, dec = 0.790289933439844;
          else if(!m_Body.Cmp(_T("Enif"))) ra = 5.69058479415959, dec = 0.172351457559912;
          else if(!m_Body.Cmp(_T("Al Na'ir"))) ra = 5.7955112253515, dec = -0.819623585215376;
          else if(!m_Body.Cmp(_T("Fomalhaut"))) ra = 6.01113938223019, dec = -0.517005309535209;
          else if(!m_Body.Cmp(_T("Markab"))) ra = 6.04216260968439, dec = 0.265381676088868;
          else {
             wxString s;
             s.Printf ( _T ( "Unknown celestial body: " ) + m_Body);
             wxLogMessage ( s );
          }
          goto notplanet;
       }
       geocentric_planet(jdd, planet, deltaPsi, eps, days_per_second, ra, dec);
    notplanet:;
    }

    // account for earth's hour angle

    double gmst = sidereal_time_greenwich(jdu);
    double eoe = deltaPsi * cos(eps);
    double gast = gmst + eoe;
    ra = ra - gast;
	 
    if(lat)
        *lat = r_to_d(dec);
    if(lon)
        *lon = r_to_d(ra);
    if(ghaast)
        *ghaast = r_to_d(gast);
    if(rad)
        *rad = r;
 }

extern "C" int geomag_calc(double latitude, double longitude, double alt,
                           int day, int month, double year,
                           double results[14]);

/* Combine two lists of points by appending p2 to p1 */
wxRealPointList *Sight::MergePoints(wxRealPointList *p1, wxRealPointList *p2)
{
   /* combine lists of points */
   wxRealPointList *p = new wxRealPointList;
   wxRealPointList::iterator it;
   for (it = p1->begin(); it != p1->end(); ++it)
      p->Append(new wxRealPoint(**it));
   for (it = p2->begin(); it != p2->end(); ++it)
      p->Append(new wxRealPoint(**it));
   return p;
}

/* give the angle between two points from 0 to 2 PI */
double Sight::CalcAngle(wxRealPoint p1, wxRealPoint p2)
{
   /* rectangular coords */
   double phi = atan2(p1.y - p2.y, p1.x - p2.x);
   if(phi < 0)
      phi += 2*pi;
   return phi;
}

/* take a list of points, and return a list of points
   which form a convex polygon which encompasses all the points with vertices at points. */
wxRealPointList *Sight::ReduceToConvexPolygon(wxRealPointList *points)
{
   wxRealPointList *polygon = new wxRealPointList;
   wxRealPointList::iterator it, min;
   /* get min y point to start out at */
   for (min = it = points->begin(); it != points->end(); ++it)
      if((*it)->y < (*min)->y)
         min = it;

   double theta = 0;
   while(!points->IsEmpty()) {
      polygon->Append(*min);
      points->DeleteObject(*min);

      /* delete duplicates (optimization) */
      it = points->begin();
      while(it != points->end())
         if(**it == *polygon->back()) {
            wxRealPointList::iterator l = it;
            ++it;
            points->DeleteObject(*l);
         } else
            ++it;

      double minphi = 2*pi, maxdist = 0;
      for (min = it = points->begin(); it != points->end(); ++it) {
         double phi = CalcAngle(**it, *polygon->back());
         double dist = hypot((*it)->x - polygon->back()->x,
                             (*it)->y - polygon->back()->y);
         if(maxdist == 0)
            maxdist = dist;

         if((phi >= theta && phi < minphi)
            || (phi == minphi && dist > maxdist)) {
            min = it;
            minphi = phi;
            maxdist = dist;
         }
      }

      if(polygon->size() > 1 &&
         CalcAngle(*polygon->front(), *polygon->back()) < minphi)
         break;

      theta = minphi;
   }

   return polygon;
}

#if 0
// Calculates if two boxes intersect. If so, the function returns _ON.
// If they do not intersect, two scenario's are possible:
// other is outside this -> return _OUT
// other is inside this -> return _IN
enum OVERLAP {_IN,_ON,_OUT};

static OVERLAP Intersect(PlugIn_ViewPort *vp,
       double lat_min, double lat_max, double lon_min, double lon_max, double Marge)
{

    while(lon_min < vp->lon_min)
        lon_min += 360;
    while(lon_min > vp->lon_max)
        lon_min -= 360;
    while(lon_max < vp->lon_min)
        lon_max += 360;
    while(lon_max > vp->lon_max)
        lon_max -= 360;

    if (((vp->lon_min - Marge) > (lon_max + Marge)) ||
         ((vp->lon_max + Marge) < (lon_min - Marge)) ||
         ((vp->lat_max + Marge) < (lat_min - Marge)) ||
         ((vp->lat_min - Marge) > (lat_max + Marge)))
        return _OUT;

    // Check if other.bbox is inside this bbox
    if ((vp->lon_min <= lon_min) &&
         (vp->lon_max >= lon_max) &&
         (vp->lat_max >= lat_max) &&
         (vp->lat_min <= lat_min))
        return _IN;

    // Boundingboxes intersect
    return _ON;
}
#endif

/* Draw a polygon (specified in lat/lon coords) to dc given a list of points */
void Sight::DrawPolygon(PlugIn_ViewPort &VP, wxRealPointList &area)
{
   int n = area.size();
   wxPoint *ppoints = new wxPoint[n];
   bool rear1 = false, rear2 = false;
   wxRealPointList::iterator it = area.begin();

   double minx = 1000;
   double maxx = -1000;
   double miny = 1000;
   double maxy = -1000;

   for(int i=0; i<n && it != area.end(); i++, it++) {
      wxPoint r;

      /* don't draw areas crossing opposite from center longitude */
      double lon = (*it)->y - VP.clon;
      resolve_heading_positive(lon);

      if(lon > 90 && lon <= 180)
         rear1 = true;
      if(lon > 180 && lon < 270)
         rear2 = true;

      resolve_heading((*it)->y);

      minx = wxMin(minx, (*it)->x);
      miny = wxMin(miny, (*it)->y);
      maxx = wxMax(maxx, (*it)->x);
      maxy = wxMax(maxy, (*it)->y);

      GetCanvasPixLL(&VP, &r, (*it)->x, (*it)->y);

      ppoints[i] = r;
   }

   if(!(rear1 && rear2)) {
       if(m_dc) {
//           if(Intersect(&VP, minx, maxx, miny, maxy, 2) != _OUT)
               m_dc->DrawPolygon(n, ppoints);
       } else {
         glBegin(GL_POLYGON);
         for(int i=n-1; i>=0; i--)
             glVertex2i(ppoints[i].x, ppoints[i].y);
         glEnd();
       }
   }

   delete [] ppoints;
}

/* Compute trace areas for one dimension, given center certainty, and constant */
double Sight::ComputeStepSize(double certainty, double stepsize, double min, double max)
{
   return (max - min) / (floor(certainty / stepsize) + 1);
}

/* render the area of position for this sight */
void Sight::Render( wxDC *dc, PlugIn_ViewPort &VP )
{
    if ( !m_bVisible )
        return;

    m_dc = dc;
    
    if(dc) {
        dc->SetPen ( wxPen(m_Colour, 1) );
        dc->SetBrush ( wxBrush(m_Colour) );
    } else {
        glColor4ub(m_Colour.Red(), m_Colour.Green(), m_Colour.Blue(), m_Colour.Alpha());
        glPushAttrib(GL_COLOR_BUFFER_BIT | GL_POLYGON_BIT);      //Save state
        
        glEnable(GL_POLYGON_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    
    std::list<wxRealPointList*>::iterator it = polygons.begin();
    while(it != polygons.end()) {
        DrawPolygon(VP, **it);
        ++it;
    }
    
    if(!m_dc)
        glPopAttrib();            // restore state
}

void Sight::Recompute()
{
    switch(m_Type) {
    case ALTITUDE: RecomputeAltitude(); break;
    case AZIMUTH: RecomputeAzimuth(); break;
    }
}

void Sight::RebuildPolygons()
{
    switch(m_Type) {
    case ALTITUDE: RebuildPolygonsAltitude(); break;
    case AZIMUTH: RebuildPolygonsAzimuth(); break;
    }

    /* now shift the vertices as needed */
    for(std::list<wxRealPointList*>::iterator it = polygons.begin(); it != polygons.end(); it++) {
        wxRealPointList *area = *it;
        for(wxRealPointList::iterator it2 = area->begin(); it2 != area->end(); it2++) {
            wxRealPoint *p = *it2;
            double lat = p->x, lon = p->y;

            double localbearing = m_ShiftBearing;
            if(m_bMagneticShiftBearing) {
                double results[14];
                resolve_heading(lon);
                geomag_calc(lat, lon, m_EyeHeight,
                            m_DateTime.GetDay(), m_DateTime.GetMonth(), m_DateTime.GetYear(),
                            results);
                localbearing += results[0];
            }
            double localaltitude = 90-m_ShiftNm/60;
            *p = DistancePoint(localaltitude, localbearing, lat, lon);
        }
    }
}

void Sight::RecomputeAltitude()
{      
    m_CalcStr.clear();
    m_CalcStr+=_("Formulas used to calculate sight\n\n");

   /* correct for height of observer
      The dip of the sea horizon in minutes = 1.753*sqrt(height) */
    double EyeHeightCorrection = 1.753*sqrt(m_EyeHeight) / 60.0;
    m_CalcStr+=wxString::Format(_("Eye Height is %.3f meters\n\
Height Correction Degrees = 1.753*sqrt(%.3f) / 60.0\n\
Height Correction Degrees = %.3f\n"),
                                m_EyeHeight, m_EyeHeight, EyeHeightCorrection);
      
    /* compensate for refraction */
    double RefractionCorrection;
#if 0
    double Ha = m_Measurement - m_EyeHeightCorrection;
    double Ref = 1/tan(d_to_r(Ha + (7.31/(Ha + 4.4))));
    double RefImp = Ref - .06 * sin(d_to_r(14.7*Ref + 13));

    RefractionCorrection = RefImp * .00467 * m_Pressure / (273.15 + m_Temperature);
#else
    double x = tan(M_PI/180 * m_Measurement + 4.848e-2*(M_PI/180) / (tan(M_PI/180 * m_Measurement) + .028));
    m_CalcStr+=wxString::Format(_("\nRefraction Correction\n\
x = tan(Pi/180*Measurement + 4.848e-2*(Pi/180) / (tan(Pi/180*Measurement) + .028))\n\
x = tan(Pi/180*%.3f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.3f) + .028))\n\
x = %.3f\n"), m_Measurement, m_Measurement, x);
    RefractionCorrection = .267 * m_Pressure / (x*(m_Temperature + 273.15)) / 60.0;
    m_CalcStr+=wxString::Format(_("\
RefractionCorrection = .267 * Pressure / (x*(Temperature + 273.15)) / 60.0\n\
RefractionCorrection = .267 * %.3f / (x*(%.3f + 273.15)) / 60.0\n\
RefractionCorrection = %.5f\n"), m_Pressure, m_Temperature, RefractionCorrection);
#endif

    double SD = 0;
    double lc = 0;

    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_DateTime, 0, 0, 0, &rad);
        lc = 0.266564/rad;
        SD = r_to_d(sin(d_to_r(lc)));

        m_CalcStr+=wxString::Format(_("\nSun selected, Limb Correction\n\
ra = %.3f, lc = 0.266564/ra\n"), rad, lc);
    }

    /* moon radius: 1738 km
       distance to moon: 384400 km
    NOTE: could replace with a routine that finds the distance based on time */
    if(!m_Body.Cmp(_T("Moon"))){
        SD = r_to_d(1738/384400.0);
        lc = r_to_d(asin(d_to_r(SD)));
        m_CalcStr+=wxString::Format(_("\nMoon selected, Limb Correction\n\
SD = %.3f\n\
lc = 180/Pi * asin(Pi/180*SD)\n\
lc = %.3f\n"), SD, lc);
    }

    double LimbCorrection = 0;
    if(lc) {
        if(m_BodyLimb == UPPER) {
            LimbCorrection = lc;
            m_CalcStr+=wxString::Format(_("Upper Limb"));
        } else if(m_BodyLimb == LOWER) {
            LimbCorrection = -lc;
            m_CalcStr+=wxString::Format(_("Lower Limb"));
        }

        m_CalcStr+=wxString::Format(_("\nLimbCorrection = %.5f\n"), LimbCorrection);
    }


    double ObservedAltitude = m_Measurement - EyeHeightCorrection - RefractionCorrection - LimbCorrection;
    m_CalcStr+=wxString::Format(_("\nObserved Altitude\n\
ObservedAltitude = Measurement - EyeHeightCorrection - RefractionCorrection - LimbCorrection\n\
ObservedAltitude = %.3f - %.3f - %.3f - %.3f\n\
ObservedAltitude = %.5f\n"), m_Measurement, EyeHeightCorrection,
                                RefractionCorrection, LimbCorrection, ObservedAltitude);

    /* correct for limb shot */
    double ParallaxCorrection = 0;
    double HP = 0;
    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_DateTime, 0, 0, 0, &rad);
        HP = 0.002442/rad;

        m_CalcStr+=wxString::Format(_("\nSun selected, parallax correction\n\
rad = %.3f, HP = 0.002442/rad = %.3f\n"), rad, HP);
    }
      
    /* earth radius: 6357 km
       distance to moon: 384400 km
       NOTE: could replace with a routine that finds the distance based on time */
    if(!m_Body.Cmp(_T("Moon"))){
        HP = r_to_d(6357/384400.0);
        m_CalcStr+=wxString::Format(_("\nMoon selected, parallax correction\n\
HP = %.3f\n"), HP);
    }

    if(HP) {
        ParallaxCorrection = -r_to_d(asin(sin(d_to_r(HP))*cos(d_to_r(ObservedAltitude))));
        m_CalcStr+=wxString::Format(_("\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * ObservedAltitude))\n\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * %.3f ) * cos(Pi/180 * %.3f))\n\
ParallaxCorrection = %.5f\n"), HP, ObservedAltitude, ParallaxCorrection);
    }

    m_CorrectedAltitude = ObservedAltitude - ParallaxCorrection;
    m_CalcStr+=wxString::Format(_("\nCorrected Altitude\n\
CorrectedAltitude = ObservedAltitude - ParallaxCorrection\n\
CorrectedAltitude = %.3f - %.3f\n\
CorrectedAltitude = %.5f\n"), ObservedAltitude, ParallaxCorrection,
                                m_CorrectedAltitude);


   double lat, lon, ghaast, rad;
   BodyLocation(m_DateTime, &lat, &lon, &ghaast, &rad);

   double sha = 360 - lon - ghaast;
   resolve_heading_positive(sha);
   double sha_minutes = (sha - floor(sha))*60;
   sha = floor(sha);

   double ghaast_minutes = (ghaast - floor(ghaast))*60;
   ghaast = floor(ghaast);

   double gha = -lon;
   resolve_heading_positive(gha);
   double gha_minutes = (gha - floor(gha))*60;
   gha = floor(gha);

   double dec = lat;
   char dec_sign = dec > 0 ? 'N' : 'S';
   dec = fabs(dec);
   double dec_minutes = (dec - floor(dec))*60;
   dec = floor(dec);

   wxString almstr = _("Almanac Data For ") + m_Body +
wxString::Format(_("\n\
Geographical Position (lat, lon) = %.3f %.3f\n\
GHAAST = %.0f %.3f'\n\
SHA = %.0f %.3f'\n\
GHA = %.0f %.3f'\n\
Dec = %c %.0f %.3f'\n\
SD = %.3f'\n\
HP = %.3f'\n\n"), lat, lon,
                 ghaast, ghaast_minutes, sha, sha_minutes,
                 gha, gha_minutes, dec_sign, dec, dec_minutes,
                 SD*60, HP*60);

   m_CalcStr = almstr + m_CalcStr;
}

void Sight::RecomputeAzimuth()
{      
    m_CalcStr.clear();
    resolve_heading_positive(m_Measurement);
}

void Sight::RebuildPolygonsAltitude()
{
      polygons.clear();

      double altitudemin, altitudemax, altitudestep;
      altitudemin = m_CorrectedAltitude - m_MeasurementCertainty;
      altitudemax = m_CorrectedAltitude + m_MeasurementCertainty;
      altitudestep = ComputeStepSize(m_MeasurementCertainty, 1, altitudemin, altitudemax);

      double timemin, timemax, timestep;
      timemin =  - m_TimeCertainty;
      timemax =  + m_TimeCertainty;
      timestep = ComputeStepSize(m_TimeCertainty, 1, timemin, timemax);

      BuildAltitudeLineOfPosition(1, altitudemin, altitudemax, altitudestep,
                                  timemin, timemax, timestep);
}


/* Calculate latitude and longitude position for a sight taken with time, altitude,
    and trace angle */
wxRealPoint Sight::DistancePoint( double altitude, double trace, double lat, double lon)
{
    double rlat, rlon, y, x; 
  
    double dang_r = d_to_r(90-altitude);
    double trace_r = d_to_r(trace);
    double lat_r = d_to_r(lat);
    double lon_r = d_to_r(lon);
    double rlat_r, rlon_r;

    rlat_r = asin(sin(lat_r)*cos(dang_r)+cos(lat_r)*sin(dang_r)*cos(trace_r));
    y = sin(trace_r)*sin(dang_r)*cos(lat_r);
    x = cos(dang_r)-sin(lat_r)*sin(rlat_r);
    rlon_r = lon_r + atan2(y,x);
    
    rlat = r_to_d(rlat_r);
    rlon = r_to_d(rlon_r);
    
//    ll_gc_ll(lat, lon, trace, 60*(90-altitude),
//             &rlat, &rlon);
    
    return wxRealPoint(rlat, rlon);
 }

void Sight::BuildAltitudeLineOfPosition(double tracestep,
                                        double altitudemin, double altitudemax, double altitudestep,
                                        double timemin, double timemax, double timestep)
{
   double lat, lon;
   BodyLocation(m_DateTime, &lat, &lon, 0, 0);
   wxRealPointList *p, *l = new wxRealPointList;
   for(double trace=-180; trace<=180; trace+=tracestep) {
      p = new wxRealPointList;
      for(double altitude=altitudemin; altitude<=altitudemax
              && fabs(altitude) <= 90; altitude+=altitudestep) {
//         for(double time=timemin; time<=timemax; time+=timestep)
            p->Append(new wxRealPoint(DistancePoint( altitude, trace, lat, lon)));
            if(altitudestep == 0)
                break;
      }
      wxRealPointList *m = MergePoints(l, p);
      wxRealPointList *n = ReduceToConvexPolygon(m);
      polygons.push_back(n);

      m->DeleteContents(true);
      delete m;
      l->DeleteContents(true);
      delete l;

      l = p;
   }
}

void Sight::RebuildPolygonsAzimuth()
{
    polygons.clear();

    double azimuthmin, azimuthmax, azimuthstep;
    azimuthmin = m_Measurement - m_MeasurementCertainty;
    azimuthmax = m_Measurement + m_MeasurementCertainty;
    azimuthstep = ComputeStepSize(m_MeasurementCertainty, 1, azimuthmin, azimuthmax);
    
    double timemin, timemax, timestep;
    timemin = - m_TimeCertainty;
    timemax = + m_TimeCertainty;
    timestep = ComputeStepSize(m_TimeCertainty, 1, timemin, timemax);
    
    BuildBearingLineOfPosition(1, azimuthmin, azimuthmax, azimuthstep,
                               timemin, timemax, timestep);
}

/* find latitude and longitude which sees the body at the time, altitude and bearing
   iterative method so we can easily support magnetic variation */
bool Sight::BearingPoint( double altitude, double bearing,
                          double &rlat, double &rlon, double &trace, double &lastlat, double &lastlon,
                          double lat, double lon)
{
    double localbearing = bearing;

    resolve_heading(localbearing);
	
    double rangle;
    double mdb = 1000;
    double mdl = 1001;
    double b;
    if (trace > 999)
    {
        lastlat = lat;
        lastlon = lon;
            
        /* apply magnetic correction to bearing */
        if(m_bMagneticNorth) {
            double results[14];
            geomag_calc(lat, lon, m_EyeHeight,
                        m_DateTime.GetDay(), m_DateTime.GetMonth(), m_DateTime.GetYear(),
                        results);
            localbearing += results[0];
        }
        trace = localbearing + 180;
    }

    resolve_heading(trace);

    while((fabs(mdb)<fabs(mdl))&&(fabs(mdb)>.001)) {
//       ll_gc_ll(lat, lon, trace, 60*(90-altitude), &rlat, &rlon);
//       ll_gc_ll_reverse(rlat, rlon, lat, lon, &b, 0);
        mdl = mdb;
		
        double y, x, yy, xx;
	double dang_r = d_to_r(1.0);
	double trace_r = d_to_r(trace);
	double lat_r = d_to_r(lat);
	double lon_r = d_to_r(lon);
	double rlat_r, rlon_r, backbearing_r;
        double lastlat_r = d_to_r(lastlat);
        double lastlon_r = d_to_r(lastlon);
        double rangle_r;

	rlat_r = asin(sin(lastlat_r)*cos(dang_r)+cos(lastlat_r)*sin(dang_r)*cos(trace_r));
	y = sin(trace_r)*sin(dang_r)*cos(lastlat_r);
	x = cos(dang_r)-sin(lastlat_r)*sin(rlat_r);
	rlon_r = lastlon_r + atan2(y,x);

	yy = sin(lon_r - rlon_r)*cos(lat_r);
	xx = cos(rlat_r)*sin(lat_r) - sin(rlat_r)*cos(lat_r)*cos(lon_r - rlon_r);
	backbearing_r = atan2(yy,xx);
	
	rlat = r_to_d(rlat_r);
	rlon = r_to_d(rlon_r);

        resolve_heading(rlon);

	b = r_to_d(backbearing_r);

        rangle_r =  acos(sin(lat_r)*sin(rlat_r)+cos(lat_r)*cos(rlat_r)*cos(rlon_r - lon_r));
        rangle = r_to_d(rangle_r);
	
        /* apply magnetic correction to bearing */
        if(m_bMagneticNorth) {
            double results[14];
            geomag_calc(rlat, rlon, m_EyeHeight,
                        m_DateTime.GetDay(), m_DateTime.GetMonth(), m_DateTime.GetYear(),
                        results);
            b -= results[0];
        }

        mdb = bearing - b;
        resolve_heading(mdb);

        trace+=mdb;

        resolve_heading(trace);
    }	
    return ((fabs(mdb)<.1)&&(fabs(rangle)<90.0));
 }


void Sight::BuildBearingLineOfPosition(double altitudestep,
                                       double azimuthmin, double azimuthmax, double azimuthstep,
                                       double timemin, double timemax, double timestep)
{ 
    double lasttrace[100];
    for (int i = 0; i < 100; i++)
        lasttrace[i]= 1000.0;
    
    double lastlat[100];
    double lastlon[100];
    double trace;
    
    double blat, blon;
    
    BodyLocation(m_DateTime, &blat, &blon, 0, 0);

    resolve_heading(blon);

    wxRealPointList *p, *l = new wxRealPointList;
    l->Append(new wxRealPoint(blat, blon));
    for(double altitude=200; altitude>=0; altitude-=1) 
    {
        int index = 0;
        p = new wxRealPointList;
        double lat, lon, llat, llon;
        for(double azimuth=azimuthmin; azimuth<=azimuthmax; azimuth+=.25)
        {
            trace = lasttrace[index];
            llat = lastlat[index];
            llon = lastlon[index];
            if(BearingPoint(altitude, azimuth, lat, lon, trace, llat, llon, blat, blon))
            {
                if(lat > 90)
                    lat = 90.0;
                else if(lat < -90)
                    lat = -90.0;

                {
                    p->Append(new wxRealPoint(lat, lon)); 
                    lasttrace[index] = trace;

                    lastlat[index] = lat;
                    lastlon[index] = lon;
                }
            }
            index += 1;
        }
        wxRealPointList *m = MergePoints(l, p);
        wxRealPointList *n = ReduceToConvexPolygon(m);
        polygons.push_back(n);      
        m->DeleteContents(true);
        delete m;
        l->DeleteContents(true);
        delete l;
        l = p;
    }
}
