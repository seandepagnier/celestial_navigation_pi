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

#include <wx/wx.h>
#include <wx/listimpl.cpp>    // toh, 2009.02.22

#include "wx/notebook.h"
#include "wx/datetime.h"
#include "wx/colordlg.h"
#include "wx/fileconf.h"

#include "ocpn_plugin.h"

#include "Sight.h"
#include "SightDialog.h"
#include "FindBodyDialog.h"
#include "celestial_navigation_pi.h"

SightDialog::SightDialog( wxWindow* parent, Sight &s, int clock_offset)
    : SightDialogBase(parent), m_Sight(s), m_clock_offset(clock_offset), m_breadytorecompute(false)
{
    m_cBody->Append(_T("Sun"));
    m_cBody->Append(_T("Moon"));
    m_cBody->Append(_T("Mercury"));
    m_cBody->Append(_T("Venus"));
    m_cBody->Append(_T("Mars"));
    m_cBody->Append(_T("Jupiter"));
    m_cBody->Append(_T("Saturn"));

    m_cBody->Append(_T("Alpheratz"));
    m_cBody->Append(_T("Ankaa"));
    m_cBody->Append(_T("Achernar"));
    m_cBody->Append(_T("Acamar"));
    m_cBody->Append(_T("Acrux"));
    m_cBody->Append(_T("Alioth"));
    m_cBody->Append(_T("Alkaid"));
    m_cBody->Append(_T("Aldebaran"));
    m_cBody->Append(_T("Alnilam"));
    m_cBody->Append(_T("Adhara"));
    m_cBody->Append(_T("Avior"));
    m_cBody->Append(_T("Alphard"));
    m_cBody->Append(_T("Arcturus"));
    m_cBody->Append(_T("Alphecca"));
    m_cBody->Append(_T("Antares"));
    m_cBody->Append(_T("Atria"));
    m_cBody->Append(_T("Altair"));
    m_cBody->Append(_T("Al Na'ir"));
    m_cBody->Append(_T("Bellatrix"));
    m_cBody->Append(_T("Betelgeuse"));
    m_cBody->Append(_T("Canopus"));
    m_cBody->Append(_T("Capella"));
    m_cBody->Append(_T("Diphda"));
    m_cBody->Append(_T("Deneb"));
    m_cBody->Append(_T("Dubhe"));
    m_cBody->Append(_T("Denebola"));
    m_cBody->Append(_T("Eltanin"));
    m_cBody->Append(_T("Enif"));
    m_cBody->Append(_T("Elnath"));
    m_cBody->Append(_T("Fomalhaut"));
    m_cBody->Append(_T("Gienah"));
    m_cBody->Append(_T("Gacrux"));
    m_cBody->Append(_T("Hamal"));
    m_cBody->Append(_T("Kochab"));
    m_cBody->Append(_T("Kaus"));
    m_cBody->Append(_T("Hadar"));
    m_cBody->Append(_T("Menkar"));
    m_cBody->Append(_T("Mirfak"));
    m_cBody->Append(_T("Menkent"));
    m_cBody->Append(_T("Markab"));
    m_cBody->Append(_T("Miaplacidus"));
    m_cBody->Append(_T("Nunki"));
    m_cBody->Append(_T("Procyon"));
    m_cBody->Append(_T("Polaris"));
    m_cBody->Append(_T("Peacock"));
    m_cBody->Append(_T("Pollux"));
    m_cBody->Append(_T("Regulus"));
    m_cBody->Append(_T("Rigil"));
    m_cBody->Append(_T("Rigel"));
    m_cBody->Append(_T("Rasalhague"));
    m_cBody->Append(_T("Sirius"));
    m_cBody->Append(_T("Suhail"));
    m_cBody->Append(_T("Schedar"));
    m_cBody->Append(_T("Spica"));
    m_cBody->Append(_T("Sabik"));
    m_cBody->Append(_T("Shaula"));
    m_cBody->Append(_T("Vega"));
    m_cBody->Append(_T("Zubenelgenubi"));
    
    m_cBody->SetSelection(0);

//    SetColorScheme((ColorScheme)0);

    GetSizer()->SetSizeHints(this);
    Centre();

    m_cType->SetSelection(m_Sight.m_Type);

    m_cbMagneticAzimuth->Enable(m_cType->GetSelection() == AZIMUTH);
    m_cLimb->Enable(m_cType->GetSelection() == ALTITUDE);

    int index = m_cBody->FindString(m_Sight.m_Body);
    if(index != wxNOT_FOUND)
        m_cBody->SetSelection(index);

    m_cLimb->SetSelection((int)m_Sight.m_BodyLimb);
    m_Calendar->SetDate(m_Sight.m_DateTime);

    m_sHours->SetValue(m_Sight.m_DateTime.Format(_T("%H")));
    m_sMinutes->SetValue(m_Sight.m_DateTime.Format(_T("%M")));
    m_sSeconds->SetValue(m_Sight.m_DateTime.Format(_T("%S")));
   
    m_sCertaintySeconds->SetValue(m_Sight.m_TimeCertainty);

    m_sTransparency->SetValue(m_Sight.m_Colour.Alpha());
    m_tEyeHeight->SetValue(wxString::Format(_T("%.1f"), m_Sight.m_EyeHeight));
    m_sTemperature->SetValue(m_Sight.m_Temperature);
    m_sPressure->SetValue(m_Sight.m_Pressure);
    m_tIndexError->SetValue(wxString::Format(_T("%.5f"), m_Sight.m_IndexError));

    m_tShiftNm->SetValue(wxString::Format(_T("%.2f"), m_Sight.m_ShiftNm));
    m_tShiftBearing->SetValue(wxString::Format(_T("%.2f"), m_Sight.m_ShiftBearing));
    m_cbMagneticShiftBearing->SetValue(m_Sight.m_bMagneticShiftBearing);

    double measurement = trunc(m_Sight.m_Measurement);
    double measurementminutes = 60*(m_Sight.m_Measurement - measurement);
    m_tMeasurement->SetValue(wxString::Format(_T("%.0f"), measurement));
    m_tMeasurementMinutes->SetValue(wxString::Format(_T("%.2f"), measurementminutes));
    m_tMeasurementCertainty->SetValue(wxString::Format(_T("%.2f"), m_Sight.m_MeasurementCertainty));
    m_cbMagneticAzimuth->SetValue(m_Sight.m_bMagneticNorth);
    m_ColourPicker->SetColour(m_Sight.m_Colour);

    // calculate approximate lunar altitude
    if(wxIsNaN(m_Sight.m_LunarMoonAltitude))
        m_Sight.m_LunarMoonAltitude = BodyAltitude(_T("moon"));
    m_tLunarMoonAltitude->SetValue(wxString::Format(_T("%.2f"), m_Sight.m_LunarMoonAltitude));
    m_tLunarBodyAltitude->SetValue(wxString::Format(_T("%.2f"), m_Sight.m_LunarBodyAltitude));
    NewBody();
    
    m_breadytorecompute = true;
    Recompute();
}

SightDialog::~SightDialog( )
{
   if(m_Sight.m_MeasurementCertainty < .01) {
       wxMessageDialog w
           ( m_parent,
             _("Measurement certainty likely set to small, sight may not appear "),
             _("Warning"), wxOK | wxICON_WARNING );
       w.ShowModal();
   }
}

#if 0
void SightDialog::SetColorScheme(ColorScheme cs)
{
      SetBackgroundColour(GetGlobalColor(_T("DILG1")));

      wxColour back_color = GetGlobalColor(_T("DILG2"));
      wxColour text_color = GetGlobalColor(_T("DILG3"));

      m_CancelButton->SetBackgroundColour(back_color);
      m_CancelButton->SetForegroundColour(text_color);

      m_OKButton->SetBackgroundColour(back_color);
      m_OKButton->SetForegroundColour(text_color);
}
#endif

void SightDialog::NewBody()
{
    m_tLunarBodyAltitude->SetValue(wxString::Format(_T("%f"), BodyAltitude(m_cBody->GetStringSelection())));
}

void SightDialog::OnFindBody( wxCommandEvent& event )
{
   FindBodyDialog findbody_dialog(GetParent(), m_Sight);
   findbody_dialog.ShowModal();
}

wxDateTime SightDialog::DateTime()
{
   wxDateTime datetime =  m_Calendar->GetDate();

   double hours, minutes, seconds;
   hours = m_sHours->GetValue();
   minutes = m_sMinutes->GetValue();
   seconds = m_sSeconds->GetValue();

   double i;
   datetime.SetHour(hours);
   datetime.SetMinute(minutes);
   datetime.SetSecond(seconds);
   datetime.SetMillisecond(1000*modf(seconds, &i));

   return datetime;
}

void SightDialog::OnSetDefaults( wxCommandEvent& event )
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath( _T("/PlugIns/CelestialNavigation") );

    double eyeheight;
    m_tEyeHeight->GetValue().ToDouble(&eyeheight);
    pConf->Write( _T("DefaultEyeHeight"), eyeheight ); 
    pConf->Write( _T("DefaultTemperature"), m_sTemperature->GetValue() );
    pConf->Write( _T("DefaultPressure"), m_sPressure->GetValue() );
    double indexerror;
    m_tIndexError->GetValue().ToDouble(&indexerror);
    pConf->Write( _T("DefaultIndexError"), indexerror );
}

void SightDialog::Recompute()
{
    m_cbMagneticAzimuth->Enable(m_cType->GetSelection() == AZIMUTH);
    m_cLimb->Enable(m_cType->GetSelection() != AZIMUTH);

    m_fgSizerLunar->Show(m_cType->GetSelection() == LUNAR);

    if(!m_breadytorecompute)
        return;

   m_Sight.m_Type = (Sight::Type)m_cType->GetSelection();
   m_Sight.m_Body = m_cBody->GetStringSelection();
   m_Sight.m_BodyLimb = (Sight::BodyLimb)m_cLimb->GetSelection();

   if(!m_Sight.m_Body.Cmp(_T("Moon")) && m_cType->GetSelection() == LUNAR) {
       wxMessageDialog w
           ( m_parent,
             _("Lunar shot will be invalid taking distance from moon to itself"),
             _("Warning"), wxOK | wxICON_WARNING );
       w.ShowModal();
   }

   
   m_Sight.m_DateTime = DateTime();
   m_Sight.m_TimeCertainty = m_sCertaintySeconds->GetValue();

   double measurement, measurementminutes;
   m_tMeasurement->GetValue().ToDouble(&measurement);
   m_tMeasurementMinutes->GetValue().ToDouble(&measurementminutes);
   measurement += measurementminutes / 60;
   m_Sight.m_Measurement = measurement;

   double measurementcertainty;
   m_tMeasurementCertainty->GetValue().ToDouble(&measurementcertainty);
   m_Sight.m_MeasurementCertainty = measurementcertainty;

   m_tLunarMoonAltitude->GetValue().ToDouble(&m_Sight.m_LunarMoonAltitude);
   m_tLunarBodyAltitude->GetValue().ToDouble(&m_Sight.m_LunarBodyAltitude);

   m_tEyeHeight->GetValue().ToDouble(&m_Sight.m_EyeHeight);
   m_Sight.m_Temperature = m_sTemperature->GetValue();
   m_Sight.m_Pressure = m_sPressure->GetValue();
   m_tIndexError->GetValue().ToDouble(&m_Sight.m_IndexError);

   wxColour fc = m_ColourPicker->GetColour(), c = wxColour(m_Sight.m_ColourName);
   if(c.Red() != fc.Red() || c.Green() != fc.Green() || c.Blue() != fc.Blue())
       m_Sight.m_ColourName = fc.GetAsString();

   m_Sight.m_Colour = wxColour(fc.Red(), fc.Green(), fc.Blue(), m_sTransparency->GetValue());

   m_Sight.m_bMagneticNorth = m_cbMagneticAzimuth->GetValue();

   double shiftnm, shiftbearing;
   m_tShiftNm->GetValue().ToDouble(&shiftnm);
   m_Sight.m_ShiftNm = shiftnm;
   m_tShiftBearing->GetValue().ToDouble(&shiftbearing);
   m_Sight.m_ShiftBearing = shiftbearing;
   m_Sight.m_bMagneticShiftBearing = m_cbMagneticShiftBearing->GetValue();

   m_Sight.Recompute(m_clock_offset);
   m_tCalculations->SetValue(m_Sight.m_CalcStr);

   Refresh();
}

double SightDialog::BodyAltitude(wxString body)
{
    Sight lunar(Sight::ALTITUDE, body, Sight::CENTER, wxDateTime::Now(), 0, 0, 0);
    double lat1 = celestial_navigation_pi_CursorLat(), lat2;
    double lon1 = celestial_navigation_pi_CursorLon(), lon2;
    lunar.BodyLocation(lunar.m_DateTime, &lat2, &lon2, 0, 0);
    double bearing, dist;
    ll_gc_ll_reverse(lat1, lon1, lat2, lon2, &bearing, &dist);
    return 90 - dist/60;
}
