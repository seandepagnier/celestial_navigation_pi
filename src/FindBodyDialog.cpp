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
#include "wx/wxprec.h"

#ifndef WX_PRECOMP
#include "wx/wx.h"
#endif

#include <wx/listimpl.cpp>    // toh, 2009.02.22

#include "wx/wxprec.h"


#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include "FindBodyDialog.h"

#include "../../../include/ocpn_plugin.h"

#include "Sight.h"
#include "celestial_navigation_pi.h"
#include "geodesic.h"

double FindBodyDialog::lat = -100, FindBodyDialog::lon;

FindBodyDialog::FindBodyDialog( wxWindow* parent, Sight &sight )
: FindBodyDialogBase(parent), m_Sight(sight)
{
    if(lat == -100) {
        lat = celestial_navigation_pi_CursorLat();
        lon = celestial_navigation_pi_CursorLon();
    }

    m_tLatitude->SetValue(wxString::Format(_T("%f"), lat));
    m_tLongitude->SetValue(wxString::Format(_T("%f"), lon));

    Centre();
    Update();
}

FindBodyDialog::~FindBodyDialog( )
{
}

extern "C" int geomag_calc(double latitude, double longitude, double alt,
                           int day, int month, double year, double results[14]);

void FindBodyDialog::OnUpdate( wxCommandEvent& event )
{
    Update();
}

void FindBodyDialog::OnDone( wxCommandEvent& event )
{
   EndModal(wxID_OK);
}

void FindBodyDialog::Update()
{
    double lat1, lon1, lat2, lon2, bearing, dist, ra;
    m_tLatitude->GetValue().ToDouble(&lat1);
    m_tLongitude->GetValue().ToDouble(&lon1);
    
    m_Sight.BodyLocation(m_Sight.m_DateTime, lat2, lon2, ra);

    ll_gc_ll_reverse(lat1, lon1, lat2, lon2, &bearing, &dist);

    dist = 90 - dist/60;

    if(m_cbMagneticAzimuth->GetValue()) {
        double results[14];
          
        geomag_calc(lat1, lon1, m_Sight.m_EyeHeight,
                    m_Sight.m_DateTime.GetDay(), m_Sight.m_DateTime.GetMonth(),
                    m_Sight.m_DateTime.GetYear(), results);
        bearing -= results[0];
    }
    
    m_stAltitude->SetLabel(wxString::Format(_T("%f"), dist));
    m_stAzimuth->SetLabel(wxString::Format(_T("%f"), bearing));
}
