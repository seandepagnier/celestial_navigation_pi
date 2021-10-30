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
#include <wx/fileconf.h>

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/imaglist.h>

#include "tinyxml.h"

#include <GL/gl.h>

#include "ocpn_plugin.h"

#include "Sight.h"
#include "SightDialog.h"
#include "CelestialNavigationDialog.h"
#include "celestial_navigation_pi.h"


#include "astrolabe/astrolabe.hpp"
static wxString DataDirectory()
{
    wxString s = wxFileName::GetPathSeparator();
    return *GetpSharedDataLocation() + "plugins" + s + "celestial_navigation_pi" + s + "data" + s;
}

static wxString UserDataDirectory()
 {
    wxString s = wxFileName::GetPathSeparator();
    return *GetpPrivateApplicationDataLocation() + s + "plugins"
        + s + "celestial_navigation" + s;
 }


/* XPM */
static const char *eye[]={
"20 20 7 1",
". c none",
"# c #000000",
"a c #333333",
"b c #666666",
"c c #999999",
"d c #cccccc",
"e c #ffffff",
"....................",
"....................",
"....................",
"....................",
".......######.......",
".....#aabccb#a#.....",
"....#deeeddeebcb#...",
"..#aeeeec##aceaec#..",
".#bedaeee####dbcec#.",
"#aeedbdabc###bcceea#",
".#bedad######abcec#.",
"..#be#d######dadb#..",
"...#abac####abba#...",
".....##acbaca##.....",
".......######.......",
"....................",
"....................",
"....................",
"....................",
"...................."};

enum { rmVISIBLE = 0, rmTYPE, rmBODY, rmTIME, rmMEASUREMENT, rmCOLOR };// RMColumns;

// sort callback. Sort by body.
#if wxCHECK_VERSION(2, 9, 0)
int wxCALLBACK SortSights(long item1, long item2, wxIntPtr list)
#else
int wxCALLBACK SortSights(long item1, long item2, long list)
#endif
{
    wxListCtrl *lc = (wxListCtrl*)list;

    wxListItem it1, it2;
    it1.SetId(lc->FindItem(-1, item1));
    it1.SetColumn(1);

    it2.SetId(lc->FindItem(-1, item2));
    it2.SetColumn(1);

    lc->GetItem(it1);
    lc->GetItem(it2);

    return it1.GetText().Cmp(it2.GetText());
}

CelestialNavigationDialog::CelestialNavigationDialog(wxWindow *parent)
    : CelestialNavigationDialogBase(parent),
      m_FixDialog(this),
      m_ClockCorrectionDialog(this)
{
    wxFileConfig *pConf = GetOCPNConfigObject();

    pConf->SetPath( _T("/PlugIns/CelestialNavigation") );

//#ifdef __WXGTK__
//    Move(0, 0);        // workaround for gtk autocentre dialog behavior
//#endif
//    Move(pConf->Read ( _T ( "DialogPosX" ), 20L ), pConf->Read ( _T ( "DialogPosY" ), 20L ));
    wxPoint p = GetPosition();
    pConf->Read ( _T ( "DialogX" ), &p.x, p.x);
    pConf->Read ( _T ( "DialogY" ), &p.y, p.y);
    SetPosition(p);

    wxSize s = GetSize();
    pConf->Read ( _T ( "DialogWidth" ), &s.x, s.x);
    pConf->Read ( _T ( "DialogHeight" ), &s.y, s.y);
    SetSize(s);

// create a image list for the list with just the eye icon
    wxImageList *imglist = new wxImageList(20, 20, true, 1);
    imglist->Add(wxBitmap(eye));
    m_lSights->AssignImageList(imglist, wxIMAGE_LIST_SMALL);

    m_lSights->InsertColumn(rmVISIBLE, wxT(""));
    m_lSights->SetColumnWidth(0, 28);

    m_lSights->InsertColumn(rmTYPE, _("Type"));
    m_lSights->InsertColumn(rmBODY, _("Body"));
    m_lSights->InsertColumn(rmTIME, _("Time (UT)"));
    m_lSights->InsertColumn(rmMEASUREMENT, _("Measurement"));
    m_lSights->InsertColumn(rmCOLOR, _("Color"));

    m_sights_path = celestial_navigation_pi::StandardPath() + _T("Sights.xml");

    if(!OpenXML(m_sights_path, false)) {
        /* create directory for plugin files if it doesn't already exist */
        wxFileName fn(m_sights_path);
        wxFileName fn2 = fn.GetPath();
        if(!fn.DirExists()) {
            fn2.Mkdir();
            fn.Mkdir();
        }
    }

//
#ifdef __OCPN__ANDROID__
    GetHandle()->setAttribute(Qt::WA_AcceptTouchEvents);
    GetHandle()->grabGesture(Qt::PanGesture);
    GetHandle()->setStyleSheet( qtStyleSheet);
    m_lSights->GetHandle()->setAttribute(Qt::WA_AcceptTouchEvents);//
    m_lSights->GetHandle()->grabGesture(Qt::PanGesture);
    m_lSights->Connect( wxEVT_QT_PANGESTURE,
                       (wxObjectEventFunction) (wxEventFunction) &CelestialNavigationDialog::OnEvtPanGesture, NULL, this );
    GetHandle()->setStyleSheet( qtStyleSheet);//
   Move(0, 0);
#endif

//

}

#ifdef __OCPN__ANDROID__
void CelestialNavigationDialog::OnEvtPanGesture( wxQT_PanGestureEvent &event)
{
    switch(event.GetState()){
        case GestureStarted:
            m_startPos = GetPosition();
            m_startMouse = event.GetCursorPos(); //g_mouse_pos_screen;
            break;
        default:
        {
            wxPoint pos = event.GetCursorPos();
            int x = wxMax(0, pos.x + m_startPos.x - m_startMouse.x);
            int y = wxMax(0, pos.y + m_startPos.y - m_startMouse.y);
            int xmax = ::wxGetDisplaySize().x - GetSize().x;
            x = wxMin(x, xmax);
            int ymax = ::wxGetDisplaySize().y - GetSize().y;          // Some fluff at the bottom
            y = wxMin(y, ymax);

            Move(x, y);
        } break;
    }
// master
}
#endif

CelestialNavigationDialog::~CelestialNavigationDialog()
{
    wxFileConfig *pConf = GetOCPNConfigObject();
    pConf->SetPath( _T("/PlugIns/CelestialNavigation") );

    wxPoint p = GetPosition();
    pConf->Write ( _T ( "DialogX" ), p.x);
    pConf->Write ( _T ( "DialogY" ), p.y);

    wxSize s = GetSize();
    pConf->Write ( _T ( "DialogWidth" ), s.x);
    pConf->Write ( _T ( "DialogHeight" ), s.y);

    SaveXML(m_sights_path);
}

#define FAIL(X) do { error = X; goto failed; } while(0)
double AttributeDouble(TiXmlElement *e, const char *name, double def)
{
    const char *attr = e->Attribute(name);
    if(!attr)
        return def;
    char *end;
    double d = strtod(attr, &end);
    if(end == attr)
        return def;
    return d;
}

int AttributeInt(TiXmlElement *e, const char *name, int def)
{
    const char *attr = e->Attribute(name);
    if(!attr)
        return def;
    char *end;
    long d = strtol(attr, &end, 10);
    if(end == attr)
        return def;
    return d;
}

bool AttributeBool(TiXmlElement *e, const char *name, bool def)
{
    return AttributeInt(e, name, def) != 0;
}

bool CelestialNavigationDialog::OpenXML(wxString filename, bool reportfailure)
{
    TiXmlDocument doc;
    wxString error;

    wxFileName fn(filename);

    if(!doc.LoadFile(filename.mb_str()))
        FAIL(_("Failed to load file: ") + filename);
    else {
        TiXmlHandle root(doc.RootElement());

        if(strcmp(root.Element()->Value(), "OpenCPNCelestialNavigation"))
            FAIL(_("Invalid xml file"));

        m_lSights->DeleteAllItems();

        for(TiXmlElement* e = root.FirstChild().Element(); e; e = e->NextSiblingElement()) {
            if(!strcmp(e->Value(), "ClockError")) {
                m_ClockCorrectionDialog.m_sClockCorrection->SetValue(AttributeInt(e, "Seconds", 0));
            } else if(!strcmp(e->Value(), "Sight")) {
                Sight s;

                s.m_bVisible = AttributeBool(e, "Visible", true);
                s.m_Type = (Sight::Type)AttributeInt(e, "Type", 0);
                s.m_Body = wxString::FromUTF8(e->Attribute("Body"));
                s.m_BodyLimb = (Sight::BodyLimb)AttributeInt(e, "BodyLimb", 0);

                s.m_DateTime.ParseISODate(wxString::FromUTF8(e->Attribute("Date")));

                wxDateTime time;
                time.ParseISOTime(wxString::FromUTF8(e->Attribute("Time")));

                if(s.m_DateTime.IsValid() && time.IsValid()) {
                    s.m_DateTime.SetHour(time.GetHour());
                    s.m_DateTime.SetMinute(time.GetMinute());
                    s.m_DateTime.SetSecond(time.GetSecond());
                } else
                    continue; /* skip if invalid */

                s.m_TimeCertainty = AttributeDouble(e, "TimeCertainty", 0);

                s.m_Measurement = AttributeDouble(e, "Measurement", 0);
                s.m_MeasurementCertainty = AttributeDouble(e, "MeasurementCertainty", .25);

                s.m_EyeHeight = AttributeDouble(e, "EyeHeight", 2);
                s.m_Temperature = AttributeDouble(e, "Temperature", 10);
                s.m_Pressure = AttributeDouble(e, "Pressure", 1010);
                s.m_IndexError = AttributeDouble(e, "IndexError", 0);

                s.m_ShiftNm = AttributeDouble(e, "ShiftNm", 0);
                s.m_ShiftBearing = AttributeDouble(e, "ShiftBearing", 0);
                s.m_bMagneticShiftBearing = AttributeBool(e, "MagneticShiftBearing", 0);

                s.m_ColourName = wxString::FromUTF8(e->Attribute("ColourName"));
                s.m_Colour = wxColour(wxString::FromUTF8(e->Attribute("Colour")));
                s.m_Colour.Set(s.m_Colour.Red(), s.m_Colour.Green(), s.m_Colour.Blue(),
                               AttributeInt(e, "Transparency", 150));

                Sight *ns = new Sight(s);

                ns->Recompute(m_ClockCorrectionDialog.m_sClockCorrection->GetValue());
                ns->RebuildPolygons();
                InsertSight(ns, false);
            } else
                FAIL(_("Unrecognized xml node"));
        }
    }

    RequestRefresh( GetParent() );
    return true;
failed:

    if(reportfailure) {
        wxMessageDialog mdlg(this, error, _("Celestial Navigation"), wxOK | wxICON_ERROR);
        mdlg.ShowModal();
    }
    return false;
}

void CelestialNavigationDialog::SaveXML(wxString filename)
{
    TiXmlDocument doc;
    TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "utf-8", "" );
    doc.LinkEndChild( decl );

    TiXmlElement * root = new TiXmlElement( "OpenCPNCelestialNavigation" );
    doc.LinkEndChild( root );

    char version[24];
    sprintf(version, "%d.%d", PLUGIN_VERSION_MAJOR, PLUGIN_VERSION_MINOR);
    root->SetAttribute("version", version);
    root->SetAttribute("creator", "Opencpn Celestial Navigation plugin");

    TiXmlElement *c = new TiXmlElement( "ClockError" );
    c->SetAttribute("Seconds", m_ClockCorrectionDialog.m_sClockCorrection->GetValue());
    root->LinkEndChild(c);

    for(int i = 0; i<m_lSights->GetItemCount(); i++) {
        TiXmlElement *c = new TiXmlElement( "Sight" );

        Sight *s = (Sight*)wxUIntToPtr(m_lSights->GetItemData(i));

        c->SetAttribute("Visible", s->m_bVisible);
        c->SetAttribute("Type", s->m_Type);
        c->SetAttribute("Body", s->m_Body.mb_str());
        c->SetAttribute("BodyLimb", s->m_BodyLimb);

        c->SetAttribute("Date", s->m_DateTime.FormatISODate().mb_str());
        c->SetAttribute("Time", s->m_DateTime.FormatISOTime().mb_str());

        c->SetDoubleAttribute("TimeCertainty", s->m_TimeCertainty);

        c->SetDoubleAttribute("Measurement", s->m_Measurement);
        c->SetDoubleAttribute("MeasurementCertainty", s->m_MeasurementCertainty);

        c->SetDoubleAttribute("EyeHeight", s->m_EyeHeight);
        c->SetDoubleAttribute("Temperature", s->m_Temperature);
        c->SetDoubleAttribute("Pressure", s->m_Pressure);
        c->SetDoubleAttribute("IndexError", s->m_IndexError);

        c->SetDoubleAttribute("ShiftNm", s->m_ShiftNm);
        c->SetDoubleAttribute("ShiftBearing", s->m_ShiftBearing);
        c->SetDoubleAttribute("MagneticShiftBearing", s->m_bMagneticShiftBearing);

        c->SetAttribute("ColourName", s->m_ColourName.mb_str());
        c->SetAttribute("Colour", s->m_Colour.GetAsString().mb_str());
        c->SetAttribute("Transparency", s->m_Colour.Alpha());

        root->LinkEndChild(c);
    }

    if(!doc.SaveFile(filename.mb_str())) {
        wxMessageDialog mdlg(this, _("Failed to save xml file: ") + filename,
                             _("Celestial Navigation"), wxOK | wxICON_ERROR);
        mdlg.ShowModal();
    }
}

void CelestialNavigationDialog::InsertSight(Sight *s, bool warnings)
{
#if 1
    wxListItem item;
    item.SetId(m_lSights->GetItemCount());
    item.SetData(s);
    item.SetMask(item.GetMask() | wxLIST_MASK_TEXT);

    int idx = m_lSights->InsertItem(item);
    m_lSights->SetItemImage(idx, s->IsVisible() ? 0 : -1);
#else
    idx = m_lSights->InsertItem(idx+1, (*it)->IsVisible() ? 0 : -1);
#endif
    UpdateSight(idx, warnings);
}

void CelestialNavigationDialog::UpdateSight(int idx, bool warnings)
{
    Sight *s = (Sight*)wxUIntToPtr(m_lSights->GetItemData(idx));

    // then add sights to the listctrl
    m_lSights->SetItem(idx, rmTYPE, SightType[s->m_Type]);
    m_lSights->SetItem(idx, rmBODY, s->m_Body);
    wxDateTime dt = s->m_DateTime;
    m_lSights->SetItem(idx, rmTIME, dt.FormatISODate() + _T(" ") + dt.FormatISOTime());
    m_lSights->SetItem(idx, rmMEASUREMENT, wxString::Format(_T("%.4f"), s->m_Measurement));
    if(s->m_Type == Sight::LUNAR)
        m_lSights->SetItem(idx, rmCOLOR, _("Time Correction") +
                           wxString::Format(_T(": %.4f"), s->m_TimeCorrection));
    else
        m_lSights->SetItem(idx, rmCOLOR, s->m_ColourName);

    m_lSights->SetColumnWidth(rmTYPE, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmBODY, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmTIME, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(rmCOLOR, wxLIST_AUTOSIZE);

    if(m_lSights->GetColumnWidth(1) < 20)
        m_lSights->SetColumnWidth(1, 50);

    if(m_lSights->GetColumnWidth(2) < 20)
        m_lSights->SetColumnWidth(2, 50);

    m_lSights->SortItems(SortSights, (long)m_lSights);

    UpdateButtons();
    UpdateFix(warnings);
}

void CelestialNavigationDialog::UpdateSights()
{
    for(int i = 0; i<m_lSights->GetItemCount(); i++)
        UpdateSight(i);
}

void CelestialNavigationDialog::UpdateButtons()
{
    // enable/disable buttons
    long selected_index_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    bool enable = !(selected_index_index < 0);

    m_bEditSight->Enable(enable);
    m_bDeleteSight->Enable(enable);
    m_bDeleteAllSights->Enable(m_lSights->GetItemCount() > 0);
    m_bDeleteSight->Enable(enable);
}

void CelestialNavigationDialog::UpdateFix(bool warnings)
{
    m_FixDialog.Update(m_ClockCorrectionDialog.m_sClockCorrection->GetValue(), warnings);
}

void CelestialNavigationDialog::OnNew(wxCommandEvent &event)
{
    wxDateTime now = wxDateTime::Now().ToUTC();

    Sight s(Sight::ALTITUDE, _("Sun"), Sight::LOWER, now, 0, 0, 10);
    SightDialog dialog(GetParent(), s, m_ClockCorrectionDialog.m_sClockCorrection->GetValue());

    if( dialog.ShowModal() == wxID_OK ) {
        Sight *ns = new Sight(s);

        dialog.Recompute();
        ns->RebuildPolygons();
        InsertSight(ns);
        RequestRefresh( GetParent() );
    }
}

void CelestialNavigationDialog::OnDuplicate(wxCommandEvent &event)
{
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;

    Sight *psight = (Sight*)wxUIntToPtr(m_lSights->GetItemData(selected_index));
    Sight *ns = new Sight(*psight);
    ns->RebuildPolygons();
    InsertSight(ns);
    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnEdit( )
{
    // Manipulate selected_index sight/track
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;

    Sight *psight = (Sight*)wxUIntToPtr(m_lSights->GetItemData(selected_index));
    Sight originalsight = *psight; /* in case of cancel */

    SightDialog dialog(GetParent(), *psight, m_ClockCorrectionDialog.m_sClockCorrection->GetValue());

    if( dialog.ShowModal() == wxID_OK ) {
        dialog.Recompute();
        psight->RebuildPolygons();
        UpdateSight(selected_index);
    } else
        *psight = originalsight;

    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnDelete(wxCommandEvent &event)
{
    // Delete selected_index sight/track
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;

    m_lSights->DeleteItem(selected_index);
    RequestRefresh( GetParent() );
}

void CelestialNavigationDialog::OnDeleteAll(wxCommandEvent &event)
{
    wxMessageDialog mdlg(this, _("Are you sure you want to delete all sights?"),
                         _("Celestial Navigation"), wxYES_NO);
    if(mdlg.ShowModal() == wxID_YES) {
        m_lSights->DeleteAllItems();
        RequestRefresh( GetParent() );
    }
}

void CelestialNavigationDialog::OnFix( wxCommandEvent& event )
{
    m_FixDialog.Show();
}

void CelestialNavigationDialog::OnDRShift( wxCommandEvent& event )
{
    #if 0
    DRShiftDialog dialog;
    if(dialog.ShowModel() == wxID_OK) {
        double shiftnm, shiftbearing;
        dialog.m_tShiftNm->GetValue().ToDouble(&shiftnm);
        dialog.m_tShiftBearing->GetValue().ToDouble(&shiftbearing);
        bool MagneticShiftBearing = dialog.m_cbMagneticShiftBearing->GetValue();

        for (std::list<Sight*>::iterator it = m_SightList.begin(); it != m_SightList.end(); it++) {
            Sight *s = *it;
            if(!s->IsVisible())
                continue;

            if(s->m_bMagneticShiftBearing != MagneticShiftBearing
        }
    }
        #endif
}

void CelestialNavigationDialog::OnClockOffset( wxCommandEvent& event )
{
    m_ClockCorrectionDialog.Show();
}

//void CelestialNavigationDialog::OnInformation( wxCommandEvent& event )
//{
//    wxString infolocation = *GetpSharedDataLocation()
//        + _T("plugins/celestial_navigation_pi/data/")
//        + _("Celestial_Navigation_Information.html");
//    wxLaunchDefaultBrowser(_T("file://") + infolocation);
//}

    void CelestialNavigationDialog::OnInformation( wxCommandEvent& event )
{
    wxString infolocation =GetPluginDataDir("celestial_navigation_pi")
       + _T("/data/")
       + _("Celestial_Navigation_Information.html");
    wxLaunchDefaultBrowser(_T("file://") + infolocation);
}


void CelestialNavigationDialog::OnHide( wxCommandEvent& event )
{
    m_tbHide->SetLabel(m_tbHide->GetValue() ? _("Show") : _("Hide"));
    SetSize(m_tbHide->GetValue() ? 100 : 500, GetSize().y);
}

void CelestialNavigationDialog::OnSightListLeftDown(wxMouseEvent &event)
{
    wxPoint pos = event.GetPosition();
    int flags = 0;
    long clicked_index = m_lSights->HitTest(pos, flags);

    //    Clicking Visibility column?
    if (clicked_index > -1 && event.GetX() < m_lSights->GetColumnWidth(0))
    {
        // Process the clicked item
        Sight *sight = (Sight*)wxUIntToPtr(m_lSights->GetItemData(clicked_index));
        sight->SetVisible(!sight->IsVisible());
        m_lSights->SetItemImage(clicked_index, sight->IsVisible() ? 0 : -1);

        UpdateFix();
        RequestRefresh( GetParent() );
    }

    // Allow wx to process...
    event.Skip();
}

void CelestialNavigationDialog::OnSightSelected(wxListEvent &event)
{
    UpdateButtons();
}
