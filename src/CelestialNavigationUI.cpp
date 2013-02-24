///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct  8 2012)
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
	fgSizer25 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer25->AddGrowableCol( 0 );
	fgSizer25->AddGrowableRow( 0 );
	fgSizer25->SetFlexibleDirection( wxBOTH );
	fgSizer25->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_lSights = new wxListCtrl( this, wxID_ANY, wxDefaultPosition, wxSize( 300,-1 ), wxLC_HRULES|wxLC_REPORT|wxLC_SINGLE_SEL|wxLC_SORT_ASCENDING );
	fgSizer25->Add( m_lSights, 0, wxALL|wxEXPAND, 5 );
	
	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxVERTICAL );
	
	m_bNewSight = new wxButton( this, wxID_ANY, wxT("New Sight"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bNewSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bWarpSight = new wxButton( this, wxID_ANY, wxT("Warp to Sight"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bWarpSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bEditSight = new wxButton( this, wxID_ANY, wxT("Edit Sight"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bEditSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bDeleteSight = new wxButton( this, wxID_ANY, wxT("Delete Sight"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bDeleteSight, 0, wxALL|wxEXPAND, 5 );
	
	m_bDeleteAllSights = new wxButton( this, wxID_ANY, wxT("Delete All Sights"), wxDefaultPosition, wxDefaultSize, 0 );
	bSizer1->Add( m_bDeleteAllSights, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer25->Add( bSizer1, 1, wxEXPAND, 5 );
	
	
	this->SetSizer( fgSizer25 );
	this->Layout();
	fgSizer25->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_lSights->Connect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CelestialNavigationDialogBase::OnSightListLeftDown ), NULL, this );
	m_lSights->Connect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_bNewSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnNew ), NULL, this );
	m_bWarpSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnWarp ), NULL, this );
	m_bEditSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnEdit ), NULL, this );
	m_bDeleteSight->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDelete ), NULL, this );
	m_bDeleteAllSights->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDeleteAllSights ), NULL, this );
}

CelestialNavigationDialogBase::~CelestialNavigationDialogBase()
{
	// Disconnect Events
	m_lSights->Disconnect( wxEVT_LEFT_DOWN, wxMouseEventHandler( CelestialNavigationDialogBase::OnSightListLeftDown ), NULL, this );
	m_lSights->Disconnect( wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler( CelestialNavigationDialogBase::OnSightSelected ), NULL, this );
	m_bNewSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnNew ), NULL, this );
	m_bWarpSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnWarp ), NULL, this );
	m_bEditSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnEdit ), NULL, this );
	m_bDeleteSight->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDelete ), NULL, this );
	m_bDeleteAllSights->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( CelestialNavigationDialogBase::OnDeleteAllSights ), NULL, this );
	
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
	
	m_staticText1 = new wxStaticText( m_panel1, wxID_ANY, wxT("Type"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText1->Wrap( -1 );
	fgSizer3->Add( m_staticText1, 0, wxALL, 5 );
	
	wxString m_cTypeChoices[] = { wxT("Altitude"), wxT("Azimuth") };
	int m_cTypeNChoices = sizeof( m_cTypeChoices ) / sizeof( wxString );
	m_cType = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cTypeNChoices, m_cTypeChoices, 0 );
	m_cType->SetSelection( 0 );
	fgSizer3->Add( m_cType, 0, wxALL, 5 );
	
	m_cbMagneticAzimuth = new wxCheckBox( m_panel1, wxID_ANY, wxT("Magnetic Azimuth"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_cbMagneticAzimuth, 0, wxALL, 5 );
	
	m_staticText2 = new wxStaticText( m_panel1, wxID_ANY, wxT("Celestial Body"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText2->Wrap( -1 );
	fgSizer3->Add( m_staticText2, 0, wxALL, 5 );
	
	wxArrayString m_cBodyChoices;
	m_cBody = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cBodyChoices, 0 );
	m_cBody->SetSelection( 0 );
	fgSizer3->Add( m_cBody, 0, wxALL, 5 );
	
	m_bFindBody = new wxButton( m_panel1, wxID_ANY, wxT("Find"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer3->Add( m_bFindBody, 0, wxALL, 5 );
	
	m_staticText3 = new wxStaticText( m_panel1, wxID_ANY, wxT("Limb"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText3->Wrap( -1 );
	fgSizer3->Add( m_staticText3, 0, wxALL, 5 );
	
	wxString m_cLimbChoices[] = { wxT("Lower"), wxT("Center"), wxT("Upper") };
	int m_cLimbNChoices = sizeof( m_cLimbChoices ) / sizeof( wxString );
	m_cLimb = new wxChoice( m_panel1, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_cLimbNChoices, m_cLimbChoices, 0 );
	m_cLimb->SetSelection( 0 );
	fgSizer3->Add( m_cLimb, 0, wxALL, 5 );
	
	
	fgSizer3->Add( 0, 0, 1, wxEXPAND, 5 );
	
	
	fgSizer5->Add( fgSizer3, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer1;
	sbSizer1 = new wxStaticBoxSizer( new wxStaticBox( m_panel1, wxID_ANY, wxT("Measurement") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer4;
	fgSizer4 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer4->SetFlexibleDirection( wxBOTH );
	fgSizer4->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_tMeasurement = new wxTextCtrl( m_panel1, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_tMeasurement, 0, wxALL, 5 );
	
	m_staticText6 = new wxStaticText( m_panel1, wxID_ANY, wxT("Degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText6->Wrap( -1 );
	fgSizer4->Add( m_staticText6, 0, wxALL, 5 );
	
	m_tMeasurementMinutes = new wxTextCtrl( m_panel1, wxID_ANY, wxT("0"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_tMeasurementMinutes, 0, wxALL, 5 );
	
	m_staticText7 = new wxStaticText( m_panel1, wxID_ANY, wxT("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText7->Wrap( -1 );
	fgSizer4->Add( m_staticText7, 0, wxALL, 5 );
	
	m_tMeasurementCertainty = new wxTextCtrl( m_panel1, wxID_ANY, wxT(".5"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer4->Add( m_tMeasurementCertainty, 0, wxALL, 5 );
	
	m_staticText8 = new wxStaticText( m_panel1, wxID_ANY, wxT("Degrees Certainty"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText8->Wrap( -1 );
	fgSizer4->Add( m_staticText8, 0, wxALL, 5 );
	
	
	sbSizer1->Add( fgSizer4, 1, wxEXPAND, 5 );
	
	
	fgSizer5->Add( sbSizer1, 1, wxEXPAND, 5 );
	
	
	m_panel1->SetSizer( fgSizer5 );
	m_panel1->Layout();
	fgSizer5->Fit( m_panel1 );
	m_notebook1->AddPage( m_panel1, wxT("Sight"), true );
	m_panel2 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer8;
	fgSizer8 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer8->SetFlexibleDirection( wxBOTH );
	fgSizer8->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_Calendar = new wxCalendarCtrl( m_panel2, wxID_ANY, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer8->Add( m_Calendar, 0, wxALL, 5 );
	
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
	
	m_staticText9 = new wxStaticText( m_panel2, wxID_ANY, wxT("Hours"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText9->Wrap( -1 );
	fgSizer9->Add( m_staticText9, 0, wxALL, 5 );
	
	m_sMinutes = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	fgSizer9->Add( m_sMinutes, 0, wxALL, 5 );
	
	m_staticText10 = new wxStaticText( m_panel2, wxID_ANY, wxT("Minutes"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText10->Wrap( -1 );
	fgSizer9->Add( m_staticText10, 0, wxALL, 5 );
	
	m_sSeconds = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 59, 0 );
	fgSizer9->Add( m_sSeconds, 0, wxALL, 5 );
	
	m_staticText11 = new wxStaticText( m_panel2, wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText11->Wrap( -1 );
	fgSizer9->Add( m_staticText11, 0, wxALL, 5 );
	
	
	fgSizer10->Add( fgSizer9, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer2;
	sbSizer2 = new wxStaticBoxSizer( new wxStaticBox( m_panel2, wxID_ANY, wxT("Certainty") ), wxVERTICAL );
	
	wxFlexGridSizer* fgSizer12;
	fgSizer12 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer12->SetFlexibleDirection( wxBOTH );
	fgSizer12->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_sCertaintySeconds = new wxSpinCtrl( m_panel2, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 3 );
	fgSizer12->Add( m_sCertaintySeconds, 0, wxALL, 5 );
	
	m_staticText13 = new wxStaticText( m_panel2, wxID_ANY, wxT("Seconds"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText13->Wrap( -1 );
	fgSizer12->Add( m_staticText13, 0, wxALL, 5 );
	
	
	sbSizer2->Add( fgSizer12, 1, wxEXPAND, 5 );
	
	
	fgSizer10->Add( sbSizer2, 1, wxEXPAND, 5 );
	
	
	fgSizer8->Add( fgSizer10, 1, wxEXPAND, 5 );
	
	
	m_panel2->SetSizer( fgSizer8 );
	m_panel2->Layout();
	fgSizer8->Fit( m_panel2 );
	m_notebook1->AddPage( m_panel2, wxT("Time"), false );
	m_panel3 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer14;
	fgSizer14 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer14->SetFlexibleDirection( wxBOTH );
	fgSizer14->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText14 = new wxStaticText( m_panel3, wxID_ANY, wxT("Transparency"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText14->Wrap( -1 );
	fgSizer14->Add( m_staticText14, 0, wxALL, 5 );
	
	m_sTransparency = new wxSlider( m_panel3, wxID_ANY, 50, 0, 255, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL|wxSL_INVERSE );
	fgSizer14->Add( m_sTransparency, 0, wxALL|wxEXPAND, 5 );
	
	
	fgSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText18 = new wxStaticText( m_panel3, wxID_ANY, wxT("Color"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText18->Wrap( -1 );
	fgSizer14->Add( m_staticText18, 0, wxALL, 5 );
	
	m_ColourPicker = new wxColourPickerCtrl( m_panel3, wxID_ANY, *wxBLACK, wxDefaultPosition, wxDefaultSize, wxCLRP_DEFAULT_STYLE );
	fgSizer14->Add( m_ColourPicker, 0, wxALL, 5 );
	
	
	fgSizer14->Add( 0, 0, 1, wxEXPAND, 5 );
	
	m_staticText211 = new wxStaticText( m_panel3, wxID_ANY, wxT("Shift Sights"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText211->Wrap( -1 );
	fgSizer14->Add( m_staticText211, 0, wxALL, 5 );
	
	m_tShiftNm = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_tShiftNm, 0, wxALL, 5 );
	
	m_staticText23 = new wxStaticText( m_panel3, wxID_ANY, wxT("Nm"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText23->Wrap( -1 );
	fgSizer14->Add( m_staticText23, 0, wxALL, 5 );
	
	m_staticText24 = new wxStaticText( m_panel3, wxID_ANY, wxT("On Bearing"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText24->Wrap( -1 );
	fgSizer14->Add( m_staticText24, 0, wxALL, 5 );
	
	m_tShiftBearing = new wxTextCtrl( m_panel3, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_tShiftBearing, 0, wxALL, 5 );
	
	m_staticText25 = new wxStaticText( m_panel3, wxID_ANY, wxT("Degrees"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText25->Wrap( -1 );
	fgSizer14->Add( m_staticText25, 0, wxALL, 5 );
	
	m_staticText26 = new wxStaticText( m_panel3, wxID_ANY, wxT("Bearing is"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText26->Wrap( -1 );
	fgSizer14->Add( m_staticText26, 0, wxALL, 5 );
	
	m_cbMagneticShiftBearing = new wxCheckBox( m_panel3, wxID_ANY, wxT("Magnetic"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer14->Add( m_cbMagneticShiftBearing, 0, wxALL, 5 );
	
	
	m_panel3->SetSizer( fgSizer14 );
	m_panel3->Layout();
	fgSizer14->Fit( m_panel3 );
	m_notebook1->AddPage( m_panel3, wxT("Config"), false );
	m_panel8 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer21;
	fgSizer21 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer21->SetFlexibleDirection( wxBOTH );
	fgSizer21->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxFlexGridSizer* fgSizer13;
	fgSizer13 = new wxFlexGridSizer( 0, 3, 0, 0 );
	fgSizer13->SetFlexibleDirection( wxBOTH );
	fgSizer13->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_staticText15 = new wxStaticText( m_panel8, wxID_ANY, wxT("Eye Height"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText15->Wrap( -1 );
	fgSizer13->Add( m_staticText15, 0, wxALL, 5 );
	
	m_sEyeHeight = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 0, 1000, 2 );
	fgSizer13->Add( m_sEyeHeight, 0, wxALL, 5 );
	
	m_staticText16 = new wxStaticText( m_panel8, wxID_ANY, wxT("Meters"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText16->Wrap( -1 );
	fgSizer13->Add( m_staticText16, 0, wxALL, 5 );
	
	m_staticText17 = new wxStaticText( m_panel8, wxID_ANY, wxT("Temperature"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText17->Wrap( -1 );
	fgSizer13->Add( m_staticText17, 0, wxALL, 5 );
	
	m_sTemperature = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, -100, 100, 20 );
	fgSizer13->Add( m_sTemperature, 0, wxALL, 5 );
	
	m_staticText19 = new wxStaticText( m_panel8, wxID_ANY, wxT("Celcius"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText19->Wrap( -1 );
	fgSizer13->Add( m_staticText19, 0, wxALL, 5 );
	
	m_staticText20 = new wxStaticText( m_panel8, wxID_ANY, wxT("Pressure"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText20->Wrap( -1 );
	fgSizer13->Add( m_staticText20, 0, wxALL, 5 );
	
	m_sPressure = new wxSpinCtrl( m_panel8, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxSP_ARROW_KEYS, 1, 2000, 1000 );
	fgSizer13->Add( m_sPressure, 0, wxALL, 5 );
	
	m_staticText21 = new wxStaticText( m_panel8, wxID_ANY, wxT("MilliBars"), wxDefaultPosition, wxDefaultSize, 0 );
	m_staticText21->Wrap( -1 );
	fgSizer13->Add( m_staticText21, 0, wxALL, 5 );
	
	
	fgSizer21->Add( fgSizer13, 1, wxEXPAND, 5 );
	
	m_bSetDefaults = new wxButton( m_panel8, wxID_ANY, wxT("Set As Defaults"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer21->Add( m_bSetDefaults, 0, wxALL, 5 );
	
	
	m_panel8->SetSizer( fgSizer21 );
	m_panel8->Layout();
	fgSizer21->Fit( m_panel8 );
	m_notebook1->AddPage( m_panel8, wxT("Parameters"), false );
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
	m_notebook1->AddPage( m_panel81, wxT("Calculations"), false );
	m_panel811 = new wxPanel( m_notebook1, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	wxFlexGridSizer* fgSizer2111;
	fgSizer2111 = new wxFlexGridSizer( 0, 1, 0, 0 );
	fgSizer2111->AddGrowableCol( 0 );
	fgSizer2111->AddGrowableRow( 0 );
	fgSizer2111->SetFlexibleDirection( wxBOTH );
	fgSizer2111->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	m_htmlInformation = new wxHtmlWindow( m_panel811, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxHW_SCROLLBAR_AUTO );
	fgSizer2111->Add( m_htmlInformation, 0, wxALL|wxEXPAND, 5 );
	
	
	m_panel811->SetSizer( fgSizer2111 );
	m_panel811->Layout();
	fgSizer2111->Fit( m_panel811 );
	m_notebook1->AddPage( m_panel811, wxT("Information"), false );
	
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
	m_cBody->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bFindBody->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnFindBody ), NULL, this );
	m_cLimb->Connect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementMinutes->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementCertainty->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_Calendar->Connect( wxEVT_CALENDAR_DOUBLECLICKED, wxCalendarEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sHours->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sMinutes->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sSeconds->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sCertaintySeconds->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_ColourPicker->Connect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftNm->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftBearing->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sEyeHeight->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTemperature->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sPressure->Connect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bSetDefaults->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnSetDefaults ), NULL, this );
}

SightDialogBase::~SightDialogBase()
{
	// Disconnect Events
	m_cType->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticAzimuth->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cBody->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bFindBody->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnFindBody ), NULL, this );
	m_cLimb->Disconnect( wxEVT_COMMAND_CHOICE_SELECTED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurement->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementMinutes->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tMeasurementCertainty->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_Calendar->Disconnect( wxEVT_CALENDAR_DOUBLECLICKED, wxCalendarEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sHours->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sMinutes->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sSeconds->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sCertaintySeconds->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTransparency->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_ColourPicker->Disconnect( wxEVT_COMMAND_COLOURPICKER_CHANGED, wxColourPickerEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftNm->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_tShiftBearing->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_cbMagneticShiftBearing->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sEyeHeight->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sTemperature->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_sPressure->Disconnect( wxEVT_COMMAND_SPINCTRL_UPDATED, wxSpinEventHandler( SightDialogBase::Recompute ), NULL, this );
	m_bSetDefaults->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( SightDialogBase::OnSetDefaults ), NULL, this );
	
}

FindBodyDialogBase::FindBodyDialogBase( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxDialog( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );
	
	wxFlexGridSizer* fgSizer24;
	fgSizer24 = new wxFlexGridSizer( 0, 2, 0, 0 );
	fgSizer24->SetFlexibleDirection( wxBOTH );
	fgSizer24->SetNonFlexibleGrowMode( wxFLEX_GROWMODE_SPECIFIED );
	
	wxStaticBoxSizer* sbSizer6;
	sbSizer6 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Latitude") ), wxVERTICAL );
	
	m_tLatitude = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer6->Add( m_tLatitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer6, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer7;
	sbSizer7 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Longitude") ), wxVERTICAL );
	
	m_tLongitude = new wxTextCtrl( this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, 0 );
	sbSizer7->Add( m_tLongitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer7, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer8;
	sbSizer8 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Altitude") ), wxVERTICAL );
	
	m_stAltitude = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAltitude->Wrap( -1 );
	sbSizer8->Add( m_stAltitude, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer8, 1, wxEXPAND, 5 );
	
	wxStaticBoxSizer* sbSizer9;
	sbSizer9 = new wxStaticBoxSizer( new wxStaticBox( this, wxID_ANY, wxT("Azimuth") ), wxVERTICAL );
	
	m_stAzimuth = new wxStaticText( this, wxID_ANY, wxT("MyLabel"), wxDefaultPosition, wxDefaultSize, 0 );
	m_stAzimuth->Wrap( -1 );
	sbSizer9->Add( m_stAzimuth, 0, wxALL, 5 );
	
	
	fgSizer24->Add( sbSizer9, 1, wxEXPAND, 5 );
	
	m_bDone = new wxButton( this, wxID_ANY, wxT("Done"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_bDone, 0, wxALL, 5 );
	
	m_cbMagneticAzimuth = new wxCheckBox( this, wxID_ANY, wxT("Magnetic"), wxDefaultPosition, wxDefaultSize, 0 );
	fgSizer24->Add( m_cbMagneticAzimuth, 0, wxALL, 5 );
	
	
	this->SetSizer( fgSizer24 );
	this->Layout();
	fgSizer24->Fit( this );
	
	this->Centre( wxBOTH );
	
	// Connect Events
	m_tLatitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_tLongitude->Connect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_bDone->Connect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnDone ), NULL, this );
	m_cbMagneticAzimuth->Connect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
}

FindBodyDialogBase::~FindBodyDialogBase()
{
	// Disconnect Events
	m_tLatitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_tLongitude->Disconnect( wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	m_bDone->Disconnect( wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnDone ), NULL, this );
	m_cbMagneticAzimuth->Disconnect( wxEVT_COMMAND_CHECKBOX_CLICKED, wxCommandEventHandler( FindBodyDialogBase::OnUpdate ), NULL, this );
	
}
