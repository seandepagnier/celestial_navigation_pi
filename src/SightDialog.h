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

#ifndef _SIGHTDIALOG_H_
#define _SIGHTDIALOG_H_

#include "wx/listctrl.h"
#include "wx/calctrl.h"

#include "CelestialNavigationUI.h"


class Sight;

class SightDialog: public SightDialogBase
{

public:
   enum {ALTITUDE, AZIMUTH};

   SightDialog(wxWindow* parent, Sight &sight);
    ~SightDialog( );

//    void SetColorScheme(ColorScheme cs);

    void OnSetDefaults( wxCommandEvent& event );
    void MeasurementEntered( wxCommandEvent& event ) { EndModal(wxID_OK); }
    void Recompute( wxCommandEvent& event ) { Recompute(); }
    void RecomputeCalendar( wxCalendarEvent& event ) { Recompute(); }
    void RecomputeSpin( wxSpinEvent& event ) { Recompute(); }
//    void RecomputeScroll( wxScrollEvent& event ) { Recompute(); }
    void RecomputeColor( wxColourPickerEvent& event ) { Recompute(); }
    void OnFindBody( wxCommandEvent& event );

    wxDateTime DateTime();

    void Recompute();

private:
    Sight &m_Sight;
    bool m_breadytorecompute;
};



#endif
    // _SIGHTDIALOG_H_
