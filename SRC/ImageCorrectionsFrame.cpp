#include "ImageCorrectionsFrame.h"

ImageCorrectionsFrame::ImageCorrectionsFrame(wxWindow* parent)
    :
    Frame(parent)
{
    m_Image_Box->SetScrollbars(20, 20, 50, 48);
    m_Image_Box->SetBackgroundColour(wxColor(192, 192, 192));
    m_Color_Hexagon_Box->SetBackgroundColour(wxColor(192, 192, 192));
}

void ImageCorrectionsFrame::image_BoxOnUpdateUI(wxUpdateUIEvent& event)
{
    // TODO: Implement image_BoxOnUpdateUI
    Repaint();
}

void ImageCorrectionsFrame::color_Hexagon_BoxOnLeftDClick(wxMouseEvent& event)
{
     //TODO: Implement color_Hexagon_BoxOnLeftDClick
    Repaint();
}

void ImageCorrectionsFrame::m_Color_Hexagon_BoxOnUpdateUI(wxUpdateUIEvent& event)
{
    Repaint_picker();
}

void ImageCorrectionsFrame::chanel_choiceOnUpdateUI(wxUpdateUIEvent& event)
{
    // TODO: Implement chanel_choiceOnUpdateUI
    
}

void ImageCorrectionsFrame::slider_ChangeCoefficientOnScroll(wxScrollEvent& event)
{
    // TODO: Implement slider_ChangeCoefficientOnScroll
    if (m_Chanel_choice->GetSelection() == 0)
    {
        // Barwa
    }
    else if (m_Chanel_choice->GetSelection() == 1)
    {
        Brightness(m_Slider_ChangeCoefficient->GetValue() - 100);
        Repaint();
    }
    else if (m_Chanel_choice->GetSelection() == 2)
    {
        // Nasycenie
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

    /*wxColor toChange(254, 0, 0);
    wxColor newColor(0, 0, 255);
    unsigned char toR = toChange.Red();
    unsigned char toG = toChange.Green();
    unsigned char toB = toChange.Blue();
    unsigned char newR = newColor.Red();
    unsigned char newG = newColor.Green();
    unsigned char newB = newColor.Blue();
    Img_Cpy.Replace(toR, toG, toB, newR, newG, newB);
    Repaint();*/
}

void ImageCorrectionsFrame::menu_File_OpenOnMenuSelection(wxCommandEvent& event)
{
    // TODO: Implement menu_File_OpenOnMenuSelection
    std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Otwórz"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_OPEN));
    if (Dialog->ShowModal() == wxID_OK)
    {
        Img_Org.AddHandler(new wxJPEGHandler);
        Img_Org.AddHandler(new wxPNGHandler);
        Img_Org.LoadFile(Dialog->GetPath());
        Img_Cpy.AddHandler(new wxJPEGHandler);
        Img_Cpy.AddHandler(new wxPNGHandler);
        Img_Cpy.LoadFile(Dialog->GetPath());
    }
    if (Img_Org.IsOk() && Img_Cpy.IsOk())
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
    m_Image_Box->DoPrepareDC(dc); // Musimy wywolac w przypadku wxScrolledWindow, zeby suwaki prawidlowo dzialaly
    dc.DrawBitmap(bitmap, 0, 0, true); // Rysujemy bitmape na kontekscie urzadzenia
    Repaint_picker();
}

void ImageCorrectionsFrame::Repaint_picker()
{
    unsigned int width = m_Color_Hexagon_Box->GetSize().x;
    unsigned int height = m_Color_Hexagon_Box->GetSize().y;

    unsigned char* data = new unsigned char[width * height * 3];
    fill_hexagon(data, width, height);
    color_Picker = wxImage(width, height, data, false);

    wxBitmap m_picker_bitmap = wxBitmap(color_Picker, -1);
    wxClientDC dc(m_Color_Hexagon_Box); 
    wxBufferedDC DC(&dc, m_picker_bitmap);

    DC.SetDeviceOrigin(width / 2, height / 2);
}


constexpr void ImageCorrectionsFrame::fill_hexagon(
    unsigned char* data, 
    unsigned int height, 
    unsigned int width)
{
    constexpr double ratio = 1.728;
    constexpr double tales = 125 / 216.5;
    constexpr double color_ratio = 2.04;
    for (unsigned int y = 0; y < height / 4; ++y)
    {
        for (unsigned int x = 125; x < 125 + y * ratio; ++x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = 255;
            data[base + 1] = color_ratio * tales * (s + f);
            data[base + 2] = color_ratio * tales * (s - f);
        }
        for (int x = 125; x > 125 - y * ratio; --x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = 255;
            data[base + 1] = color_ratio * tales * (s + f);
            data[base + 2] = color_ratio * tales * (s - f);
        }
    }
    for (unsigned int y = height/4; y < height/2; ++y)
    {
        unsigned int h{ y - height / 4 };
        for (unsigned int x = 125; x < 125 + (108-h * ratio); ++x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = 255;
            data[base + 1] = color_ratio * tales * (s + f);
            data[base + 2] = color_ratio * tales * (s - f);
        }
        for (int x = 125; x > 125 - (108 - h * ratio); --x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = 255;
            data[base + 1] = color_ratio * tales * (s + f);
            data[base + 2] = color_ratio * tales * (s - f);
        }
    }
    
    constexpr unsigned int width_h = 216 + 17;
    for (unsigned int y = height / 4; y < height /2; ++y)
    {
        unsigned int h{ y - height / 4 };
        for (unsigned int x = 17; x < h * ratio + 17; ++x)
        {
            double f = x - 17;
            double s = (108 - f) * sqrt(3) / 3.;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio*(125 - h + f/tan(M_PI/3.));
            data[base + 1] = 255 * (2.*sqrt(3)*f/(3.*125.));
            data[base + 2] = 255;
        }
        for (unsigned int x = 216+17; x >= width_h - h * ratio; --x)
        {
            double f = x - 125;
            double s = sqrt(3) * h;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * (125 - h + (108-f)/tan(M_PI/3.));
            data[base + 1] = 255;
            data[base + 2] = 255 * (1-2 * sqrt(3) * f / (3*125.));
        }
    }

    constexpr double rr = 125. / 108.;
    for (unsigned int y = height / 2; y < 3*height / 4; ++y)
    {
        unsigned int h{ y - height / 2 };
        for (unsigned int x = 17; x <= 125; ++x)
        {
            double f = x-17;
            double s = height / 4 - h + f * tan(M_PI / 6.);
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * (height/4. - h + f/tan(M_PI/3.));
            data[base + 1] = 255 * f / (cos(M_PI / 6.) * 125);
            data[base + 2] = 255;
        }
        for (unsigned int x = 125; x <= 216+17; ++x)
        {
            double f = x - 125;
            double s = (f) * sqrt(3) / 3.;;
            size_t base = (x + width * y) * 3;
            data[base + 0] = 255*(1-(h+s)/125.);
            data[base + 1] = 255;
            data[base + 2] = 255 * (2 * sqrt(3) *(108 - f) / (3 * 125.));
        }
    }

    const double ratio_h = height / (4. * 108);
    for (unsigned int y = 3*height / 4; y < height; ++y)
    {
        unsigned int h{ y - 3*height / 4};
        for (int x = 125; x < 125 + (108 - h * ratio); ++x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * ((108-f) * height / (4. * 108) - h);
            data[base + 1] = 255;
            data[base + 2] = 255 * (1 - f / (sin(M_PI/3.) * 125));
        }
        for (int x = 125; x >= 125 - (108 - h * ratio); --x)
        {
            double f = x - 17.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * (f*ratio_h-h);
            data[base + 1] = 255 * (f/(sin(M_PI/3.)* 125));
            data[base + 2] = 255;
        }
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
    unsigned char* Img_data = Img_Cpy.GetData();

    int temp;

    for (int i = 0; i < size; i++)
    {
        temp = Img_data[i] + value;

        if (temp > 255)
        {
            temp = 255;
        }
        else if (temp < 0)
        {
            temp = 0;
        }

        Img_data[i] = temp;
    }
}
