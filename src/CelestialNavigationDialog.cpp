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
#include <wx/wxprec.h>

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/imaglist.h>

#include <iostream>

#include "../../../include/ocpn_plugin.h"

#include "Sight.h"
#include "SightDialog.h"
#include "CelestialNavigationDialog.h"

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
    : CelestialNavigationDialogBase(parent)
{

      // create a image list for the list with just the eye icon
      wxImageList *imglist = new wxImageList(20, 20, true, 1);
      imglist->Add(wxBitmap(eye));
      m_lSights->AssignImageList(imglist, wxIMAGE_LIST_SMALL);

      m_lSights->InsertColumn(rmVISIBLE, wxT(""));
      m_lSights->SetColumnWidth(0, 28);

      m_lSights->InsertColumn(rmTYPE, _("Type"));
      m_lSights->InsertColumn(rmBODY, _("Body"));
      m_lSights->InsertColumn(rmTIME, _("Time"));
      m_lSights->InsertColumn(rmMEASUREMENT, _("Measurement"));
      m_lSights->InsertColumn(rmCOLOR, _("Color"));

      UpdateSights();
}

CelestialNavigationDialog::~CelestialNavigationDialog()
{
}

void CelestialNavigationDialog::UpdateSights()
{
    // if an item was selected, make it selected again if it still exist
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    long selected_id = -1;
    if (selected_index > -1)
        selected_id = m_lSights->GetItemData(selected_index);

    // Delete existing items
    m_lSights->DeleteAllItems();

    // then add sights to the listctrl
    SightList::iterator it;
    wxListItem item;
    int index = 0;

    for (it = m_SightList.begin(); it != m_SightList.end(); ++it, ++index)
    {
        item.SetId(index);
        item.SetImage((*it)->IsVisible() ? 0 : -1);
        item.SetData(index);
        
        long idx = m_lSights->InsertItem(item);
        m_lSights->SetItemImage(index, (*it)->IsVisible() ? 0 : -1);
        m_lSights->SetItem(idx, rmTYPE, (*it)->m_Type ? _("Azimuth") : _("Altitude"));
        m_lSights->SetItem(idx, rmBODY, (*it)->m_Body);
        m_lSights->SetItem(idx, rmTIME, (*it)->m_DateTime.Format());
        m_lSights->SetItem(idx, rmMEASUREMENT, wxString::Format(_T("%f"), (*it)->m_Measurement));
        
        m_lSights->SetItem(idx, rmCOLOR,
                           wxString::Format(_T("0x%llx%llx%llx"),
                                            (*it)->m_Colour.Red(),
                                            (*it)->m_Colour.Green(),
                                            (*it)->m_Colour.Blue()));
    }
    
    m_lSights->SetColumnWidth(1, wxLIST_AUTOSIZE);
    m_lSights->SetColumnWidth(2, wxLIST_AUTOSIZE);
    
    if(m_lSights->GetColumnWidth(1) < 20)
        m_lSights->SetColumnWidth(1, 50);

    if(m_lSights->GetColumnWidth(2) < 20)
        m_lSights->SetColumnWidth(2, 50);
    
    m_lSights->SortItems(SortSights, (long)m_lSights);
    
    // restore selection if possible
    // NOTE this will select a different item, if one is deleted
    // (the next sight will get that index).
    if (selected_id > -1)
    {
        selected_index = m_lSights->FindItem(-1, selected_id);
        m_lSights->SetItemState(selected_index, wxLIST_STATE_SELECTED, wxLIST_STATE_SELECTED);
    }
    
    UpdateButtons();
}

void CelestialNavigationDialog::UpdateButtons()
{
      // enable/disable buttons
      long selected_index_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      bool enable = !(selected_index_index < 0);

      m_bWarpSight->Enable(enable);
      m_bEditSight->Enable(enable);
      m_bDeleteSight->Enable(enable);
      m_bDeleteAllSights->Enable(m_SightList.GetCount() > 0);
}

void CelestialNavigationDialog::MakeAllSightsInvisible()
{
      SightList::iterator it;
      long index = 0;
      for (it = m_SightList.begin(); it != m_SightList.end(); ++it, ++index)
      {
            if ((*it)->IsVisible()) { // avoid config updating as much as possible!
                  (*it)->SetVisible(false);
                  m_lSights->SetItemImage(m_lSights->FindItem(-1, index), -1);
            }
      }
}

void CelestialNavigationDialog::OnNew(wxCommandEvent &event)
{
    wxDateTime now = wxDateTime::Now();
    now.MakeUTC();

    Sight s(Sight::ALTITUDE, _("Sun"), Sight::LOWER, now, 1, 0, 1);
    SightDialog dialog(GetParent(), s);
      
    if( dialog.ShowModal() == wxID_OK ) {
        Sight *ns = new Sight(s);

        dialog.RecomputeSight();
        ns->RebuildPolygons();
        m_SightList.Append(ns);
        UpdateSights();
    }
}

void CelestialNavigationDialog::OnWarp(wxCommandEvent &event)
{
      long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (selected_index < 0) return;

      Sight *psight = m_SightList.Item(m_lSights->GetItemData(selected_index))->GetData();
      double lat, lon, rad;
      psight->BodyLocation(psight->m_DateTime, lat, lon, rad);
      /* not fully implemented */
}

void CelestialNavigationDialog::OnEdit(wxCommandEvent &event)
{
    // Manipulate selected_index sight/track
    long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
    if (selected_index < 0) return;

    Sight *psight = m_SightList.Item(m_lSights->GetItemData(selected_index))->GetData();
    Sight originalsight = *psight; /* in case of cancel */
    
    SightDialog dialog(GetParent(), *psight);
    
    if( dialog.ShowModal() == wxID_OK ) {
        psight->RebuildPolygons();
        UpdateSights();
    } else
        *psight = originalsight;
}

void CelestialNavigationDialog::OnDelete(wxCommandEvent &event)
{
      // Delete selected_index sight/track
      long selected_index = m_lSights->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
      if (selected_index < 0) return;

      Sight *psight_to_delete = m_SightList.Item(m_lSights->GetItemData(selected_index))->GetData();
      m_SightList.DeleteObject(psight_to_delete);

      UpdateSights();
      Refresh();
}
 
void CelestialNavigationDialog::OnDeleteAllSights(wxCommandEvent &event)
{
     wxMessageDialog mdlg(this, _("Are you sure you want to delete <ALL> sights?"),
                          wxString(_("OpenCPN Alert"), wxYES_NO));

      m_SightList.Clear();

      UpdateSights();
      Refresh();
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
            Sight *sight = m_SightList.Item(m_lSights->GetItemData(clicked_index))->GetData();
            sight->SetVisible(!sight->IsVisible());
            m_lSights->SetItemImage(clicked_index, sight->IsVisible() ? 0 : -1);

            Refresh();
      }

      // Allow wx to process...
      event.Skip();
}

void CelestialNavigationDialog::OnSightSelected(wxListEvent &event)
{
    long clicked_index = event.m_itemIndex;
    // Process the clicked item
    Sight *sight = m_SightList.Item(m_lSights->GetItemData(clicked_index))->GetData();
    m_lSights->SetItemImage(clicked_index, sight->IsVisible() ? 0 : -1);
    Refresh();

    UpdateButtons();
}
/*
void CelestialNavigationDialog::OnUpdateAllSightsTimeOffset(wxSpinEvent &event)
{
    SightList::iterator it;
    for (it = m_SightList.begin(); it != m_SightList.end(); ++it)
       (*it)->RebuildPolygons(spinSightTimeOffset->GetValue());

    Refresh();
}
*/

