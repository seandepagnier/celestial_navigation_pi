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


#include <list>

#ifdef __MSVC__
#include <float.h>
#include <iostream>
#include <limits>
#define NAN std::numeric_limits<double>::quiet_NaN ()
#define INFINITY std::numeric_limits<double>::infinity ()

#define isnan _isnan
#define isinf(x) (!_finite(x) && !_isnan(x))

#define trunc(d) ( ((d)>0) ? floor(d) : ceil(d) )
#endif

WX_DECLARE_LIST(wxRealPoint, wxRealPointList);

class piDC;

//    Sight
//----------------------------------------------------------------------------

const wxString SightType[] = {_("Altitude"), _("Azimuth"), _("Lunar")};

class Sight : public wxObject
{
public:
    enum Type {ALTITUDE, AZIMUTH, LUNAR};
    enum BodyLimb {LOWER, CENTER, UPPER};

    Sight() { s_lastsightcolor++; }
    Sight(Type type, wxString body, BodyLimb bodylimb, wxDateTime datetime,
          double timecertainty, double measurement, double measurementcertainty);

    ~Sight();

    void SetVisible(bool visible = true); ///< set visibility and make points selectable accordingly
    bool IsVisible() { return m_bVisible; }

    void Recompute(int clock_offset);
    void RebuildPolygons();

    wxString Alminac(double lat, double lon, double ghaast, double rad, double SD, double HP);
    void RecomputeAltitude();
    void RecomputeAzimuth();
    void RecomputeLunar();

    void RebuildPolygonsAltitude();
    void RebuildPolygonsAzimuth();

    bool       m_bVisible;  // should this sight be drawn?

    Type       m_Type;
    wxString   m_Body;
    BodyLimb   m_BodyLimb;

    wxDateTime  m_DateTime;      // Time for the sight
    double      m_TimeCertainty;

    double      m_Measurement; // Measurement angle in degrees (NaN is valid for all)
    double      m_MeasurementCertainty;
    double      m_LunarMoonAltitude, m_LunarBodyAltitude;

    double      m_EyeHeight; // Height above sea in meters
    double      m_Temperature; // Temperature in degrees celcius
    double      m_Pressure; // Pressure in millibars
    double      m_IndexError; // Error of measurement in degrees

    double      m_ShiftNm;               // direction to move points
    double      m_ShiftBearing;          // direction to move points
    bool        m_bMagneticShiftBearing; // use magnetic or true for shift
      
    wxString   m_ColourName;
    wxColour   m_Colour;     // Color of the sight

    virtual void Render(piDC &dc, PlugIn_ViewPort &pVP);

    void BodyLocation(wxDateTime time, double *lat, double *lon, double *ghaash, double *rad);
    std::list<wxRealPoint> GetPoints();

    wxString m_CalcStr;

    /* for altitude */
    double      m_ObservedAltitude; /* after all corrections are applied */

    /* for azimuth */
    bool       m_bMagneticNorth; // if azimuth angle is in magnetic coordinates

    /* for lunar */
    double m_TimeCorrection;

protected:
    double CalcAngle(wxRealPoint p1, wxRealPoint p2);
    double ComputeStepSize(double certainty, double stepsize, double min, double max);

    wxRealPointList *MergePoints(wxRealPointList *p1, wxRealPointList *p2);
    wxRealPointList *ReduceToConvexPolygon(wxRealPointList *points);

    std::list<wxRealPointList*> polygons;

private:
    wxRealPoint DistancePoint( double altitude, double trace, double lat, double lon);
    void BuildAltitudeLineOfPosition(double altitudemin, double altitudemax, double altitudestep,
                                     double tracestep, double timemin, double timemax, double timestep);
    bool BearingPoint(double altitude, double trace,
                      double &rlat, double &rlon, double &lasttrace, double &llat, double &llon,
                      double lat, double lon);
    void BuildBearingLineOfPosition(double altitudestep,
                                    double azimuthmin, double azimuthmax, double azimuthstep,
                                    double timemin, double timemax, double timestep);

    void DrawPolygon(piDC &dc, PlugIn_ViewPort &vp, wxRealPointList &area);

    wxDateTime m_CorrectedDateTime;

    static int s_lastsightcolor;
};

double resolve_heading(double heading);
double resolve_heading_positive(double heading);

