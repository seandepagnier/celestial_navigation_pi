/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Celestial Navigation Support
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2015 by Sean D'Epagnier                                 *
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

//#include "wx/wxprec.h"

//#ifndef  WX_PRECOMP
//  #include "wx/wx.h"
//#endif //precompiled headers

#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <wx/wx.h>
#include <wx/progdlg.h>
#include <wx/listimpl.cpp>
#include <wx/fileconf.h>

#include <GL/gl.h>

#include "ocpn_plugin.h"

#include "celestial_navigation_pi.h"
#include "Sight.h"
#include "transform_star.hpp"

WX_DEFINE_LIST ( wxRealPointList );

double resolve_heading(double heading)
{
   while(heading < -180)
      heading += 360;
   while(heading >= 180)
      heading -= 360;
   return heading;
}

double resolve_heading_positive(double heading)
{
   while(heading < 0)
      heading += 360;
   while(heading >= 360)
      heading -= 360;
   return heading;
}

//-----------------------------------------------------------------------------
//          Sight Implementation
//-----------------------------------------------------------------------------

int Sight::s_lastsightcolor;

Sight::Sight(Type type, wxString body, BodyLimb bodylimb, wxDateTime datetime,
             double timecertainty, double measurement, double measurementcertainty)
    : m_bVisible(true), m_Type(type), m_Body(body), m_BodyLimb(bodylimb),
     m_DateTime(datetime), m_TimeCertainty(timecertainty),
     m_Measurement(measurement), m_MeasurementCertainty(measurementcertainty),
      m_LunarMoonAltitude(NAN), m_LunarBodyAltitude(NAN),
      m_ShiftNm(0), m_ShiftBearing(0), m_bMagneticShiftBearing(true),
      m_bMagneticNorth(true)
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath( _T("/PlugIns/CelestialNavigation") );

    pConf->Read( _T("DefaultEyeHeight"), &m_EyeHeight, 2 ); 
    pConf->Read( _T("DefaultTemperature"), &m_Temperature, 10 );
    pConf->Read( _T("DefaultPressure"), &m_Pressure, 1010 );
    pConf->Read( _T("DefaultIndexError"), &m_IndexError, 0 );

    const wxString sightcolornames[] = {
        _T("MEDIUM VIOLET RED"), _T("MIDNIGHT BLUE"), _T("ORANGE"),
        _T("PLUM"), _T("PURPLE"), _T("RED"), _T("SALMON"),
        _T("SLATE BLUE"), _T("SPRING GREEN"),
        _T("ORANGE RED"), _T("ORCHID"), _T("PALE GREEN"), _T("PINK"),
        _T("BROWN"), _T("BLUE"), _T("GREEN YELLOW"),
        _T("GOLDENROD"), _T("BLUE VIOLET"),
        _T("AQUAMARINE"), _T("CADET BLUE"), _T("CORAL"),
        _T("CORNFLOWER BLUE"), _T("FOREST GREEN"), _T("GOLD"),
        _T("THISTLE"), _T("TURQUOISE"), _T("VIOLET"),
        _T("SEA GREEN"), _T("SKY BLUE"), _T("YELLOW GREEN"),
        _T("INDIAN RED"), _T("LIGHT BLUE"),
        _T("LIME GREEN"), _T("MAGENTA"), _T("MAROON"),
        _T("MEDIUM GOLDENROD"), _T("MEDIUM ORCHID"), _T("MEDIUM SEA GREEN"),
        _T("VIOLET RED"), _T("YELLOW")};

    m_ColourName = sightcolornames[s_lastsightcolor].Lower();
    m_Colour = wxColour(m_ColourName);

    m_Colour.Set(m_Colour.Red(), m_Colour.Green(), m_Colour.Blue(), 150);

    if(++s_lastsightcolor == (sizeof sightcolornames) / (sizeof *sightcolornames))
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

//    Used in Frontend2
//    astrolabe::globals::vsop87d_text_path = GetPluginDataDir("celestial_navigation_pi");
//    astrolabe::globals::vsop87d_text_path.append("/data/");
//    astrolabe::globals::vsop87d_text_path.append("vsop87d.txt");

//   Used in Master
//   static int error_message = 1;
     astrolabe::globals::vsop87d_text_path = (const char *)GetpSharedDataLocation()->mb_str();
     astrolabe::globals::vsop87d_text_path.append("plugins/celestial_navigation_pi/data/");
     astrolabe::globals::vsop87d_text_path.append("vsop87d.txt");
//  parent of 547ae52... android support



    time.MakeFromUTC();
    double jdu = time.GetJulianDayNumber();
    // julian day dynamic
    double jdd = ut_to_dt(jdu);              
   
    double l, b, r;
    double ra, dec, dra=0., ddec=0., radvel=0., parallax=0.;
    // nutation in longitude
    const double deltaPsi = nut_in_lon(jdd);
    
    // apparent obliquity
    const double eps = obliquity(jdd) + nut_in_obl(jdd);

    try {
        Sun sun;
        sun.dimension3(jdd, l, b, r);
    } catch (Error e) {
        static bool showonce = false;
        if(!showonce) {
            wxString err;
            const char *what = e.what();
            while(*what) err += *what++;

//  master duplicate
//            wxMessageDialog mdlg(NULL, _("vsop87d.txt missing or corrupt\n")
//                                 + err + _("The plugin will not work correctly"),
//                                 _("Failure Alert"), wxOK | wxICON_ERROR);
//            mdlg.ShowModal();
//            wxRemoveFile(astrolabe::globals::vsop87d_text_path);
//      parent of 547ae52... android support

            wxMessageDialog mdlg(NULL, _("Astrolab failed, data unavailable:\n")
                                 + err + _("\nDid you forget to install vsop87d.txt?\n")
                                 +_("The plugin will not work correctly"),
                                 wxString(_("Failure Alert"), wxOK | wxICON_ERROR));
            mdlg.ShowModal();
            showonce = true;

        }
        return;
    }

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
       vPlanets *planetPtr = &planet;
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
          planetPtr = NULL;
/* Numbers from http://simbad.u-strasbg.fr */
#define IFDEC_STAR(name,rahh,ramm,rass,drax,decdd,decmm,decss,ddecx,radvelx,parallaxx) if(!m_Body.Cmp(_T(name))) ra = (rahh+(ramm+rass/60.)/60.)/12.*pi, dra = drax, dec = (decdd>0?1.:-1.)*(abs(decdd)+(decmm+decss/60.)/60.)/180.*pi, ddec = ddecx, radvel = radvelx, parallax = parallaxx;
          IFDEC_STAR("Alpheratz",0,8,23.25988,137.46,29,5,25.5520,-163.44,-10.10,33.62)
          else IFDEC_STAR("Ankaa",0,26,17.05140,233.05,-42,18,21.55,-356.30,74.6,38.5)
	  else IFDEC_STAR("Schedar",0,40,30.44107,50.88,56,32,14.3922,-32.13,-4.31,14.29)
	  else IFDEC_STAR("Diphda",0,43,35.37090,232.55,-17,59,11.7827,31.99,13.32,33.86)
	  else IFDEC_STAR("Achernar",1,37,42.84548,87.00,-57,14,12.31,-38.24,18.60,23.39)
	  else IFDEC_STAR("Hamal",2,7,10.40570,188.55,23,27,44.7032,-148.08,-14.64,49.56)
	  else IFDEC_STAR("Polaris",2,31,49.09456,44.48,89,15,50.7923,-11.85,-16.42,7.54)
	  else IFDEC_STAR("Acamar",2,58,15.696,-44.6,-40,18,16.97,19.0,11.9,28.00)
	  else IFDEC_STAR("Menkar",3,2,16.77307,-10.41,4,5,23.0596,-76.85,-26.08,13.09)
	  else IFDEC_STAR("Mirfak",3,24,19.37009,23.75,49,51,40.2455,-26.23,-2.04,6.44)
	  else IFDEC_STAR("Aldebaran",4,35,55.23907,63.45,16,30,33.4885,-188.94,54.26,48.94)
          else IFDEC_STAR("Rigel",5,14,32.27210,1.31,-8,12,5.8981,0.50,17.80,3.78)
          else IFDEC_STAR("Capella",5,16,41.35871,75.25,45,59,52.7693,-426.89,29.19,76.2)
          else IFDEC_STAR("Bellatrix",5,25,7.86325,-8.11,6,20,58.9318,-12.88,18.2,12.92)
          else IFDEC_STAR("Elnath",5,26,17.51312,22.76,28,36,26.8262,-173.58,9.2,24.36)
          else IFDEC_STAR("Alnilam",5,36,12.81335,1.44,-1,12,6.9089,-0.78,27.30,1.65)
          else IFDEC_STAR("Betelgeuse",5,55,10.30536,27.54,7,24,25.4304,11.30,21.91,6.55)
          else IFDEC_STAR("Canopus",6,23,57.10988,19.93,-52,41,44.3810,23.24,20.30,10.55)
          else IFDEC_STAR("Sirius",6,45,8.91728,-546.01,-16,42,58.0171,-1223.07,-5.50,379.21)
          else IFDEC_STAR("Adhara",6,58,37.54876,3.24,-28,58,19.5102,1.33,27.30,8.05)
          else IFDEC_STAR("Procyon",7,39,18.11950,-714.59,5,13,29.9552,-1036.80,-3.2,284.56)
          else IFDEC_STAR("Pollux",7,45,18.94987,-626.55,28,1,34.3160,-45.80,3.23,96.54)
          else IFDEC_STAR("Avior",8,22,30.83526,-25.52,-59,30,34.1431,22.06,11.60,5.39)
          else IFDEC_STAR("Suhail",9,7,59.75787,-24.01,-43,25,57.3273,13.52,17.60,5.99)
          else IFDEC_STAR("Miaplacidus",9,13,11.97746,-156.47,-69,43,1.9473,108.95,-5.10,28.82)
          else IFDEC_STAR("Alphard",9,27,35.24270,-15.23,-8,39,30.9583,34.37,-4.27,18.09)
          else IFDEC_STAR("Regulus",10,8,22.31099,-248.73,11,58,1.9516,5.59,5.9,41.13)
          else IFDEC_STAR("Dubhe",11,3,43.67152,-134.11,61,45,3.7249,-34.70,-9.40,26.54)
          else IFDEC_STAR("Denebola",11,49,3.57834,-497.68,14,34,19.4090,-114.67,-0.20,90.91)
          else IFDEC_STAR("Gienah",12,15,48.37081,-158.61,-17,32,30.9496,21.86,-4.2,21.23)
          else IFDEC_STAR("Acrux",12,26,35.871,-35.3,-63,5,56.58,-12.0,-11.2,0.0)
          else IFDEC_STAR("Gacrux",12,31,9.95961,28.23,-57,6,47.5684,-265.08,21.00,36.83)
          else IFDEC_STAR("Alioth",12,54,1.74959,111.91,55,57,35.3627,-8.24,-12.70,39.51)
          else IFDEC_STAR("Spica",13,25,11.57937,-42.35,-11,9,40.7501,-30.67,1.0,13.06)
          else IFDEC_STAR("Alkaid",13,47,32.43776,-121.17,49,18,47.7602,-14.91,-13.40,31.38)
          else IFDEC_STAR("Hadar",14,3,49.40535,-33.27,-60,22,22.9266,-23.16,5.90,8.32)
          else IFDEC_STAR("Menkent",14,6,40.94752,-520.53,-36,22,11.8371,-518.06,1.30,55.45)
          else IFDEC_STAR("Arcturus",14,15,39.67207,-1093.39,19,10,56.6730,-2000.06,-5.19,88.83)
          else IFDEC_STAR("Rigil",14,39,36.49400,-3679.25,-60,50,2.3737,473.67,-21.40,754.81)
          else IFDEC_STAR("Zubenelgenubi",14,50,52.71309,-105.68,-16,2,30.3955,-68.40,-10.,43.03)
          else IFDEC_STAR("Kochab",14,50,42.32580,-32.61,74,9,19.8142,11.42,16.96,24.91)
          else IFDEC_STAR("Alphecca",15,34,41.26800,120.27,26,42,52.8940,-89.58,1.7,43.46)
          else IFDEC_STAR("Antares",16,29,24.45970,-12.11,-26,25,55.2094,-23.30,-3.50,5.89)
          else IFDEC_STAR("Atria",16,48,39.89508,17.99,-69,01,39.7626,-31.58,-3.00,8.35)
          else IFDEC_STAR("Sabik",17,10,22.68689,40.13,-15,43,29.6639,99.17,-2.40,36.91)
          else IFDEC_STAR("Shaula",17,33,36.52012,-8.53,-37,6,13.7648,-30.80,-3.00,5.71)
          else IFDEC_STAR("Rasalhague",17,34,56.06945,108.07,12,33,36.1346,-221.57,11.70,67.13)
          else IFDEC_STAR("Eltanin",17,56,36.36988,-8.48,51,29,20.0242,-22.79,-27.91,21.14)
          else IFDEC_STAR("Kaus Australis",18,24,10.31840,-39.42,-34,23,4.6193,-124.20,-15.00,22.76)
          else IFDEC_STAR("Vega",18,36,56.33635,200.94,38,47,1.2802,286.23,-20.60,130.23)
          else IFDEC_STAR("Nunki",18,55,15.92650,15.14,-26,17,48.2068,-53.43,-11.2,14.32)
          else IFDEC_STAR("Altair",19,50,46.99855,536.23,8,52,5.9563,385.29,-26.60,194.95)
          else IFDEC_STAR("Peacock",20,25,38.85705,6.90,-56,44,6.3230,-86.02,2.0,18.24)
          else IFDEC_STAR("Deneb",20,41,25.91514,2.01,45,16,49.2197,1.85,-4.90,2.31)
          else IFDEC_STAR("Enif",21,44,11.15614,26.92,9,52,30.0311,0.44,3.39,4.73)
          else IFDEC_STAR("Al Na'ir",22,8,13.98473,126.69,-46,57,39.5078,-147.47,10.90,32.29)
          else IFDEC_STAR("Fomalhaut",22,57,39.04625,328.95,-29,37,20.0533,-164.67,6.50,129.81)
          else IFDEC_STAR("Scheat",23,3,46.45746,187.65,28,4,58.0336,136.93,7.99,16.64)
          else IFDEC_STAR("Markab",23,4,45.65345,60.40,15,12,18.9617,-41.30,-2.70,24.46)
          else {
             wxString s;
             s.Printf ( _T ( "Unknown celestial body: " ) + m_Body);
             wxLogMessage ( s );
          }
          proper_motion_parallax(jdd,ra,dec,dra,ddec,radvel,parallax);
          frame_bias(ra,dec);
          precess(jdd,ra,dec);
          nutate(jdd,ra,dec);
       }
       if (planetPtr != NULL)
          geocentric_planet(jdd, planet, deltaPsi, eps, days_per_second, ra, dec);
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

std::list<wxRealPoint> Sight::GetPoints()
{
    std::list<wxRealPoint> points;
    for(std::list<wxRealPointList*>::iterator it = polygons.begin();
        it != polygons.end(); it++)
        for(wxRealPointList::iterator it2 = (*it)->begin(); it2 != (*it)->end(); it2++)
            points.push_back(**it2);
    return points;
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
      lon = resolve_heading_positive(lon);

      if(lon > 90 && lon <= 180)
         rear1 = true;
      if(lon > 180 && lon < 270)
         rear2 = true;

      (*it)->y = resolve_heading((*it)->y);

      minx = wxMin(minx, (*it)->x);
      miny = wxMin(miny, (*it)->y);
      maxx = wxMax(maxx, (*it)->x);
      maxy = wxMax(maxy, (*it)->y);

      GetCanvasPixLL(&VP, &r, (*it)->x, (*it)->y);

      ppoints[i] = r;
   }

   if(!(rear1 && rear2)) {
       if(m_dc)
           m_dc->DrawPolygon(n, ppoints);
       else {
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

void Sight::Recompute(int clock_offset)
{
    m_CalcStr.clear();

    if(clock_offset)
        m_CalcStr+=wxString::Format(_("Applying clock correction of %d seconds\n\n"), clock_offset);

    m_CorrectedDateTime = m_DateTime + wxTimeSpan::Seconds(clock_offset);
    
    switch(m_Type) {
    case ALTITUDE: RecomputeAltitude(); break;
    case AZIMUTH: RecomputeAzimuth(); break;
    case LUNAR: RecomputeLunar(); break;
    }
}

void Sight::RebuildPolygons()
{
    switch(m_Type) {
    case ALTITUDE: RebuildPolygonsAltitude(); break;
    case AZIMUTH: RebuildPolygonsAzimuth(); break;
    case LUNAR: return; // lunar has no polygons
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
                lon = resolve_heading(lon);
                geomag_calc(lat, lon, m_EyeHeight,
                            m_CorrectedDateTime.GetDay(), m_CorrectedDateTime.GetMonth(), m_CorrectedDateTime.GetYear(),
                            results);
                localbearing += results[0];
            }
            double localaltitude = 90-m_ShiftNm/60;
            *p = DistancePoint(localaltitude, localbearing, lat, lon);
        }
    }
}

wxString Sight::Alminac(double lat, double lon, double ghaast, double rad, double SD, double HP)
{
   double sha = 360 - lon - ghaast;
   sha = resolve_heading_positive(sha);
   double sha_minutes = (sha - floor(sha))*60;
   sha = floor(sha);

   double ghaast_minutes = (ghaast - floor(ghaast))*60;
   ghaast = floor(ghaast);

   double gha = -lon;
   gha = resolve_heading_positive(gha);
   double gha_minutes = (gha - floor(gha))*60;
   gha = floor(gha);

   double dec = lat;
   char dec_sign = dec > 0 ? 'N' : 'S';
   dec = fabs(dec);
   double dec_minutes = (dec - floor(dec))*60;
   dec = floor(dec);

   return _("Almanac Data For ") + m_Body +
wxString::Format(_("\n\
Geographical Position (lat, lon) = %.4f %.4f\n\
GHAAST = %.0f %.1f'\n\
SHA = %.0f %.1f'\n\
GHA = %.0f %.1f'\n\
Dec = %c %.0f %.1f'\n\
SD = %.1f'\n\
HP = %.1f'\n\n"), lat, lon,
                 ghaast, ghaast_minutes, sha, sha_minutes,
                 gha, gha_minutes, dec_sign, dec, dec_minutes,
                 SD*60, HP*60);
}

void Sight::RecomputeAltitude()
{      
    m_CalcStr+=_("Formulas used to calculate sight\n\n");

    /* correct for index error */
    double IndexCorrection = m_IndexError / 60.0;
    m_CalcStr+=wxString::Format(_("Index Error is %.4f degrees\n\n"), IndexCorrection);

    /* correct for height of observer
       The dip of the sea horizon in minutes = 1.758*sqrt(height) */
    double EyeHeightCorrection = 1.758*sqrt(m_EyeHeight) / 60.0;
    m_CalcStr+=wxString::Format(_("Eye Height is %.4f meters\n\
Height Correction Degrees = 1.758*sqrt(%.4f) / 60.0\n\
Height Correction Degrees = %.4f\n"),
                                m_EyeHeight, m_EyeHeight, EyeHeightCorrection);

    /* Apparent Altitude Ha */
    double ApparentAltitude = m_Measurement - IndexCorrection - EyeHeightCorrection;
    m_CalcStr+=wxString::Format(_("\nApparent Altitude (Ha)\n\
ApparentAltitude = Measurement - IndexCorrection - EyeHeightCorrection\n\
ApparentAltitude = %.4f - %.4f - %.4f\n\
ApparentAltitude = %.4f\n"), m_Measurement, IndexCorrection,
                                EyeHeightCorrection, ApparentAltitude);
    
    /* compensate for refraction */
    double RefractionCorrection;
#if 0
    /* old correction not used */
    double Ha = m_Measurement - m_EyeHeightCorrection;
    double Ref = 1/tan(d_to_r(Ha + (7.31/(Ha + 4.4))));
    double RefImp = Ref - .06 * sin(d_to_r(14.7*Ref + 13));

    RefractionCorrection = RefImp * .00467 * m_Pressure / (273.15 + m_Temperature);
#else
    double x = tan(M_PI/180 * ApparentAltitude + 4.848e-2*(M_PI/180)
                   / (tan(M_PI/180 * ApparentAltitude) + .028));
    m_CalcStr+=wxString::Format(_("\nRefraction Correction\n\
x = tan(Pi/180*ApparentAltitude + 4.848e-2*(Pi/180) / (tan(Pi/180*ApparentAltitude) + .028))\n\
x = tan(Pi/180*%.4f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.4f) + .028))\n\
x = %.4f\n"), ApparentAltitude, ApparentAltitude, x);
    RefractionCorrection = .267 * m_Pressure / (x*(m_Temperature + 273.15)) / 60.0;
    m_CalcStr+=wxString::Format(_("\
RefractionCorrection = .267 * Pressure / (x*(Temperature + 273.15)) / 60.0\n\
RefractionCorrection = .267 * %.4f / (x*(%.4f + 273.15)) / 60.0\n\
RefractionCorrection = %.4f\n"), m_Pressure, m_Temperature, RefractionCorrection);
#endif

    double SD = 0;
    double lc = 0;

    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_CorrectedDateTime, 0, 0, 0, &rad);
        lc = 0.266564/rad;
        SD = r_to_d(sin(d_to_r(lc)));

        m_CalcStr+=wxString::Format(_("\nSun selected, Limb Correction\n\
ra = %.4f, lc = 0.266564/ra = %.4f\n"), rad, lc);
    }

    /* moon radius: 1738 km
       distance to moon: 384400 km
    NOTE: could replace with a routine that finds the distance based on time */
    if(!m_Body.Cmp(_T("Moon"))){
        SD = r_to_d(1738/384400.0);
        lc = r_to_d(asin(d_to_r(SD)));
        m_CalcStr+=wxString::Format(_("\nMoon selected, Limb Correction\n\
SD = %.4f\n\
lc = 180/Pi * asin(Pi/180*SD)\n\
lc = %.4f\n"), SD, lc);
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

        m_CalcStr+=wxString::Format(_("\nLimbCorrection = %.4f\n"), LimbCorrection);
    }

    double CorrectedAltitude = ApparentAltitude - RefractionCorrection - LimbCorrection;
    m_CalcStr+=wxString::Format(_("\nCorrected Altitude\n\
CorrectedAltitude = ApparentAltitude - RefractionCorrection - LimbCorrection\n\
CorrectedAltitude = %.4f - %.4f - %.4f\n\
CorrectedAltitude = %.4f\n"), ApparentAltitude,
                                RefractionCorrection, LimbCorrection, CorrectedAltitude);

    /* correct for limb shot */
    double ParallaxCorrection = 0;
    double HP = 0;
    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_CorrectedDateTime, 0, 0, 0, &rad);
        HP = 0.002442/rad;

        m_CalcStr+=wxString::Format(_("\nSun selected, parallax correction\n\
rad = %.4f, HP = 0.002442/rad = %.4f\n"), rad, HP);
    }
      
    /* earth radius: 6357 km
       distance to moon: 384400 km
       NOTE: could replace with a routine that finds the distance based on time */
    if(!m_Body.Cmp(_T("Moon"))){
        HP = r_to_d(6357/384400.0);
        m_CalcStr+=wxString::Format(_("\nMoon selected, parallax correction\n\
HP = %.4f\n"), HP);
    }

    if(HP) {
        ParallaxCorrection = -r_to_d(asin(sin(d_to_r(HP))*cos(d_to_r(CorrectedAltitude))));
        m_CalcStr+=wxString::Format(_("\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * CorrectedAltitude))\n\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * %.4f ) * cos(Pi/180 * %.4f))\n\
ParallaxCorrection = %.4f\n"), HP, CorrectedAltitude, ParallaxCorrection);
    }

    m_ObservedAltitude = CorrectedAltitude - ParallaxCorrection;
    m_CalcStr+=wxString::Format(_("\nObserved Altitude (Ho)\n\
ObservedAltitude = CorrectedAltitude - ParallaxCorrection\n\
ObservedAltitude = %.4f - %.4f\n\
ObservedAltitude = %.4f\n"), CorrectedAltitude, ParallaxCorrection, m_ObservedAltitude);

   double lat, lon, ghaast, rad;
   BodyLocation(m_CorrectedDateTime, &lat, &lon, &ghaast, &rad);

   m_CalcStr = Alminac(lat, lon, ghaast, rad, SD, HP) + m_CalcStr;
}

void Sight::RecomputeAzimuth()
{      
    m_Measurement = resolve_heading_positive(m_Measurement);
}

void Sight::RecomputeLunar()
{      
    m_CalcStr+=_("Formulas used to calculate sight\n\n");

    /* correct for index error */
    double IndexCorrection = m_IndexError / 60.0;
    m_CalcStr+=wxString::Format(_("Index Error is %.4f degrees\n\n"), IndexCorrection);

    /* correct for height of observer
       The dip of the sea horizon in minutes = 1.758*sqrt(height) */
    double EyeHeightCorrection = 1.758*sqrt(m_EyeHeight) / 60.0;
    m_CalcStr+=wxString::Format(_("Eye Height is %.4f meters\n\
Height Correction Degrees = 1.758*sqrt(%.4f) / 60.0\n\
Height Correction Degrees = %.4f\n"),
                                m_EyeHeight, m_EyeHeight, EyeHeightCorrection);

    /* Apparent Altitude Ha */
    double ApparentAltitudeMoon = m_LunarMoonAltitude - IndexCorrection - EyeHeightCorrection;
    m_CalcStr+=wxString::Format(_("\nApparent Moon Altitude (Ha)\n\
ApparentAltitudeMoon = MeasurementMoon - IndexCorrection - EyeHeightCorrection\n\
ApparentAltitudeMoon = %.4f - %.4f - %.4f\n\
ApparentAltitudeMoon = %.4f\n"), m_LunarMoonAltitude, IndexCorrection,
                                EyeHeightCorrection, ApparentAltitudeMoon);
    
    /* compensate for refraction */
    double RefractionCorrectionMoon;

    double x = tan(M_PI/180 * ApparentAltitudeMoon + 4.848e-2*(M_PI/180)
                   / (tan(M_PI/180 * ApparentAltitudeMoon) + .028));
    m_CalcStr+=wxString::Format(_("\nRefraction Correction\n\
x = tan(Pi/180*ApparentAltitudeMoon + 4.848e-2*(Pi/180) / (tan(Pi/180*ApparentAltitudeMoon) + .028))\n\
x = tan(Pi/180*%.4f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.4f) + .028))\n\
x = %.4f\n"), ApparentAltitudeMoon, ApparentAltitudeMoon, x);
    RefractionCorrectionMoon = .267 * m_Pressure / (x*(m_Temperature + 273.15)) / 60.0;
    m_CalcStr+=wxString::Format(_("\
RefractionCorrectionMoon = .267 * Pressure / (x*(Temperature + 273.15)) / 60.0\n\
RefractionCorrectionMoon = .267 * %.4f / (x*(%.4f + 273.15)) / 60.0\n\
RefractionCorrectionMoon = %.4f\n"), m_Pressure, m_Temperature, RefractionCorrectionMoon);

    /* moon radius: 1738 km
       distance to moon: 384400 km
    NOTE: could replace with a routine that finds the distance based on time */
    double lunar_SD = r_to_d(1738/384400.0);
    double lunar_lc = r_to_d(asin(d_to_r(lunar_SD)));
    m_CalcStr+=wxString::Format(_("\nMoon selected, Limb Correction\n\
SD = %.4f\n\
lc = 180/Pi * asin(Pi/180*SD)\n\
lc = %.4f\n"), lunar_SD, lunar_lc);

    double LimbCorrectionMoon = 0;
    if(lunar_lc) {
        if(m_BodyLimb == UPPER) {
            LimbCorrectionMoon = lunar_lc;
            m_CalcStr+=wxString::Format(_("Upper Limb"));
        } else if(m_BodyLimb == LOWER) {
            LimbCorrectionMoon = -lunar_lc;
            m_CalcStr+=wxString::Format(_("Lower Limb"));
        }

        m_CalcStr+=wxString::Format(_("\nLimbCorrectionMoon = %.4f\n"), LimbCorrectionMoon);
    }

    m_CalcStr+=wxString::Format(_("\nLimbCorrectionMoon = %.4f\n"), LimbCorrectionMoon);

    double CorrectedAltitudeMoon = ApparentAltitudeMoon - RefractionCorrectionMoon - LimbCorrectionMoon;
    m_CalcStr+=wxString::Format(_("\nCorrected Altitude\n\
CorrectedAltitudeMoon = ApparentAltitudeMoon - RefractionCorrectionMoon - LimbCorrectionMoon\n\
CorrectedAltitudeMoon = %.4f - %.4f - %.4f\n\
CorrectedAltitudeMoon = %.4f\n"), ApparentAltitudeMoon, RefractionCorrectionMoon,
                                LimbCorrectionMoon, CorrectedAltitudeMoon);
    
    /* earth radius: 6357 km
       distance to moon: 384400 km
       NOTE: could replace with a routine that finds the distance based on time */
    double ParallaxCorrectionMoon;
    double lunar_HP = r_to_d(6357/384400.0);
    m_CalcStr+=wxString::Format(_("\nMoon selected, parallax correction\n\
HP = %.4f\n"), lunar_HP);

    ParallaxCorrectionMoon = -r_to_d(asin(sin(d_to_r(lunar_HP))*cos(d_to_r(CorrectedAltitudeMoon))));
    m_CalcStr+=wxString::Format(_("\
ParallaxCorrectionMoon = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * CorrectedAltitude))\n\
ParallaxCorrectionMoon = -180/Pi * asin( sin(Pi/180 * %.4f ) * cos(Pi/180 * %.4f))\n\
ParallaxCorrectionMoon = %.4f\n"), lunar_HP, CorrectedAltitudeMoon, ParallaxCorrectionMoon);


    // body

    /* Apparent Altitude Ha */
    double ApparentAltitude = m_LunarBodyAltitude - IndexCorrection - EyeHeightCorrection;
    m_CalcStr+=wxString::Format(_("\nApparent Altitude (Ha)\n\
ApparentAltitude = Measurement - IndexCorrection - EyeHeightCorrection\n\
ApparentAltitude = %.4f - %.4f - %.4f\n\
ApparentAltitude = %.4f\n"), m_LunarBodyAltitude, IndexCorrection,
                                EyeHeightCorrection, ApparentAltitude);
    
    /* compensate for refraction */
    double RefractionCorrection;

    x = tan(M_PI/180 * ApparentAltitude + 4.848e-2*(M_PI/180)
            / (tan(M_PI/180 * ApparentAltitude) + .028));
    m_CalcStr+=wxString::Format(_("\nRefraction Correction\n\
x = tan(Pi/180*ApparentAltitude + 4.848e-2*(Pi/180) / (tan(Pi/180*ApparentAltitude) + .028))\n\
x = tan(Pi/180*%.4f + 4.848e-2*(Pi/180) / (tan(Pi/180*%.4f) + .028))\n\
x = %.4f\n"), ApparentAltitude, ApparentAltitude, x);
    RefractionCorrection = .267 * m_Pressure / (x*(m_Temperature + 273.15)) / 60.0;
    m_CalcStr+=wxString::Format(_("\
RefractionCorrection = .267 * Pressure / (x*(Temperature + 273.15)) / 60.0\n\
RefractionCorrection = .267 * %.4f / (x*(%.4f + 273.15)) / 60.0\n\
RefractionCorrection = %.4f\n"), m_Pressure, m_Temperature, RefractionCorrection);

    double SD = 0;
    double lc = 0;

    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_CorrectedDateTime, 0, 0, 0, &rad);
        lc = 0.266564/rad;
        SD = r_to_d(sin(d_to_r(lc)));

        m_CalcStr+=wxString::Format(_("\nSun selected, Limb Correction\n\
ra = %.4f, lc = 0.266564/ra = %.4f\n"), rad, lc);
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

        m_CalcStr+=wxString::Format(_("\nLimbCorrection = %.4f\n"), LimbCorrection);
    }

    double CorrectedAltitude = ApparentAltitude - RefractionCorrection - LimbCorrection;
    m_CalcStr+=wxString::Format(_("\nCorrected Altitude\n\
CorrectedAltitude = ApparentAltitude - RefractionCorrection - LimbCorrection\n\
CorrectedAltitude = %.4f - %.4f - %.4f\n\
CorrectedAltitude = %.4f\n"), ApparentAltitude, RefractionCorrection,
                                LimbCorrection, CorrectedAltitude);

    /* correct for limb shot */
    double ParallaxCorrection = 0;
    double HP = 0;
    if( !m_Body.Cmp(_T("Sun"))) {
        double rad;
        BodyLocation(m_CorrectedDateTime, 0, 0, 0, &rad);
        HP = 0.002442/rad;

        m_CalcStr+=wxString::Format(_("\nSun selected, parallax correction\n\
rad = %.4f, HP = 0.002442/rad = %.4f\n"), rad, HP);
    }

    if(HP) {
        ParallaxCorrection = -r_to_d(asin(sin(d_to_r(HP))*cos(d_to_r(CorrectedAltitude))));
        m_CalcStr+=wxString::Format(_("\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * HP ) * cos(Pi/180 * CorrectedAltitude))\n\
ParallaxCorrection = -180/Pi * asin( sin(Pi/180 * %.4f ) * cos(Pi/180 * %.4f))\n\
ParallaxCorrection = %.4f\n"), HP, CorrectedAltitude, ParallaxCorrection);
    }


    double CorrectionsMoon = RefractionCorrectionMoon + LimbCorrectionMoon + ParallaxCorrectionMoon;
    double CorrectionsBody = RefractionCorrection + LimbCorrection + ParallaxCorrection;
    double Corrections = fabs(CorrectionsMoon - CorrectionsBody);

    m_CalcStr+=wxString::Format(_("\
CorrectionsMoon = %.4f\n\
CorrectionsBody = %.4f\n\
Corrections = abs(CorrectionsMoon - CorrectionsBody) = %.4f\n"), CorrectionsMoon, CorrectionsBody, Corrections);

    double CorrectedMeasurement = m_Measurement - Corrections - IndexCorrection;
    m_CalcStr+=wxString::Format(_("\
CorrectedMeasurement = Measurement - Corrections - IndexCorrection\n\
CorrectedMeasurement = %.4f - %.4f - %.4f\n\
CorrectedMeasurement = %.4f\n"), m_Measurement, Corrections, IndexCorrection,
                                CorrectedMeasurement);

   double lat, lon, ghaast, rad;
   BodyLocation(m_CorrectedDateTime, &lat, &lon, &ghaast, &rad);

   m_CalcStr = Alminac(lat, lon, ghaast, rad, SD, HP) + m_CalcStr;
   
   double lunar_lat, lunar_lon, lunar_ghaast, lunar_rad;
   wxString body = m_Body;
   m_Body = _T("Moon");
   BodyLocation(m_CorrectedDateTime, &lunar_lat, &lunar_lon, &lunar_ghaast, &lunar_rad);

   m_CalcStr = Alminac(lunar_lat, lunar_lon, lunar_ghaast, lunar_rad, lunar_SD, lunar_HP) + m_CalcStr;
   m_Body = body;

   // Compute angle between moon and body
   double x1 = cos(lunar_lat)*cos(lunar_lon),   y1 = cos(lunar_lat)*sin(lunar_lon),   z1 = sin(lunar_lat);
   double x2 = cos(lat)*cos(lon),               y2 = cos(lat)*sin(lon),               z2 = sin(lat);
   double ang = acos(x1*x2 + y1*y2 + z1*z2) * 180 / M_PI;

//   double CorrectedMeasurement = m_Measurement - IndexCorrection - LimbCorrection;
   m_CalcStr+=wxString::Format(_("\nCalculated angle between Moon and ") + m_Body + _T(" %.4f"), ang);
   double error = CorrectedMeasurement - ang;
   m_CalcStr+=wxString::Format(_("\nError from measurement: %.4f"), error);

   m_TimeCorrection = error * 6720;

   m_CalcStr+=_("\nMoon takes 28 days to orbit, one degree of error takes 6720 seconds");
   m_CalcStr+=wxString::Format(_("\nTime correction %.4f seconds"), m_TimeCorrection);
}

void Sight::RebuildPolygonsAltitude()
{
      polygons.clear();

      double altitudemin, altitudemax, altitudestep;
      altitudemin = m_ObservedAltitude - m_MeasurementCertainty/60;
      altitudemax = m_ObservedAltitude + m_MeasurementCertainty/60;
      altitudestep = ComputeStepSize(m_MeasurementCertainty/60, 1, altitudemin, altitudemax);

      double timemin, timemax, timestep;
      timemin =  - m_TimeCertainty;
      timemax =  + m_TimeCertainty;
//      timestep = ComputeStepSize(m_TimeCertainty, 1, timemin, timemax);
      timestep = wxMax(2*m_TimeCertainty, 1);
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
    for(double time=timemin; time<=timemax; time+=timestep) {
   double lat, lon;
   BodyLocation(m_CorrectedDateTime+wxTimeSpan::Seconds(time), &lat, &lon, 0, 0);
   wxRealPointList *p, *l = new wxRealPointList;
   for(double trace=-180; trace<=180; trace+=tracestep) {
      p = new wxRealPointList;
      for(double altitude=altitudemin; altitude<=altitudemax
              && fabs(altitude) <= 90; altitude+=altitudestep) {
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
}

void Sight::RebuildPolygonsAzimuth()
{
    polygons.clear();

    double azimuthmin, azimuthmax, azimuthstep;
    azimuthmin = m_Measurement - m_MeasurementCertainty/60;
    azimuthmax = m_Measurement + m_MeasurementCertainty/60;
    azimuthstep = ComputeStepSize(m_MeasurementCertainty/60, 1, azimuthmin, azimuthmax);
    
    double timemin, timemax, timestep;
    timemin = - m_TimeCertainty;
    timemax = + m_TimeCertainty;
//    timestep = ComputeStepSize(m_TimeCertainty, 1, timemin, timemax);
    timestep = wxMax(2*m_TimeCertainty, 1);
    
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

    localbearing = resolve_heading(localbearing);
	
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
                        m_CorrectedDateTime.GetDay(), m_CorrectedDateTime.GetMonth(), m_CorrectedDateTime.GetYear(),
                        results);
            localbearing += results[0];
        }
        trace = localbearing + 180;
    }

    trace = resolve_heading(trace);

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

        rlon = resolve_heading(rlon);

	b = r_to_d(backbearing_r);

        rangle_r =  acos(sin(lat_r)*sin(rlat_r)+cos(lat_r)*cos(rlat_r)*cos(rlon_r - lon_r));
        rangle = r_to_d(rangle_r);
	
        /* apply magnetic correction to bearing */
        if(m_bMagneticNorth) {
            double results[14];
            geomag_calc(rlat, rlon, m_EyeHeight,
                        m_CorrectedDateTime.GetDay(), m_CorrectedDateTime.GetMonth(), m_CorrectedDateTime.GetYear(),
                        results);
            b -= results[0];
        }

        mdb = bearing - b;
        mdb = resolve_heading(mdb);

        trace+=mdb;

        trace = resolve_heading(trace);
    }	
    return ((fabs(mdb)<.1)&&(fabs(rangle)<90.0));
 }


void Sight::BuildBearingLineOfPosition(double altitudestep,
                                       double azimuthmin, double azimuthmax, double azimuthstep,
                                       double timemin, double timemax, double timestep)
{ 
    for(double time=timemin; time<=timemax; time+=timestep) {
    double lasttrace[100];
    for (int i = 0; i < 100; i++)
        lasttrace[i]= 1000.0;
    
    double lastlat[100];
    double lastlon[100];
    double trace;
    
    double blat, blon;
    
    BodyLocation(m_CorrectedDateTime+wxTimeSpan::Seconds(time), &blat, &blon, 0, 0);

    blon = resolve_heading(blon);

    /* sometimes it takes a long time to build magnetic azimuth sights */
    wxProgressDialog progressdialog(
        _("Celestial Navigation"), _("Building bearing Sight Positions"), 201, NULL,
        wxPD_SMOOTH | wxPD_ELAPSED_TIME | wxPD_REMAINING_TIME);

    wxRealPointList *p, *l = new wxRealPointList;
    l->Append(new wxRealPoint(blat, blon));
    for(double altitude=200; altitude>=0; altitude-=1) 
    {
        if(m_bMagneticNorth && (int)altitude%10==0)
            progressdialog.Update(200-altitude);

        int index = 0;
        p = new wxRealPointList;
        double lat, lon, llat, llon;
        for(double azimuth=azimuthmin; azimuth<=azimuthmax; azimuth+=azimuthstep)
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
}
