#include "ImageCorrectionsFrame.h"

ImageCorrectionsFrame::ImageCorrectionsFrame(wxWindow* parent)
    :
    Frame(parent)
{
    m_Image_Box->SetScrollbars(20, 20, 50, 50);
    m_Image_Box->SetBackgroundColour(wxColor(192, 192, 192));
}

void ImageCorrectionsFrame::image_BoxOnUpdateUI(wxUpdateUIEvent& event)
{
    // TODO: Implement image_BoxOnUpdateUI
    Repaint();
}

void ImageCorrectionsFrame::color_Hexagon_BoxOnLeftDClick(wxMouseEvent& event)
{
    // TODO: Implement color_Hexagon_BoxOnLeftDClick
}

void ImageCorrectionsFrame::chanel_choiceOnUpdateUI(wxUpdateUIEvent& event)
{
    // TODO: Implement chanel_choiceOnUpdateUI
}

void ImageCorrectionsFrame::slider_ChangeCoefficientOnScroll(wxScrollEvent& event)
{
    // TODO: Implement slider_ChangeCoefficientOnScroll
}

void ImageCorrectionsFrame::slider_MixImagesOnScroll(wxScrollEvent& event)
{
    // TODO: Implement slider_MixImagesOnScroll
}

void ImageCorrectionsFrame::menu_File_OpenOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_OpenOnMenuSelection
    std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Otwórz"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN));
    if (Dialog->ShowModal() == wxID_OK)
    {
        Img_Cpy.AddHandler(new wxJPEGHandler);
        Img_Cpy.AddHandler(new wxPNGHandler);
        Img_Cpy.LoadFile(Dialog->GetPath());
    }
    if (Img_Cpy.IsOk())
        Repaint();
}

void ImageCorrectionsFrame::menu_File_SaveOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_SaveOnMenuSelection
    if (Img_Cpy.IsOk())
    {
        Repaint();
        std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Zapisz"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT));
        if (Dialog->ShowModal() == wxID_OK)
        {
            Img_Cpy.AddHandler(new wxJPEGHandler);
            Img_Cpy.AddHandler(new wxPNGHandler);
            //m_Image = m_Bitmap.ConvertToImage();
            Img_Cpy.SaveFile(Dialog->GetPath());
        }
        Repaint();
    }

}

void ImageCorrectionsFrame::menu_File_ExitOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_ExitOnMenuSelection
    Destroy();
}

void ImageCorrectionsFrame::menu_About_InfoOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_About_InfoOnMenuSelection
}

void ImageCorrectionsFrame::Repaint()
{
    wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
    wxClientDC dc(m_Image_Box);   // Pobieramy kontekst okna
    wxBufferedDC buffDC(&dc);
    buffDC.Clear();
    m_Image_Box->DoPrepareDC(buffDC); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
    buffDC.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
}
