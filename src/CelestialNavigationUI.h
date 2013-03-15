///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#ifndef __CELESTIALNAVIGATIONUI_H__
#define __CELESTIALNAVIGATIONUI_H__

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/string.h>
#include <wx/stattext.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/spinctrl.h>
#include <wx/combobox.h>
#include <wx/sizer.h>
#include <wx/statbox.h>
#include <wx/listctrl.h>
#include <wx/button.h>
#include <wx/dialog.h>
#include <wx/choice.h>
#include <wx/checkbox.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/calctrl.h>
#include <wx/slider.h>
#include <wx/clrpicker.h>
#include <wx/notebook.h>
#include <wx/html/htmlwin.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class CelestialNavigationDialogBase
///////////////////////////////////////////////////////////////////////////////
class CelestialNavigationDialogBase : public wxDialog 
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
		wxListCtrl* m_lSights;
		wxButton* m_bNewSight;
		wxButton* m_bEditSight;
		wxButton* m_bDeleteSight;
		wxButton* m_bDeleteAllSights;
		wxButton* m_bInformation;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdateFix( wxSpinEvent& event ) { event.Skip(); }
		virtual void OnUpdateFix( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnSightListLeftDown( wxMouseEvent& event ) { event.Skip(); }
		virtual void OnSightSelected( wxListEvent& event ) { event.Skip(); }
		virtual void OnNew( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnEdit( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDelete( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDeleteAll( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnInformation( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		CelestialNavigationDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Celestial Navigation Sights"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
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
		wxSpinCtrl* m_sEyeHeight;
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
		virtual void OnFindBody( wxCommandEvent& event ) { event.Skip(); }
		virtual void Recompute( wxCalendarEvent& event ) { event.Skip(); }
		virtual void Recompute( wxSpinEvent& event ) { event.Skip(); }
		virtual void Recompute( wxScrollEvent& event ) { event.Skip(); }
		virtual void Recompute( wxColourPickerEvent& event ) { event.Skip(); }
		virtual void OnSetDefaults( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		SightDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Sight Properties"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE|wxRESIZE_BORDER ); 
		~SightDialogBase();
	
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
		wxStaticText* m_stAltitude;
		wxStaticText* m_stAzimuth;
		wxButton* m_bDone;
		wxCheckBox* m_cbMagneticAzimuth;
		
		// Virtual event handlers, overide them in your derived class
		virtual void OnUpdate( wxCommandEvent& event ) { event.Skip(); }
		virtual void OnDone( wxCommandEvent& event ) { event.Skip(); }
		
	
	public:
		
		FindBodyDialogBase( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Find Celestial Body"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE ); 
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

#endif //__CELESTIALNAVIGATIONUI_H__
