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
	Służy do rysowania obrazka w stanie aktualnym
	*/
	void Repaint();
	/**
	Służy do rysowania hexagonu kolorów, pokazuje aktualnie wybrany kolor
	*/
	void Repaint_picker();
	/**
	Inicjuje sześciokąt kolorów
	*/
	void Initialize_picker();
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
	Służy do pobrania koloru z obrazka
	*/
	void m_Image_BoxOnLeftDown(wxMouseEvent& event) override final;
	/**
	Służy do pobrania koloru z sześciokąta
	*/
	void m_Color_Hexagon_BoxOnLeftDown(wxMouseEvent& event) override final;


	/**
	Odświeżanie
	*/
	void image_BoxOnUpdateUI(wxUpdateUIEvent& event);
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
	/**
	Służy do zmiany nasycenia
	\param init_color kolor wypełnienia
	\param size rozmiar pola
	*/
	void Initialize_Color_Buttons(const wxColour& init_color, const wxSize& size);
	/**
	Służy do zmiany nasycenia
	\param button bitmapa guzika z kolorem
	\param image obraz guzika
	\param color wypełnienia
	*/
	void Change_button_color(wxBitmapButton* button, wxImage& image, const wxColour& color);
	/**
	Służy do zmiany koloru na obrazkie
	*/
	void m_pickedColourButtonOnButtonClick(wxCommandEvent& event) override final;
	/**
	Służy do mieszania obrazów oryginalnego ze skorygowanym
	\param value aktualne położenie suwaka
	*/
	void Blend_images(double value);

private:
	/**
	Przechowuje oryginalny obrazek
	*/
	wxImage Img_Org;
	/**
	Przechowuje modyfikowany obrazek, wyświetlana wersja
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
	Przechowuje wartości RGB referencyjne piksela
	*/
	wxImage::RGBValue Img_RGB_ref;
	/**
	Przechowuje wartości RGB modyfikowane piksela
	*/
	wxImage::RGBValue Img_RGB_mod;
	/**
	Przechowuje hexagon kolorów
	*/
	wxImage color_Picker;
	/**
	Przechowuje koordynaty na sześciokącie
	*/
	wxPoint m_color_picker_mouse_position;
	/**
	Przechowuje koordynaty na obrazku
	*/
	wxPoint m_image_mouse_position;
	/**
	Przechowuje obrazek koloru referencyjnego
	*/
	wxImage m_picked_colorButton_color;
	/**
	Przechowuje obrazek koloru modyfikowanego
	*/
	wxImage m_changed_colorButton_color;
	/**
	Przechowuje obrazek zastępczy
	*/
	wxImage Img_Cpy2;

};

#endif // __ImageCorrectionsFrame__
