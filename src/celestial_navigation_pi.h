/******************************************************************************
 *
 * Project:  OpenCPN
 * Purpose:  Celestial Navigation Plugin
 * Author:   Sean D'Epagnier
 *
 ***************************************************************************
 *   Copyright (C) 2010, 2014 by Sean D'Epagnier                           *
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

#ifndef _CELESTIAL_NAVIGATIONPI_H_
#define _CELESTIAL_NAVIGATIONPI_H_

#include <wx/wx.h>

#include "version.h"

#define ABOUT_AUTHOR_URL "http://seandepagnier.users.sourceforge.net"

#include "ocpn_plugin.h"

#include "CelestialNavigationDialog.h"

//----------------------------------------------------------------------------------------------------------
//    The PlugIn Class Definition
//----------------------------------------------------------------------------------------------------------

#define CELESTIAL_NAVIGATION_TOOL_POSITION    -1  // Request default positioning of toolbar tool

class celestial_navigation_pi : public wxEvtHandler, opencpn_plugin_117
{
public:
      celestial_navigation_pi(void *ppimgr);
      ~celestial_navigation_pi(void);

//    The required PlugIn Methods
      int Init(void);
      bool DeInit(void);

      int GetAPIVersionMajor();
      int GetAPIVersionMinor();
      int GetPlugInVersionMajor();
      int GetPlugInVersionMinor();
      int GetPlugInVersionPatch();
      int GetPlugInVersionPost();
	  
      wxBitmap *GetPlugInBitmap();
      wxString GetCommonName();
      wxString GetShortDescription();
      wxString GetLongDescription();
	  //Shipdriver Panel Icon definition
	  wxBitmap m_panelBitmap; 

      void OnToolbarToolCallback(int id);

      int GetToolbarToolCount(void);
      void SetColorScheme(PI_ColorScheme cs);

      bool RenderOverlay( wxDC &dc, PlugIn_ViewPort *vp );
      bool RenderGLOverlay( wxGLContext *pcontext, PlugIn_ViewPort *vp );
      bool RenderOverlayAll(wxDC *dc, PlugIn_ViewPort *vp);

      static wxString StandardPath();
      void SetPositionFixEx(PlugIn_Position_Fix_Ex &pfix);
      void SetCursorLatLon(double lat, double lon);
	  

private:
      wxWindow         *m_parent_window;
      int               m_leftclick_tool_id;

      CelestialNavigationDialog       *m_pCelestialNavigationDialog;
};

extern void celestial_navigation_pi_BoatPos(double &lat, double &lon);

#endif
