/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Celestial Navigation Plugin
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
 */

#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif //precompiled headers

//#include <wx/wx.h>
#include <wx/stdpaths.h>
#include <GL/gl.h>

#include "ocpn_plugin.h"

#include "Sight.h"
#include "celestial_navigation_pi.h"
#include "icons.h"

using namespace std;

// the class factories, used to create and destroy instances of the PlugIn

extern "C" DECL_EXP opencpn_plugin* create_pi(void *ppimgr)
{
    return (opencpn_plugin *)new celestial_navigation_pi(ppimgr);
}

extern "C" DECL_EXP void destroy_pi(opencpn_plugin* p)
{
    delete p;
}

//---------------------------------------------------------------------------------------------------------
//
//    Celestial_Navigation PlugIn Implementation
//
//---------------------------------------------------------------------------------------------------------

celestial_navigation_pi::celestial_navigation_pi(void *ppimgr)
    :opencpn_plugin_116 (ppimgr)
{
    // Create the PlugIn icons
    initialize_images();
}

celestial_navigation_pi::~celestial_navigation_pi(void){}


//---------------------------------------------------------------------------------------------------------
//
//          PlugIn initialization and de-init
//
//---------------------------------------------------------------------------------------------------------

extern "C" int geomag_load(const char *mdfile);

int celestial_navigation_pi::Init(void)
{
    AddLocaleCatalog( _T("opencpn-celestial_navigation_pi") );




    // Get a pointer to the opencpn display canvas, to use as a parent for windows created
    m_parent_window = GetOCPNCanvasWindow();

    //    This PlugIn needs a toolbar icon, so request its insertion
 
#ifdef PLUGIN_USE_SVG
    m_leftclick_tool_id = InsertPlugInToolSVG( "Celestial Navigation" , _svg_celestial_navigation, _svg_celestial_navigation_rollover,
        _svg_celestial_navigation_toggled, wxITEM_CHECK, _( "Celestial Navigation" ),  "" , NULL, CELESTIAL_NAVIGATION_TOOL_POSITION, 0, this);
#else
    m_leftclick_tool_id  = InsertPlugInTool
        ("", _img_celestial_navigation, _img_celestial_navigation, wxITEM_NORMAL,
         _("Celestial Navigation"), "", NULL, CELESTIAL_NAVIGATION_TOOL_POSITION, 0, this);
#endif

    m_pCelestialNavigationDialog = NULL;	 

    return (WANTS_OVERLAY_CALLBACK |
            WANTS_OPENGL_OVERLAY_CALLBACK |
            WANTS_NMEA_EVENTS         |
//            WANTS_CURSOR_LATLON       |
            WANTS_TOOLBAR_CALLBACK    |
            INSTALLS_TOOLBAR_TOOL
        );
}

bool celestial_navigation_pi::DeInit(void)
{
    RemovePlugInTool(m_leftclick_tool_id);

    if(m_pCelestialNavigationDialog)
    {
        m_pCelestialNavigationDialog->Close();
        delete m_pCelestialNavigationDialog;
        m_pCelestialNavigationDialog = NULL;
    }
    return true;
}

int celestial_navigation_pi::GetAPIVersionMajor()
{
    return OCPN_API_VERSION_MAJOR;
}

int celestial_navigation_pi::GetAPIVersionMinor()
{
    return OCPN_API_VERSION_MINOR;
}

int celestial_navigation_pi::GetPlugInVersionMajor()
{
    return PLUGIN_VERSION_MAJOR;
}

int celestial_navigation_pi::GetPlugInVersionMinor()
{
    return PLUGIN_VERSION_MINOR;
}

wxBitmap *celestial_navigation_pi::GetPlugInBitmap()
{
    return new wxBitmap(_img_celestial_navigation->ConvertToImage().Copy());
}

wxString celestial_navigation_pi::GetCommonName()
{
 //   return _("Celestial Navigation");
	return _T(PLUGIN_COMMON_NAME);	
}

wxString celestial_navigation_pi::GetShortDescription()
{
	   return _(PLUGIN_SHORT_DESCRIPTION);
}

wxString celestial_navigation_pi::GetLongDescription()
{
       return _(PLUGIN_LONG_DESCRIPTION);

}

void celestial_navigation_pi::OnToolbarToolCallback(int id)
{
    int ret;
    if(!m_pCelestialNavigationDialog) {
        /* load the geographical magnetic table */
        wxString geomag_text_path = GetPluginDataDir("celestial_navigation_pi");   
//        geomag_text_path.Append(_T("plugins/celestial_navigation_pi/data/IGRF11.COF"));
        geomag_text_path.Append(_T("/data/IGRF11.COF"));		
        if((ret = geomag_load(geomag_text_path.mb_str())) < 0) {
	    wxString message = _("Failed to load file: ") + geomag_text_path + "\n";
	    switch (ret) {
	    case -1: message += "(" + _("open error") + ")\n"; break;
	    case -5: message += "(" + _("corrupt record") + ")\n"; break;
	    case -6: message += "(" + _("too many models") + ")\n"; break;
	    }
            wxMessageDialog mdlg(m_parent_window, message
                                 + _("Magnetic data will not be available for the celestial navigation plugin."),
                                 wxString(_("OpenCPN Alert"), wxOK | wxICON_ERROR));
            mdlg.ShowModal();
        }

        m_pCelestialNavigationDialog = new CelestialNavigationDialog(m_parent_window);
    }

    m_pCelestialNavigationDialog->Show(!m_pCelestialNavigationDialog->IsShown());
}

int celestial_navigation_pi::GetToolbarToolCount(void)
{
      return 1;
}

void celestial_navigation_pi::SetColorScheme(PI_ColorScheme cs)
{
    if (NULL == m_pCelestialNavigationDialog)
        return;

    DimeWindow(m_pCelestialNavigationDialog);
}

bool celestial_navigation_pi::RenderOverlay(wxDC &dc, PlugIn_ViewPort *vp)
{
    return RenderOverlayAll(&dc, vp);
}

bool celestial_navigation_pi::RenderGLOverlay(wxGLContext *pcontext, PlugIn_ViewPort *vp)
{
    return RenderOverlayAll(NULL, vp);
} 

bool celestial_navigation_pi::RenderOverlayAll(wxDC *dc, PlugIn_ViewPort *vp)
{
    if(!m_pCelestialNavigationDialog || !m_pCelestialNavigationDialog->IsShown())
        return false;

    /* draw sights */
    wxListCtrl *lSights = m_pCelestialNavigationDialog->m_lSights;
    for(int i = 0; i<lSights->GetItemCount(); i++) {
        Sight *s = (Sight*)wxUIntToPtr(lSights->GetItemData(i));
        s->Render ( dc, *vp );
    }

   /* now render fix */
   double lat = m_pCelestialNavigationDialog->m_FixDialog.m_fixlat;
   double lon = m_pCelestialNavigationDialog->m_FixDialog.m_fixlon;
   double err = m_pCelestialNavigationDialog->m_FixDialog.m_fixerror;
   wxPoint r1, r2;
   GetCanvasPixLL(vp, &r1, lat-1, lon-1);
   GetCanvasPixLL(vp, &r2, lat+1, lon+1);

   if(!isnan(err)) {
       if(dc) {
           dc->SetPen ( wxPen(wxColor(255, 0, 0), 1) );
           dc->SetBrush( *wxTRANSPARENT_BRUSH);
           dc->DrawLine( r1.x, r1.y, r2.x, r2.y );
           dc->DrawLine( r1.x, r2.y, r2.x, r1.y );
       } else {
           glColor3d(1, 0, 0);
           glBegin(GL_LINES);
           glVertex2i(r1.x, r1.y);
           glVertex2i(r2.x, r2.y);
           glVertex2i(r1.x, r2.y);
           glVertex2i(r2.x, r1.y);
           glEnd();
       }
   }

   return true;
}

wxString celestial_navigation_pi::StandardPath()
{
    wxString stdPath(*GetpPrivateApplicationDataLocation());
    stdPath = stdPath + wxFileName::GetPathSeparator() + "plugins"
        + wxFileName::GetPathSeparator() + "celestial_navigation"
        + wxFileName::GetPathSeparator();
    return stdPath;
}

static double s_boat_lat, s_boat_lon;
void celestial_navigation_pi::SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix)
{
    s_boat_lat = pfix.Lat;
    s_boat_lon = pfix.Lon;
}

void celestial_navigation_pi::SetCursorLatLon(double lat, double lon)
{
}

void celestial_navigation_pi_BoatPos(double &lat, double &lon)
{
    lat = s_boat_lat;
    lon = s_boat_lon;
}
