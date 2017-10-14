///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Jul 25 2017)
// http://www.wxformbuilder.org/
//
// PLEASE DO "NOT" EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "CelestialNavigationUI.h"

///////////////////////////////////////////////////////////////////////////

CelestialNavigationDialogBase::CelestialNavigationDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer25;
	fgSizer25 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer25->AddGrowableCol( 0 );
	fgSizer25->AddGrowableRow( 0 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer17;
	fgSizer17 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer17->AddGrowableCol( 0 );
	fgSizer17->AddGrowableRow( 0 );
	fgSizer17->SetFlexibleDirection( wxBOTH );
	fgSizer17->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lSights = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( -1,-1 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING );
	m_lSights->SetMinSize( wxSize( 0,-1 ) );
	
	fgSizer17->Add( m_lSights, 0, wxALL|wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_bNewSight = new wxButton( this, wxID_ANY, _("New"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bNewSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bEditSight = new wxButton( this, wxID_ANY, _("Edit"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bEditSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bDeleteSight = new wxButton( this, wxID_ANY, _("Delete"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bDeleteSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bDeleteAllSights = new wxButton( this, wxID_ANY, _("Delete All"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bDeleteAllSights, 0, wxALL|wxEXPAND, 5 );
	
	m_bFix = new wxButton( this, wxID_ANY, _("Fix"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bFix, 0, wxALL|wxEXPAND, 5 );
	
	m_bClockOffset = new wxButton( this, wxID_ANY, _("Clock Offset"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bClockOffset, 0, wxALL|wxEXPAND, 5 );
	
	m_tbHide = new wxToggleButton( this, wxID_ANY, _("Hide"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_tbHide, 0, wxALL|wxEXPAND, 5 );
	
	m_bInformation = new wxButton( this, wxID_ANY, _("Information"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bInformation, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer17->Add( fgSizer24, 1, wxEXPAND, 5 );
	
	
	fgSizer25->Add( fgSizer17, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer25 );
	this->Layout();
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_lSights->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CelestialNavigationDialogBase::OnEditMouse ), NULL, this );
	m_lSights->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CelestialNavigationDialogBase::OnSightListLeftDown ), NULL, this );
	m_lSights->Connect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_lSights->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_bNewSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnNew ), NULL, this );
	m_bEditSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnEdit ), NULL, this );
	m_bDeleteSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDelete ), NULL, this );
	m_bDeleteAllSights->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDeleteAll ), NULL, this );
	m_bFix->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnFix ), NULL, this );
	m_bClockOffset->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnClockOffset ), NULL, this );
	m_tbHide->Connect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnHide ), NULL, this );
	m_bInformation->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnInformation ), NULL, this );
}

CelestialNavigationDialogBase::~CelestialNavigationDialogBase()
{
	// Disconnect Events
	m_lSights->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( CelestialNavigationDialogBase::OnEditMouse ), NULL, this );
	m_lSights->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CelestialNavigationDialogBase::OnSightListLeftDown ), NULL, this );
	m_lSights->Disconnect( wxEVT_COMMAND_LIST_ITEM_DESELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_lSights->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_bNewSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnNew ), NULL, this );
	m_bEditSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnEdit ), NULL, this );
	m_bDeleteSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDelete ), NULL, this );
	m_bDeleteAllSights->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDeleteAll ), NULL, this );
	m_bFix->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnFix ), NULL, this );
	m_bClockOffset->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnClockOffset ), NULL, this );
	m_tbHide->Disconnect( wxEVT_COMMAND_TOGGLEBUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnHide ), NULL, this );
	m_bInformation->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnInformation ), NULL, this );
	
}

SightDialogBase::SightDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer1;
	fgSizer1 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer1->AddGrowableCol( 0 );
	fgSizer1->AddGrowableRow( 0 );
	fgSizer1->SetFlexibleDirection( wxBOTH );
	fgSizer1->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_notebook1 = new wxNotebook( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0 );
	m_panel1 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer5;
	fgSizer5 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer5->SetFlexibleDirection( wxBOTH );
	fgSizer5->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer3->SetFlexibleDirection( wxBOTH );
	fgSizer3->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, _("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALL, 5 );
	
	wxString m_cTypeChoices[] = { _("Altitude"), _("Azimuth"), _("Lunar") };
	int m_cTypeNChoices = sizeof( m_cTypeChoices ) / sizeof( wxString );
	m_cType = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cTypeNChoices, m_cTypeChoices, 0 );
	m_cType->SetSelection( 0 );
	fgSizer3->Add( m_cType, 0, wxALL, 5 );
	
	m_cbMagneticAzimuth = new wxCheckBox( m_panel1, wxID_ANY, _("Magnetic Azimuth"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_cbMagneticAzimuth, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, _("Celestial Body"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL, 5 );
	
	wxArrayString m_cBodyChoices;
	m_cBody = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cBodyChoices, 0 );
	m_cBody->SetSelection( 0 );
	fgSizer3->Add( m_cBody, 0, wxALL, 5 );
	
	m_bFindBody = new wxButton( m_panel1, wxID_ANY, _("Find"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_bFindBody, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, _("Limb"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL, 5 );
	
	wxString m_cLimbChoices[] = { _("Lower"), _("Center"), _("Upper") };
	int m_cLimbNChoices = sizeof( m_cLimbChoices ) / sizeof( wxString );
	m_cLimb = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cLimbNChoices, m_cLimbChoices, 0 );
	m_cLimb->SetSelection( 0 );
	fgSizer3->Add( m_cLimb, 0, wxALL, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer5->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	wxFlexGridSizer* fgSizer22;
	fgSizer22 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer22->SetFlexibleDirection( wxBOTH );
	fgSizer22->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, _("Measurement") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_tMeasurement = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_tMeasurement, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel1, wxID_ANY, _("Degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer4->Add( m_staticText6, 0, wxALL, 5 );
	
	m_tMeasurementMinutes = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_tMeasurementMinutes, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel1, wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer4->Add( m_staticText7, 0, wxALL, 5 );
	
	m_tMeasurementCertainty = new wxTextCtrl( m_panel1, wxID_ANY, _("10"), wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER );
	fgSizer4->Add( m_tMeasurementCertainty, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( m_panel1, wxID_ANY, _("Minutes Certainty"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer4->Add( m_staticText8, 0, wxALL, 5 );
	
	
	sbSizer1->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	
	fgSizer22->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	m_fgSizerLunar = new wxFlexGridSizer( 0, 2, 0, 0 );
	m_fgSizerLunar->SetFlexibleDirection( wxBOTH );
	m_fgSizerLunar->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText37 = new wxStaticText( m_panel1, wxID_ANY, _("Lunar Altitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText37->Wrap( -1 );
	m_staticText37->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_INFOTEXT ) );
	
	m_fgSizerLunar->Add( m_staticText37, 0, wxALL, 5 );
	
	m_tLunarMoonAltitude = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizerLunar->Add( m_tLunarMoonAltitude, 0, wxALL, 5 );
	
	m_staticText38 = new wxStaticText( m_panel1, wxID_ANY, _("Body Altitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText38->Wrap( -1 );
	m_fgSizerLunar->Add( m_staticText38, 0, wxALL, 5 );
	
	m_tLunarBodyAltitude = new wxTextCtrl( m_panel1, wxID_ANY, _("0"), wxDefaultPosition, wxDefaultSize, 0 );
	m_fgSizerLunar->Add( m_tLunarBodyAltitude, 0, wxALL, 5 );
	
	
	fgSizer22->Add( m_fgSizerLunar, 1, wxEXPAND, 5 );
	
	
	fgSizer5->Add( fgSizer22, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( fgSizer5 );
	m_panel1->Layout();
	fgSizer5->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, _("Sight"), true );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer19;
	fgSizer19 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer19->SetFlexibleDirection( wxBOTH );
	fgSizer19->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_Calendar = new wxCalendarCtrl( m_panel2, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer19->Add( m_Calendar, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer10;
	fgSizer10 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer10->SetFlexibleDirection( wxBOTH );
	fgSizer10->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer9;
	fgSizer9 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer9->SetFlexibleDirection( wxBOTH );
	fgSizer9->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_sHours = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 23, 0 );
	fgSizer9->Add( m_sHours, 0, wxALL, 5 );
	
	m_staticText9 = new wxStaticText( m_panel2, wxID_ANY, _("Hours"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer9->Add( m_staticText9, 0, wxALL, 5 );
	
	m_sMinutes = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	fgSizer9->Add( m_sMinutes, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel2, wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer9->Add( m_staticText10, 0, wxALL, 5 );
	
	m_sSeconds = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	fgSizer9->Add( m_sSeconds, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( m_panel2, wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer9->Add( m_staticText11, 0, wxALL, 5 );
	
	
	fgSizer10->Add( fgSizer9, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, _("Certainty") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_sCertaintySeconds = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 3 );
	fgSizer12->Add( m_sCertaintySeconds, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel2, wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer12->Add( m_staticText13, 0, wxALL, 5 );
	
	
	sbSizer2->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	
	fgSizer10->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer19->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( fgSizer19, 1, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( fgSizer8 );
	m_panel2->Layout();
	fgSizer8->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, _("Time"), false );
	m_panel6 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText211 = new wxStaticText( m_panel6, wxID_ANY, _("Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer18->Add( m_staticText211, 0, wxALL, 5 );
	
	m_tShiftNm = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_tShiftNm, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel6, wxID_ANY, _("Nm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer18->Add( m_staticText23, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( m_panel6, wxID_ANY, _("Bearing"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer18->Add( m_staticText24, 0, wxALL, 5 );
	
	m_tShiftBearing = new wxTextCtrl( m_panel6, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_tShiftBearing, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( m_panel6, wxID_ANY, _("Degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer18->Add( m_staticText25, 0, wxALL, 5 );
	
	m_cbMagneticShiftBearing = new wxCheckBox( m_panel6, wxID_ANY, _("Magnetic Bearing"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_cbMagneticShiftBearing, 0, wxALL, 5 );
	
	
	m_panel6->SetSizer( fgSizer18 );
	m_panel6->Layout();
	fgSizer18->Fit( m_panel6 );
	m_notebook1->AddPage( m_panel6, _("DR Shift"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText14 = new wxStaticText( m_panel3, wxID_ANY, _("Transparency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer14->Add( m_staticText14, 0, wxALL, 5 );
	
	m_sTransparency = new wxSlider( m_panel3, wxID_ANY, 50, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_INVERSE );
	fgSizer14->Add( m_sTransparency, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText18 = new wxStaticText( m_panel3, wxID_ANY, _("Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer14->Add( m_staticText18, 0, wxALL, 5 );
	
	m_ColourPicker = new wxColourPickerCtrl( m_panel3, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer14->Add( m_ColourPicker, 0, wxALL, 5 );
	
	
	m_panel3->SetSizer( fgSizer14 );
	m_panel3->Layout();
	fgSizer14->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, _("Config"), false );
	m_panel8 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( m_panel8, wxID_ANY, _("Eye Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer13->Add( m_staticText15, 0, wxALL, 5 );
	
	m_tEyeHeight = new wxTextCtrl( m_panel8, wxID_ANY, _("2"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer13->Add( m_tEyeHeight, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( m_panel8, wxID_ANY, _("Meters"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer13->Add( m_staticText16, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( m_panel8, wxID_ANY, _("Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer13->Add( m_staticText17, 0, wxALL, 5 );
	
	m_sTemperature = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -100, 100, 20 );
	fgSizer13->Add( m_sTemperature, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( m_panel8, wxID_ANY, _("Celcius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer13->Add( m_staticText19, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( m_panel8, wxID_ANY, _("Pressure"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer13->Add( m_staticText20, 0, wxALL, 5 );
	
	m_sPressure = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 2000, 1000 );
	fgSizer13->Add( m_sPressure, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( m_panel8, wxID_ANY, _("MilliBars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer13->Add( m_staticText21, 0, wxALL, 5 );
	
	m_staticText30 = new wxStaticText( m_panel8, wxID_ANY, _("Index Error"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText30->Wrap( -1 );
	fgSizer13->Add( m_staticText30, 0, wxALL, 5 );
	
	m_tIndexError = new wxTextCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer13->Add( m_tIndexError, 0, wxALL, 5 );
	
	m_staticText31 = new wxStaticText( m_panel8, wxID_ANY, _("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText31->Wrap( -1 );
	fgSizer13->Add( m_staticText31, 0, wxALL, 5 );
	
	
	fgSizer21->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	m_bSetDefaults = new wxButton( m_panel8, wxID_ANY, _("Set As Defaults"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_bSetDefaults, 0, wxALL, 5 );
	
	
	m_panel8->SetSizer( fgSizer21 );
	m_panel8->Layout();
	fgSizer21->Fit( m_panel8 );
	m_notebook1->AddPage( m_panel8, _("Parameters"), false );
	m_panel81 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer211;
	fgSizer211 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer211->AddGrowableCol( 0 );
	fgSizer211->AddGrowableRow( 0 );
	fgSizer211->SetFlexibleDirection( wxBOTH );
	fgSizer211->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_tCalculations = new wxTextCtrl( m_panel81, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxHSCROLL|wxTE_MULTILINE|wxTE_READONLY );
	fgSizer211->Add( m_tCalculations, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel81->SetSizer( fgSizer211 );
	m_panel81->Layout();
	fgSizer211->Fit( m_panel81 );
	m_notebook1->AddPage( m_panel81, _("Calculations"), false );
	
	fgSizer1->Add( m_notebook1, 1, wxEXPAND | wxALL, 5 );
	
	m_sdbSizer1 = new wxStdDialogButtonSizer();
	m_sdbSizer1OK = new wxButton( this, wxID_OK );
	m_sdbSizer1->AddButton( m_sdbSizer1OK );
	m_sdbSizer1Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer1->AddButton( m_sdbSizer1Cancel );
	m_sdbSizer1->Realize();
	
	fgSizer1->Add( m_sdbSizer1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer1 );
	this->Layout();
	fgSizer1->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_cType->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticAzimuth->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cBody->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::NewBody ), NULL, this );
	m_bFindBody->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnFindBody ), NULL, this );
	m_cLimb->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SightDialogBase::MeasurementEntered ), NULL, this );
	m_tMeasurementMinutes->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementMinutes->Connect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SightDialogBase::MeasurementEntered ), NULL, this );
	m_tMeasurementCertainty->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_Calendar->Connect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( SightDialogBase::RecomputeCalendar ), NULL, this );
	m_sHours->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sMinutes->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sSeconds->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sCertaintySeconds->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_tShiftNm->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftBearing->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_ColourPicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SightDialogBase::RecomputeColor ), NULL, this );
	m_tEyeHeight->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTemperature->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sPressure->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_tIndexError->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bSetDefaults->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnSetDefaults ), NULL, this );
}

SightDialogBase::~SightDialogBase()
{
	// Disconnect Events
	m_cType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticAzimuth->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cBody->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::NewBody ), NULL, this );
	m_bFindBody->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnFindBody ), NULL, this );
	m_cLimb->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SightDialogBase::MeasurementEntered ), NULL, this );
	m_tMeasurementMinutes->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementMinutes->Disconnect( wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler( SightDialogBase::MeasurementEntered ), NULL, this );
	m_tMeasurementCertainty->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_Calendar->Disconnect( wxEVT_CALENDAR_SEL_CHANGED, wxCalendarEventHandler( SightDialogBase::RecomputeCalendar ), NULL, this );
	m_sHours->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sMinutes->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sSeconds->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sCertaintySeconds->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_tShiftNm->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftBearing->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SightDialogBase::RecomputeScroll ), NULL, this );
	m_ColourPicker->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SightDialogBase::RecomputeColor ), NULL, this );
	m_tEyeHeight->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTemperature->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_sPressure->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::RecomputeSpin ), NULL, this );
	m_tIndexError->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bSetDefaults->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnSetDefaults ), NULL, this );
	
}

DRShiftDialog::DRShiftDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer30;
	fgSizer30 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer30->SetFlexibleDirection( wxBOTH );
	fgSizer30->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText51 = new wxStaticText( this, wxID_ANY, _("Shift all visible Sights"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText51->Wrap( -1 );
	fgSizer30->Add( m_staticText51, 0, wxALL, 5 );
	
	wxFlexGridSizer* fgSizer18;
	fgSizer18 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer18->SetFlexibleDirection( wxBOTH );
	fgSizer18->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText211 = new wxStaticText( this, wxID_ANY, _("Distance"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer18->Add( m_staticText211, 0, wxALL, 5 );
	
	m_tShiftNm = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_tShiftNm, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( this, wxID_ANY, _("Nm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer18->Add( m_staticText23, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( this, wxID_ANY, _("Bearing"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer18->Add( m_staticText24, 0, wxALL, 5 );
	
	m_tShiftBearing = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_tShiftBearing, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( this, wxID_ANY, _("Degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer18->Add( m_staticText25, 0, wxALL, 5 );
	
	m_cbMagneticShiftBearing = new wxCheckBox( this, wxID_ANY, _("Magnetic Bearing"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer18->Add( m_cbMagneticShiftBearing, 0, wxALL, 5 );
	
	
	fgSizer30->Add( fgSizer18, 1, wxEXPAND, 5 );
	
	m_sdbSizer4 = new wxStdDialogButtonSizer();
	m_sdbSizer4OK = new wxButton( this, wxID_OK );
	m_sdbSizer4->AddButton( m_sdbSizer4OK );
	m_sdbSizer4Cancel = new wxButton( this, wxID_CANCEL );
	m_sdbSizer4->AddButton( m_sdbSizer4Cancel );
	m_sdbSizer4->Realize();
	
	fgSizer30->Add( m_sdbSizer4, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer30 );
	this->Layout();
	fgSizer30->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_tShiftNm->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
	m_tShiftBearing->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
}

DRShiftDialog::~DRShiftDialog()
{
	// Disconnect Events
	m_tShiftNm->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
	m_tShiftBearing->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( DRShiftDialog::Recompute ), NULL, this );
	
}

FindBodyDialogBase::FindBodyDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Latitude") ), wxVERTICAL );
	
	m_tLatitude = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_tLatitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Longitude") ), wxVERTICAL );
	
	m_tLongitude = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_tLongitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer7, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Altitude") ), wxVERTICAL );
	
	m_tAltitude = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer8->Add( m_tAltitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer8, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Azimuth") ), wxVERTICAL );
	
	m_tAzimuth = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY );
	sbSizer9->Add( m_tAzimuth, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer9, 1, wxEXPAND, 5 );
	
	m_cbBoatPosition = new wxCheckBox( this, wxID_ANY, _("Boat Position"), wxDefaultPosition, wxDefaultSize, 0 );
	m_cbBoatPosition->SetValue(true); 
	fgSizer24->Add( m_cbBoatPosition, 0, wxALL, 5 );
	
	m_cbMagneticAzimuth = new wxCheckBox( this, wxID_ANY, _("Magnetic"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_cbMagneticAzimuth, 0, wxALL, 5 );
	
	m_bDone = new wxButton( this, wxID_ANY, _("Done"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bDone, 0, wxALL, 5 );
	
	
	this->SetSizer( fgSizer24 );
	this->Layout();
	fgSizer24->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_tLatitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_tLongitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_cbMagneticAzimuth->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_bDone->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnDone ), NULL, this );
}

FindBodyDialogBase::~FindBodyDialogBase()
{
	// Disconnect Events
	m_tLatitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_tLongitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_cbMagneticAzimuth->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_bDone->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnDone ), NULL, this );
	
}

InformationDialog::InformationDialog( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer2111;
	fgSizer2111 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2111->AddGrowableCol( 0 );
	fgSizer2111->AddGrowableRow( 0 );
	fgSizer2111->SetFlexibleDirection( wxBOTH );
	fgSizer2111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_htmlInformation = new wxHtmlWindow( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	fgSizer2111->Add( m_htmlInformation, 0, wxALL|wxEXPAND, 5 );
	
	m_sdbSizer2 = new wxStdDialogButtonSizer();
	m_sdbSizer2OK = new wxButton( this, wxID_OK );
	m_sdbSizer2->AddButton( m_sdbSizer2OK );
	m_sdbSizer2->Realize();
	
	fgSizer2111->Add( m_sdbSizer2, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer2111 );
	this->Layout();
	
	this->Centre( wxBOTH );
}

InformationDialog::~InformationDialog()
{
}

FixDialogBase::FixDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Fix From Visible Sights") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer16;
	fgSizer16 = new wxFlexGridSizer( 0, 7, 0, 0 );
	fgSizer16->SetFlexibleDirection( wxBOTH );
	fgSizer16->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText26 = new wxStaticText( this, wxID_ANY, _("Latitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer16->Add( m_staticText26, 0, wxALL, 5 );
	
	m_stLatitude = new wxStaticText( this, wxID_ANY, _("       N/A       "), wxDefaultPosition, wxDefaultSize, 0 );
	m_stLatitude->Wrap( -1 );
	fgSizer16->Add( m_stLatitude, 0, wxALL, 5 );
	
	m_staticText28 = new wxStaticText( this, wxID_ANY, _("Longitude"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText28->Wrap( -1 );
	fgSizer16->Add( m_staticText28, 0, wxALL, 5 );
	
	m_stLongitude = new wxStaticText( this, wxID_ANY, _("          N/A          "), wxDefaultPosition, wxDefaultSize, 0 );
	m_stLongitude->Wrap( -1 );
	fgSizer16->Add( m_stLongitude, 0, wxALL, 5 );
	
	m_staticText32 = new wxStaticText( this, wxID_ANY, _("Error"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText32->Wrap( -1 );
	fgSizer16->Add( m_staticText32, 0, wxALL, 5 );
	
	m_stFixError = new wxStaticText( this, wxID_ANY, _("     N/A     "), wxDefaultPosition, wxDefaultSize, 0 );
	m_stFixError->Wrap( -1 );
	fgSizer16->Add( m_stFixError, 0, wxALL, 5 );
	
	
	fgSizer16->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText34 = new wxStaticText( this, wxID_ANY, _("Initial"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText34->Wrap( -1 );
	fgSizer16->Add( m_staticText34, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_sInitialLatitude = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, -90, 90, 0 );
	fgSizer16->Add( m_sInitialLatitude, 0, wxALL, 5 );
	
	m_staticText35 = new wxStaticText( this, wxID_ANY, _("Initial"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText35->Wrap( -1 );
	fgSizer16->Add( m_staticText35, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_sInitialLongitude = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 80,-1 ), wxSP_ARROW_KEYS, -180, 180, 0 );
	fgSizer16->Add( m_sInitialLongitude, 0, wxALL, 5 );
	
	m_staticText36 = new wxStaticText( this, wxID_ANY, _("Alg"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText36->Wrap( -1 );
	fgSizer16->Add( m_staticText36, 0, wxALIGN_CENTER|wxALL, 5 );
	
	m_cbFixAlgorithm = new wxComboBox( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxSize( 90,-1 ), 0, NULL, 0 );
	m_cbFixAlgorithm->Append( _("Plane") );
	m_cbFixAlgorithm->Append( _("Sphere") );
	m_cbFixAlgorithm->Append( _("Cone") );
	m_cbFixAlgorithm->Append( _("Cone 2") );
	m_cbFixAlgorithm->SetSelection( 1 );
	fgSizer16->Add( m_cbFixAlgorithm, 0, wxALL, 5 );
	
	m_bGo = new wxButton( this, wxID_ANY, _("Go"), wxDefaultPosition, wxSize( -1,-1 ), wxBU_EXACTFIT );
	m_bGo->Enable( false );
	
	fgSizer16->Add( m_bGo, 0, wxALL, 5 );
	
	
	sbSizer7->Add( fgSizer16, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( sbSizer7 );
	this->Layout();
	sbSizer7->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_sInitialLatitude->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FixDialogBase::OnUpdateSpin ), NULL, this );
	m_sInitialLongitude->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FixDialogBase::OnUpdateSpin ), NULL, this );
	m_cbFixAlgorithm->Connect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FixDialogBase::OnUpdate ), NULL, this );
	m_bGo->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FixDialogBase::OnGo ), NULL, this );
}

FixDialogBase::~FixDialogBase()
{
	// Disconnect Events
	m_sInitialLatitude->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FixDialogBase::OnUpdateSpin ), NULL, this );
	m_sInitialLongitude->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( FixDialogBase::OnUpdateSpin ), NULL, this );
	m_cbFixAlgorithm->Disconnect( wxEVT_COMMAND_COMBOBOX_SELECTED, wxCommandEventHandler( FixDialogBase::OnUpdate ), NULL, this );
	m_bGo->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FixDialogBase::OnGo ), NULL, this );
	
}

ClockCorrectionDialogBase::ClockCorrectionDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxStaticBoxSizer* sbSizer10;
	sbSizer10 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, _("Clock Correction") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer20;
	fgSizer20 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer20->SetFlexibleDirection( wxBOTH );
	fgSizer20->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_sClockCorrection = new wxSpinCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -10000, 10000, 0 );
	fgSizer20->Add( m_sClockCorrection, 0, wxALL, 5 );
	
	m_staticText361 = new wxStaticText( this, wxID_ANY, _("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText361->Wrap( -1 );
	fgSizer20->Add( m_staticText361, 0, wxALL, 5 );
	
	
	sbSizer10->Add( fgSizer20, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( sbSizer10 );
	this->Layout();
	sbSizer10->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_sClockCorrection->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ClockCorrectionDialogBase::OnUpdate ), NULL, this );
}

ClockCorrectionDialogBase::~ClockCorrectionDialogBase()
{
	// Disconnect Events
	m_sClockCorrection->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( ClockCorrectionDialogBase::OnUpdate ), NULL, this );
	
}
