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

#ifndef _CelestialNavigationDialog_h_
#define _CelestialNavigationDialog_h_

#include "geodesic.h"
#include "CelestialNavigationUI.h"

class CelestialNavigationDialog : public CelestialNavigationDialogBase
{
public:
    CelestialNavigationDialog(wxWindow *parent);
    ~CelestialNavigationDialog();

    std::list<Sight*> m_SightList;

    double m_fixlat, m_fixlon, m_fixerror;

private:

    bool OpenXML(wxString filename, bool reportfailure);
    void SaveXML(wxString filename);

    void UpdateSights(bool warnings=true);     // Rebuild sight list
    void UpdateButtons();           // Correct button state
    void UpdateFix(bool warnings=true);

    // event handlers
    void OnNew(wxCommandEvent &event);
    void OnEdit( );
    void OnEditMouse( wxMouseEvent& event ) { OnEdit(); }
    void OnEdit(wxCommandEvent &event) { OnEdit(); }
    void OnDelete(wxCommandEvent &event);
    void OnDeleteAll(wxCommandEvent &event);
    void OnInformation( wxCommandEvent& event );
    void OnUpdateFixSpin( wxSpinEvent& event ) { UpdateFix(); }
    void OnUpdateFix( wxCommandEvent& event ) { UpdateFix(); }
    void OnGoFix( wxCommandEvent& event );
    void OnSightListLeftDown(wxMouseEvent &event);
    void OnBtnLeftDown(wxMouseEvent &event); // record control key state for some action buttons
    
    void OnSightSelected(wxListEvent &event);

    wxString m_sights_path;
};

#endif // _CelestialNavigationDialog_h_
