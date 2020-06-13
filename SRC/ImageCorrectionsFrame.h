/////////////////////////////////////////////////////////////////////////////
// Name:        ImageCorrectionsFrame.h
// Author:      Mateusz Górczany, Hleb Shypula, Volodymyr Tymkiv
/////////////////////////////////////////////////////////////////////////////

#ifndef __ImageCorrectionsFrame__
#define __ImageCorrectionsFrame__

#include "ImageCorrections.h"

#include <memory>
#include <wx/dcclient.h>
#include <wx/wx.h>
#include <wx/colour.h>
#include <wx/colordlg.h>
#include <wx/dcbuffer.h>

/// Klasa zarządzająca funkcjami aplikacji
class ImageCorrectionsFrame : public Frame
{
public:
	/**
	Constructor
	\param parent rodzic naszej kontroli. Nie może być NULL.
	*/
	ImageCorrectionsFrame(wxWindow* parent);
	/**
	Służy do rysowania obraza w stanie aktualnym
	*/
	void Repaint();
	/**
	Służy do rysowania hexagonu kolorów
	*/
	void Repaint_picker();
	/**
	Służy do rysowania hexagonu kolorów
	\param data przechowuje dane RGB pikseli hexagonu
	\param height wysokość obszaru na hexagon
	\param width szerokość obszaru na hexagon
	*/
	constexpr void fill_hexagon(
    unsigned char* data,
    unsigned int height,
    unsigned int width);
		
protected:
	/**
	Odświeżanie
	*/
	void image_BoxOnUpdateUI(wxUpdateUIEvent& event);
	/**
	Pobieranie koloru obrazka
	*/
	void color_Hexagon_BoxOnLeftDClick(wxMouseEvent& event);
	/**
	Pobieranie koloru hexagonu
	*/
	void m_Color_Hexagon_BoxOnUpdateUI(wxUpdateUIEvent& event);
	/**
	Wybór kanału do zmiany
	*/
	void chanel_choiceOnUpdateUI(wxUpdateUIEvent& event);
	/**
	Zmiana położenia suwaka
	*/
	void slider_ChangeCoefficientOnScroll(wxScrollEvent& event);
	/**
	Mieszanie obrazu  oryginalnego ze skorygowanym
	*/
	void slider_MixImagesOnScroll(wxScrollEvent& event);
	/**
	Wybór pliku
	*/
	void menu_File_OpenOnMenuSelection(wxCommandEvent& event);
	/**
	Zapis pliku
	*/
	void menu_File_SaveOnMenuSelection(wxCommandEvent& event);
	/**
	Wyjście z programu
	*/
	void menu_File_ExitOnMenuSelection(wxCommandEvent& event);
	/**
	Info
	*/
	void menu_About_InfoOnMenuSelection(wxCommandEvent& event);
	/**
	Służy do zmiany kontrastu
	\param value aktualne położenie suwaka
	*/
	void Contrast(int value);
	/**
	Służy do zmiany jasności
	\param value aktualne położenie suwaka
	*/
	void Brightness(int value);
	/**
	Służy do zmiany barwy pikseli
	\param value aktualne położenie suwaka
	*/
	void Tone(int value);
	/**
	Służy do zmiany nasycenia
	\param value aktualne położenie suwaka
	*/
	void Saturation(int value);

	void Initialize_Color_Buttons(const wxColour &, const wxSize &);

	void Change_button_colour(wxImage &, const wxColour &color);

private:
	/**
	Przechowuje oryginalny obrazek
	*/
	wxImage Img_Org; 
	/**
	Przechowuje modyfikowany obrazek
	*/
	wxImage	Img_Cpy; 
	/**
	Przechowuje wartości HSV piksela
	*/
	wxImage::HSVValue Img_HSV;
	/**
	Przechowuje wartości RGB piksela
	*/
	wxImage::RGBValue Img_RGB;
	/**
	Przechowuje hexagon kolorów
	*/
	wxImage color_Picker;

	wxImage m_picked_colorButton_color;
	wxImage m_changed_colorButton_color;

};

#endif // __ImageCorrectionsFrame__
