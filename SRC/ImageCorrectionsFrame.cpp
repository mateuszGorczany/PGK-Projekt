#include "ImageCorrectionsFrame.h"

ImageCorrectionsFrame::ImageCorrectionsFrame(wxWindow* parent)
    : 
    Frame(parent),
    m_color_picker_mouse_position{125,125}
{
    m_Image_Box->SetScrollbars(20, 20, 50, 48);
    m_Image_Box->SetBackgroundColour(wxColor(192, 192, 192));
    m_Color_Hexagon_Box->SetBackgroundColour(wxColor(192, 192, 192));

    Initialize_Color_Buttons(wxColour("White"), wxSize{ 64, 32 });
    Initialize_picker();
}

void ImageCorrectionsFrame::image_BoxOnUpdateUI(wxUpdateUIEvent& event)
{
    Repaint();
}

void ImageCorrectionsFrame::color_Hexagon_BoxOnLeftDClick(wxMouseEvent& event)
{
    wxPoint x =wxWindow::ClientToScreen(event.GetPosition());
    Repaint();
}

void ImageCorrectionsFrame::m_pickedColourButtonOnButtonClick(wxCommandEvent& event)
{
    Img_Cpy.Replace(m_changed_colorButton_color.GetRed(5, 5),
        m_changed_colorButton_color.GetGreen(5, 5),
        m_changed_colorButton_color.GetBlue(5, 5),
        m_picked_colorButton_color.GetRed(5, 5),
        m_picked_colorButton_color.GetGreen(5, 5),
        m_picked_colorButton_color.GetBlue(5, 5));
}

void ImageCorrectionsFrame::m_Image_BoxOnLeftDown(wxMouseEvent& event)
{
    if (!Img_Org.IsOk())
        return;
    wxPoint position = event.GetPosition();
    Change_button_color(m_changedColourButton,
        m_changed_colorButton_color,
        wxColour{ Img_Cpy.GetRed(position.x,
                                      position.y),
                  Img_Cpy.GetGreen(position.x,
                                        position.y),
                  Img_Cpy.GetBlue(position.x,
                                       position.y) });
}

void ImageCorrectionsFrame::m_Color_Hexagon_BoxOnLeftDown(wxMouseEvent& event)
{

    m_color_picker_mouse_position = event.GetPosition();
    Change_button_color(m_pickedColourButton,
                        m_picked_colorButton_color, 
                        wxColour{ color_Picker.GetRed(m_color_picker_mouse_position.x,
                                                      m_color_picker_mouse_position.y),
                                  color_Picker.GetGreen(m_color_picker_mouse_position.x,
                                                        m_color_picker_mouse_position.y),
                                  color_Picker.GetBlue(m_color_picker_mouse_position.x,
                                                       m_color_picker_mouse_position.y) });
}


void ImageCorrectionsFrame::m_Color_Hexagon_BoxOnUpdateUI(wxUpdateUIEvent& event)
{
    Repaint_picker();
}

void ImageCorrectionsFrame::chanel_choiceOnUpdateUI(wxUpdateUIEvent& event)
{
    Repaint();
}

void ImageCorrectionsFrame::slider_ChangeCoefficientOnScroll(wxScrollEvent& event)
{
    if (m_Chanel_choice->GetSelection() == 0)
    {
        Tone(m_Slider_ChangeCoefficient->GetValue());
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
    Repaint();
}

void ImageCorrectionsFrame::menu_File_OpenOnMenuSelection(wxCommandEvent& event)
{
    m_Image_Box->ClearBackground();
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
    if (Img_Cpy.IsOk())
    {
        std::shared_ptr<wxFileDialog> Dialog(new wxFileDialog(this, _("Zapisz"), _(""), _(""), _("JPEG files (*.jpg)|*.jpg"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT));
        if (Dialog->ShowModal() == wxID_OK)
        {
            Img_Cpy.AddHandler(new wxJPEGHandler);
            Img_Cpy.AddHandler(new wxPNGHandler);
            Img_Cpy.SaveFile(Dialog->GetPath());
        }
    }
}

void ImageCorrectionsFrame::menu_File_ExitOnMenuSelection(wxCommandEvent& event)
{
    Destroy();
}

void ImageCorrectionsFrame::menu_About_InfoOnMenuSelection(wxCommandEvent& event)
{
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

void ImageCorrectionsFrame::Initialize_picker()
{
    unsigned int width = m_Color_Hexagon_Box->GetSize().x;
    unsigned int height = m_Color_Hexagon_Box->GetSize().y;

    unsigned char* data = new unsigned char[width * height * 3];
    fill_hexagon(data, width, height);
    color_Picker = wxImage(width, height, data, false);
}

void ImageCorrectionsFrame::Repaint_picker()
{
    wxBitmap m_picker_bitmap = wxBitmap(color_Picker, -1);
    wxClientDC dc(m_Color_Hexagon_Box);
    wxBufferedDC DC(&dc, m_picker_bitmap);

    DC.SetBrush(*wxGREY_BRUSH);
    DC.DrawCircle(m_color_picker_mouse_position, 3);
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
    for (unsigned int y = 3 * height / 4; y < height; ++y)
    {
        unsigned int h{ y - 3 * height / 4 };
        for (int x = 125; x < 125 + (108 - h * ratio); ++x)
        {
            double f = x - 125.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * ((108 - f) * height / (4. * 108) - h);
            data[base + 1] = 255;
            data[base + 2] = 255 * (1 - f / (sin(M_PI / 3.) * 125));
        }
        for (int x = 125; x >= 125 - (108 - h * ratio); --x)
        {
            double f = x - 17.;
            double s = sqrt(3) * y;
            size_t base = (x + width * y) * 3;
            data[base + 0] = color_ratio * (f * ratio_h - h);
            data[base + 1] = 255 * (f / (sin(M_PI / 3.) * 125));
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

void ImageCorrectionsFrame::Tone(int value)
{
    Img_Cpy = Img_Org.Copy();
    int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
    unsigned char* Img_Data = Img_Cpy.GetData();

    int Rref = m_picked_colorButton_color.GetRed(5,5);
    int Gref = m_picked_colorButton_color.GetGreen(5, 5);
    int Bref = m_picked_colorButton_color.GetBlue(5, 5);
    int Rmod = m_changed_colorButton_color.GetRed(5, 5);
    int Gmod = m_changed_colorButton_color.GetGreen(5, 5);
    int Bmod = m_changed_colorButton_color.GetBlue(5, 5);


    for (int i = 0; i < size; i += 3)
    {
        if (Img_Data[i] != Rmod && Img_Data[i + 1] != Gmod && Img_Data[i + 2] != Bmod)
        {
            Img_Data[i] = 1 / fabs(Img_Data[i] - Rmod) * Rref * value / 100;
            Img_Data[i+1] = 1 / fabs(Img_Data[i+1] - Gmod) * Gref * value / 100;
            Img_Data[i+2] = 1 / fabs(Img_Data[i+2] - Bmod) * Bref * value / 100;
        }
    }
    Img_Cpy.Replace(Rmod, Gmod, Bmod, Rref, Gref, Bref);
    Repaint();
}

void ImageCorrectionsFrame::Saturation(int value)
{
    Img_Cpy = Img_Org.Copy();
    int size = Img_Org.GetWidth() * Img_Org.GetHeight() * 3;
    unsigned char* Img_Data = Img_Cpy.GetData();

    for (int i = 0; i < size; i += 3)
    {
        Img_RGB.red = Img_Data[i];
        Img_RGB.green = Img_Data[i + 1];
        Img_RGB.blue = Img_Data[i + 2];

        Img_HSV = wxImage::RGBtoHSV(Img_RGB);

        if (value < 0)
        {
            Img_HSV.saturation = Img_HSV.saturation - fabs(double(value) / 100);
            if (Img_HSV.saturation < 0.0)
            {
                Img_HSV.saturation = 0.0;
            }
        }
        else if (value >= 0)
        {
            Img_HSV.saturation = Img_HSV.saturation + double(value) / 100;
            if (Img_HSV.saturation > 1.0)
            {
                Img_HSV.saturation = 1.0;
            }
        }

        Img_RGB = wxImage::HSVtoRGB(Img_HSV);

        Img_Data[i] = Img_RGB.red;
        Img_Data[i + 1] = Img_RGB.green;
        Img_Data[i + 2] = Img_RGB.blue;
    }
}


void ImageCorrectionsFrame::Initialize_Color_Buttons(const wxColour &init_color, const wxSize& size)
{
    const int width{ size.x };
    const int height{ size.y };

    const unsigned char R = init_color.Red();
    const unsigned char G = init_color.Green();
    const unsigned char B = init_color.Blue();

    unsigned char* data = new unsigned char[width * height * 3];
    unsigned char* data2 = new unsigned char[width * height * 3];


    for(int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            size_t base = (x + width * y) * 3;
            data[base + 0] = R;
            data[base + 1] = G;
            data[base + 2] = B;

            data2[base + 0] = R;
            data2[base + 1] = G;
            data2[base + 2] = B;
        }
    }

    m_picked_colorButton_color = wxImage{ size, data, false };
    m_changed_colorButton_color = wxImage{ size, data2, false };

    m_pickedColourButton->SetBitmap(wxBitmap{ m_picked_colorButton_color });
    m_changedColourButton->SetBitmap(wxBitmap{ m_changed_colorButton_color });
}

void ImageCorrectionsFrame::Change_button_color(wxBitmapButton *button, wxImage &image, const wxColour &color)
{
    const int width{ image.GetSize().GetWidth() };
    const int height{ image.GetSize().GetHeight() };

    const unsigned char R = color.Red();
    const unsigned char G = color.Green();
    const unsigned char B = color.Blue();

    unsigned char* data = image.GetData();

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            size_t base = (x + width * y) * 3;
            data[base + 0] = R;
            data[base + 1] = G;
            data[base + 2] = B;
        }
    }
    button->SetBitmap(wxBitmap{ image });
}

