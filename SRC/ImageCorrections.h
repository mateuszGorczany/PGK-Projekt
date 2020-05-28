///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version Oct 26 2018)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/scrolwin.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/sizer.h>
#include <wx/panel.h>
#include <wx/choice.h>
#include <wx/stattext.h>
#include <wx/slider.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/menu.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////////////////////////
/// Class Frame
///////////////////////////////////////////////////////////////////////////////
class Frame : public wxFrame
{
	private:

	protected:
		wxScrolledWindow* m_Image_Box;
		wxPanel* m_Color_Hexagon_Box;
		wxChoice* m_Chanel_choice;
		wxStaticText* m_StaticText_ChangeCoefficient;
		wxSlider* m_Slider_ChangeCoefficient;
		wxStaticText* m_StaticText_MixImages;
		wxSlider* m_Slider_MixImages;
		wxMenuBar* m_menubar;
		wxMenu* menu_File;
		wxMenu* menu_About;

		// Virtual event handlers, overide them in your derived class
		virtual void color_Hexagon_BoxOnLeftDClick( wxMouseEvent& event ) { event.Skip(); }
		virtual void chanel_choiceOnUpdateUI( wxUpdateUIEvent& event ) { event.Skip(); }
		virtual void slider_ChangeCoefficientOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void slider_MixImagesOnScroll( wxScrollEvent& event ) { event.Skip(); }
		virtual void menu_File_OpenOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void menu_File_SaveOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void menu_File_ExitOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }
		virtual void menu_About_InfoOnMenuSelection( wxCommandEvent& event ) { event.Skip(); }


	public:

		Frame( wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = wxT("Korekty obrazow"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize( 865,639 ), long style = wxDEFAULT_FRAME_STYLE|wxTAB_TRAVERSAL );

		~Frame();

};
