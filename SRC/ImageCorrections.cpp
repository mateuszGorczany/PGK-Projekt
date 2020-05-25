///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "ImageCorrections.h"

///////////////////////////////////////////////////////////////////////////

Frame::Frame( wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style ) : wxFrame( parent, id, title, pos, size, style )
{
	this->SetSizeHints( wxDefaultSize, wxDefaultSize );

	wxBoxSizer* bSizer1;
	bSizer1 = new wxBoxSizer( wxHORIZONTAL );

	wxBoxSizer* bSizer3;
	bSizer3 = new wxBoxSizer( wxVERTICAL );

	m_Image_Box = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL );
	m_Image_Box->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_3DLIGHT ) );

	bSizer3->Add( m_Image_Box, 1, wxEXPAND | wxALL, 5 );


	bSizer1->Add( bSizer3, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer5;
	bSizer5 = new wxBoxSizer( wxVERTICAL );

	wxBoxSizer* bSizer6;
	bSizer6 = new wxBoxSizer( wxVERTICAL );

	m_Color_Hexagon_Box = new wxPanel( this, wxID_ANY, wxDefaultPosition, wxSize( 250,250 ), wxTAB_TRAVERSAL );
	m_Color_Hexagon_Box->SetBackgroundColour( wxSystemSettings::GetColour( wxSYS_COLOUR_APPWORKSPACE ) );

	bSizer6->Add( m_Color_Hexagon_Box, 1, wxALL|wxSHAPED, 5 );


	bSizer5->Add( bSizer6, 1, wxEXPAND, 5 );

	wxBoxSizer* bSizer7;
	bSizer7 = new wxBoxSizer( wxVERTICAL );

	wxString m_Chanel_choiceChoices[] = { wxT("Barwa"), wxT("Jasność"), wxT("Nasycenie"), wxEmptyString, wxEmptyString };
	int m_Chanel_choiceNChoices = sizeof( m_Chanel_choiceChoices ) / sizeof( wxString );
	m_Chanel_choice = new wxChoice( this, wxID_ANY, wxDefaultPosition, wxDefaultSize, m_Chanel_choiceNChoices, m_Chanel_choiceChoices, 0 );
	m_Chanel_choice->SetSelection( 0 );
	bSizer7->Add( m_Chanel_choice, 0, wxALIGN_CENTER|wxALL, 5 );

	m_StaticText_ChangeCoefficient = new wxStaticText( this, wxID_ANY, wxT("Współczynnik zmian"), wxDefaultPosition, wxDefaultSize, 0 );
	m_StaticText_ChangeCoefficient->Wrap( -1 );
	bSizer7->Add( m_StaticText_ChangeCoefficient, 0, wxALIGN_CENTER|wxALL, 5 );

	m_Slider_ChangeCoefficient = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer7->Add( m_Slider_ChangeCoefficient, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );

	m_StaticText_MixImages = new wxStaticText( this, wxID_ANY, wxT("Mieszanie obrazów"), wxDefaultPosition, wxDefaultSize, 0 );
	m_StaticText_MixImages->Wrap( -1 );
	bSizer7->Add( m_StaticText_MixImages, 0, wxALIGN_CENTER|wxALL, 5 );

	m_Slider_MixImages = new wxSlider( this, wxID_ANY, 50, 0, 100, wxDefaultPosition, wxDefaultSize, wxSL_HORIZONTAL );
	bSizer7->Add( m_Slider_MixImages, 0, wxALIGN_CENTER|wxALL|wxEXPAND, 5 );


	bSizer5->Add( bSizer7, 1, wxEXPAND, 5 );


	bSizer1->Add( bSizer5, 0, wxEXPAND, 5 );


	this->SetSizer( bSizer1 );
	this->Layout();
	m_menubar = new wxMenuBar( 0 );
	menu_File = new wxMenu();
	wxMenuItem* m_Menu_File_Open;
	m_Menu_File_Open = new wxMenuItem( menu_File, wxID_ANY, wxString( wxT("Otwórz") ) , wxEmptyString, wxITEM_NORMAL );
	menu_File->Append( m_Menu_File_Open );

	wxMenuItem* m_Menu_File_Save;
	m_Menu_File_Save = new wxMenuItem( menu_File, wxID_ANY, wxString( wxT("Zapisz jako...") ) , wxEmptyString, wxITEM_NORMAL );
	menu_File->Append( m_Menu_File_Save );

	menu_File->AppendSeparator();

	wxMenuItem* m_Menu_File_Exit;
	m_Menu_File_Exit = new wxMenuItem( menu_File, wxID_ANY, wxString( wxT("Wyjdź") ) , wxEmptyString, wxITEM_NORMAL );
	menu_File->Append( m_Menu_File_Exit );

	m_menubar->Append( menu_File, wxT("Plik") );

	menu_About = new wxMenu();
	wxMenuItem* m_Menu_About_Info;
	m_Menu_About_Info = new wxMenuItem( menu_About, wxID_ANY, wxString( wxT("Info") ) , wxEmptyString, wxITEM_NORMAL );
	menu_About->Append( m_Menu_About_Info );

	m_menubar->Append( menu_About, wxT("Pomoc") );

	this->SetMenuBar( m_menubar );


	this->Centre( wxBOTH );

	// Connect Events
	m_Image_Box->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Frame::image_BoxOnUpdateUI ), NULL, this );
	m_Color_Hexagon_Box->Connect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( Frame::color_Hexagon_BoxOnLeftDClick ), NULL, this );
	m_Chanel_choice->Connect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Frame::chanel_choiceOnUpdateUI ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Connect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	menu_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::menu_File_OpenOnMenuSelection ), this, m_Menu_File_Open->GetId());
	menu_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::menu_File_SaveOnMenuSelection ), this, m_Menu_File_Save->GetId());
	menu_File->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::menu_File_ExitOnMenuSelection ), this, m_Menu_File_Exit->GetId());
	menu_About->Bind(wxEVT_COMMAND_MENU_SELECTED, wxCommandEventHandler( Frame::menu_About_InfoOnMenuSelection ), this, m_Menu_About_Info->GetId());
}

Frame::~Frame()
{
	// Disconnect Events
	m_Image_Box->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Frame::image_BoxOnUpdateUI ), NULL, this );
	m_Color_Hexagon_Box->Disconnect( wxEVT_LEFT_DCLICK, wxMouseEventHandler( Frame::color_Hexagon_BoxOnLeftDClick ), NULL, this );
	m_Chanel_choice->Disconnect( wxEVT_UPDATE_UI, wxUpdateUIEventHandler( Frame::chanel_choiceOnUpdateUI ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_ChangeCoefficient->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::slider_ChangeCoefficientOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_TOP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_BOTTOM, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_LINEUP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_LINEDOWN, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_PAGEUP, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_PAGEDOWN, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_THUMBTRACK, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_THUMBRELEASE, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );
	m_Slider_MixImages->Disconnect( wxEVT_SCROLL_CHANGED, wxScrollEventHandler( Frame::slider_MixImagesOnScroll ), NULL, this );

}
