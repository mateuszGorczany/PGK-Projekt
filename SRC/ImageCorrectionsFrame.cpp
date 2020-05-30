#include "ImageCorrectionsFrame.h"

ImageCorrectionsFrame::ImageCorrectionsFrame(wxWindow* parent)
    :
    Frame(parent)
{
    m_Image_Box->SetScrollbars(20, 20, 50, 48);
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
    Repaint();
}

void ImageCorrectionsFrame::chanel_choiceOnUpdateUI(wxUpdateUIEvent& event)
{
    // TODO: Implement chanel_choiceOnUpdateUI
    Repaint();
}

void ImageCorrectionsFrame::slider_ChangeCoefficientOnScroll(wxScrollEvent& event)
{
    // TODO: Implement slider_ChangeCoefficientOnScroll
    if (m_Chanel_choice->GetSelection() == 0)
    {
        Barwa(m_Slider_ChangeCoefficient->GetValue());
        Repaint();
    }
    else if (m_Chanel_choice->GetSelection() == 1)
    {
        Brightness(m_Slider_ChangeCoefficient->GetValue() - 100);
        Repaint();
    }
    else if (m_Chanel_choice->GetSelection() == 2)
    {
        // Nasycenie
        Saturation(m_Slider_ChangeCoefficient->GetValue() - 100);
        Repaint();
    }
    else if (m_Chanel_choice->GetSelection() == 3)
    {
        Contrast(m_Slider_ChangeCoefficient->GetValue() - 100);
        Repaint();
    }
}

void ImageCorrectionsFrame::slider_MixImagesOnScroll(wxScrollEvent& event)
{
    // TODO: Implement slider_MixImagesOnScroll
    Repaint();
}

void ImageCorrectionsFrame::menu_File_OpenOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_OpenOnMenuSelection
    std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Otwórz"), _(""), _(""), _("PNG files (*.png)|*.png|JPEG files (*.jpg)|*.jpg"), wxFD_OPEN));
    if (Dialog->ShowModal() == wxID_OK)
    {
        Img_Org.AddHandler(new wxJPEGHandler);
        Img_Org.AddHandler(new wxPNGHandler);
        Img_Org.LoadFile(Dialog->GetPath());
        Img_Cpy.AddHandler(new wxJPEGHandler);
        Img_Cpy.AddHandler(new wxPNGHandler);
        Img_Cpy.LoadFile(Dialog->GetPath());
    }
    if (Img_Org.IsOk())
    {
        Repaint();
    }
}

void ImageCorrectionsFrame::menu_File_SaveOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_SaveOnMenuSelection
    if (Img_Cpy.IsOk())
    {
        std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Zapisz"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT));
        if (Dialog->ShowModal() == wxID_OK)
        {
            Img_Cpy.AddHandler(new wxJPEGHandler);
            Img_Cpy.AddHandler(new wxPNGHandler);
            //m_Image = m_Bitmap.ConvertToImage();
            Img_Cpy.SaveFile(Dialog->GetPath());
        }
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
    if (Img_Cpy.IsOk())
    {
        wxBitmap bitmap(Img_Cpy);          // Tworzymy tymczasowa bitmape na podstawie Img_Cpy
        wxClientDC dc(m_Image_Box);  // Pobieramy kontekst okna
        m_Image_Box->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
        dc.DrawBitmap(bitmap, 0, 0, false); // Rysujemy bitmape na kontekscie urzadzenia
    }
}

void ImageCorrectionsFrame::Contrast(int value)
{
    Img_Cpy = Img_Org.Copy();
    int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
    unsigned char* Img_Data = Img_Cpy.GetData();

    double contrast = (double(value) + 100) / (100.0001 - value);

    for (int i = 0; i < size; i++)
    {
        int tmp = (Img_Data[i] - 255.0 / 2) * contrast + 255.0 / 2;

        if (tmp > 255)
            tmp = 255;
        else if (tmp < 0)
            tmp = 0;

        Img_Data[i] = tmp;
    }
}

void ImageCorrectionsFrame::Brightness(int value)
{
    Img_Cpy = Img_Org.Copy();
    int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
    unsigned char* Img_Data = Img_Cpy.GetData();

    int temp;

    for (int i = 0; i < size; i++)
    {
        temp = Img_Data[i] + value;

        if (temp > 255)
        {
            temp = 255;
        }
        else if (temp < 0)
        {
            temp = 0;
        }

        Img_Data[i] = temp;
    }
}

void ImageCorrectionsFrame::Barwa(int value)
{
    Img_Cpy = Img_Org.Copy();
    int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
    unsigned char* Img_Data = Img_Cpy.GetData();

    int Rref = 227;
    int Gref = 35;
    int Bref = 34;
    int Rmod = 34;
    int Gmod = 35;
    int Bmod = 227;

    Img_Cpy.Replace(Rref, Gref, Bref, Rmod, Gmod, Bmod);

    /*int Ru = (Rref / Rmod) * (double(value) / 200);
    int Gu = (Gref / Gmod) * (double(value) / 200);
    int Bu = (Bref / Bmod) * (double(value) / 200);*/

    for (int i = 0; i < size; i += 3)
    {
        /*Img_Data[i] = (1 / fabs(Rref - Rmod)) * value * 1000;
        Img_Data[i+1] = (1 / fabs(Gref - Gmod)) * value * 1000;
        Img_Data[i+2] = (1 / fabs(Bref - Bmod)) * value * 1000;*/
    }
}

void ImageCorrectionsFrame::Saturation(int value)
{
    
}
