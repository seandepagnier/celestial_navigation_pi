///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Dec 20 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CELESTIALNAVIGATIONUI_H__
#define __CELESTIALNAVIGATIONUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/listctrl.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/button.h>
#include <wx/tglbtn.h>
#include <wx/sizer.h>
#include <wx/dialog.h>
#include <wx/stattext.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/statbox.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/calctrl.h>
#include <wx/spinctrl.h>
#include <wx/slider.h>
#include <wx/clrpicker.h>
#include <wx/notebook.h>
#include <wx/html/htmlwin.h>
#include <wx/combobox.h>

#include "wxWTranslateCatalog.h"

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CelestialNavigationDialogBase
///////////////////////////////////////////////////////////////////////////////
class CelestialNavigationDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxButton* m_bNewSight;
		wxButton* m_bFix;
		wxButton* m_bDuplicateSight;
		wxButton* m_bClockOffset;
		wxButton* m_bEditSight;
		wxToggleButton* m_tbHide;
		wxButton* m_bDeleteSight;
		wxButton* m_bInformation;
		wxButton* m_bDeleteAllSights;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnEditMouse( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSightListLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSightSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFix( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDuplicate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnClockOffset( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnHide( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInformation( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteAll( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxListCtrl* m_lSights;
		
		CelestialNavigationDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Celestial Navigation Sights"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 500,294 ), long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~CelestialNavigationDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class SightDialogBase
///////////////////////////////////////////////////////////////////////////////
class SightDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxNotebook* m_notebook1;
		wxPanel* m_panel1;
		wxStaticText* m_staticText1;
		wxChoice* m_cType;
		wxCheckBox* m_cbMagneticAzimuth;
		wxStaticText* m_staticText2;
		wxChoice* m_cBody;
		wxButton* m_bFindBody;
		wxStaticText* m_staticText3;
		wxChoice* m_cLimb;
		wxTextCtrl* m_tMeasurement;
		wxStaticText* m_staticText6;
		wxTextCtrl* m_tMeasurementMinutes;
		wxStaticText* m_staticText7;
		wxTextCtrl* m_tMeasurementCertainty;
		wxStaticText* m_staticText8;
		wxFlexGridSizer* m_fgSizerLunar;
		wxStaticText* m_staticText37;
		wxTextCtrl* m_tLunarMoonAltitude;
		wxStaticText* m_staticText38;
		wxTextCtrl* m_tLunarBodyAltitude;
		wxPanel* m_panel2;
		wxCalendarCtrl* m_Calendar;
		wxSpinCtrl* m_sHours;
		wxStaticText* m_staticText9;
		wxSpinCtrl* m_sMinutes;
		wxStaticText* m_staticText10;
		wxSpinCtrl* m_sSeconds;
		wxStaticText* m_staticText11;
		wxSpinCtrl* m_sCertaintySeconds;
		wxStaticText* m_staticText13;
		wxPanel* m_panel6;
		wxStaticText* m_staticText211;
		wxTextCtrl* m_tShiftNm;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxTextCtrl* m_tShiftBearing;
		wxStaticText* m_staticText25;
		wxCheckBox* m_cbMagneticShiftBearing;
		wxPanel* m_panel3;
		wxStaticText* m_staticText14;
		wxSlider* m_sTransparency;
		wxStaticText* m_staticText18;
		wxColourPickerCtrl* m_ColourPicker;
		wxPanel* m_panel8;
		wxStaticText* m_staticText15;
		wxTextCtrl* m_tEyeHeight;
		wxStaticText* m_staticText16;
		wxStaticText* m_staticText17;
		wxSpinCtrl* m_sTemperature;
		wxStaticText* m_staticText19;
		wxStaticText* m_staticText20;
		wxSpinCtrl* m_sPressure;
		wxStaticText* m_staticText21;
		wxStaticText* m_staticText30;
		wxTextCtrl* m_tIndexError;
		wxStaticText* m_staticText31;
		wxButton* m_bSetDefaults;
		wxPanel* m_panel81;
		wxTextCtrl* m_tCalculations;
		wxStdDialogButtonSizer* m_sdbSizer1;
		wxButton* m_sdbSizer1OK;
		wxButton* m_sdbSizer1Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Recompute( wxCommandEvent& event ) { event.Skip(); }
		virtual void NewBody( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnFindBody( wxCommandEvent& event ) { event.Skip(); }
		virtual void MeasurementEntered( wxCommandEvent& event ) { event.Skip(); }
		virtual void RecomputeCalendar( wxCalendarEvent& event ) { event.Skip(); }
		virtual void RecomputeSpin( wxSpinEvent& event ) { event.Skip(); }
		virtual void RecomputeScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void RecomputeColor( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnSetDefaults( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SightDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Sight Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~SightDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class DRShiftDialog
///////////////////////////////////////////////////////////////////////////////
class DRShiftDialog : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText51;
		wxStaticText* m_staticText211;
		wxStaticText* m_staticText23;
		wxStaticText* m_staticText24;
		wxStaticText* m_staticText25;
		wxStdDialogButtonSizer* m_sdbSizer4;
		wxButton* m_sdbSizer4OK;
		wxButton* m_sdbSizer4Cancel;
		
		// Virtual event handlers, overide them in your derived class
		virtual void Recompute( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		wxTextCtrl* m_tShiftNm;
		wxTextCtrl* m_tShiftBearing;
		wxCheckBox* m_cbMagneticShiftBearing;
		
		DRShiftDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Dead Reckoning shift"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~DRShiftDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FindBodyDialogBase
///////////////////////////////////////////////////////////////////////////////
class FindBodyDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxTextCtrl* m_tLatitude;
		wxTextCtrl* m_tLongitude;
		wxTextCtrl* m_tAltitude;
		wxTextCtrl* m_tAzimuth;
		wxCheckBox* m_cbBoatPosition;
		wxCheckBox* m_cbMagneticAzimuth;
		wxButton* m_bDone;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDone( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FindBodyDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Find Celestial Body"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~FindBodyDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class InformationDialog
///////////////////////////////////////////////////////////////////////////////
class InformationDialog : public wxDialog 
{
	private:
	
	protected:
		wxStdDialogButtonSizer* m_sdbSizer2;
		wxButton* m_sdbSizer2OK;
	
	public:
		wxHtmlWindow* m_htmlInformation;
		
		InformationDialog( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 560,400 ), long style = wxDEFAULT_DIALOG_STYLE ); 
		~InformationDialog();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class FixDialogBase
///////////////////////////////////////////////////////////////////////////////
class FixDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText26;
		wxStaticText* m_stLatitude;
		wxStaticText* m_staticText28;
		wxStaticText* m_stLongitude;
		wxStaticText* m_staticText32;
		wxStaticText* m_stFixError;
		wxStaticText* m_staticText34;
		wxSpinCtrl* m_sInitialLatitude;
		wxStaticText* m_staticText35;
		wxSpinCtrl* m_sInitialLongitude;
		wxStaticText* m_staticText36;
		wxComboBox* m_cbFixAlgorithm;
		wxButton* m_bGo;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateSpin( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnGo( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FixDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Fix"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~FixDialogBase();
	
};

///////////////////////////////////////////////////////////////////////////////
/// Class ClockCorrectionDialogBase
///////////////////////////////////////////////////////////////////////////////
class ClockCorrectionDialogBase : public wxDialog 
{
	private:
	
	protected:
		wxStaticText* m_staticText361;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdate( wxSpinEvent& event ) { event.Skip(); }
		
	
	public:
		wxSpinCtrl* m_sClockCorrection;
		
		ClockCorrectionDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("Clock Correction"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
		~ClockCorrectionDialogBase();
	
};

#endif //__CELESTIALNAVIGATIONUI_H__
