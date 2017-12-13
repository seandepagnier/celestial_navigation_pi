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

#ifndef _FIXDIALOG_H_
#define _FIXDIALOG_H_

#include "CelestialNavigationUI.h"

#include <list>

class Sight;

class FixDialog : public FixDialogBase
{
public:
    FixDialog(wxWindow *parent);
    void Update(int clock_offset, bool warnings);

    int m_clock_offset;
    double m_fixlat, m_fixlon, m_fixerror;
private:
    void OnGo( wxCommandEvent& event );
    void OnUpdate( wxCommandEvent& event ) { Update(m_clock_offset, false); }
    void OnUpdateSpin( wxSpinEvent& event ) { Update(m_clock_offset, false); }
};

#endif
    // _FIXDIALOG_H_
