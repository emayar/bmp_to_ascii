#include "greyscale.h"

using namespace std;

greyscale::greyscale(bitmap bmp)
{
    int greyscale_image[bmp.get_image_width()][bmp.get_image_height()];

    int byte_counter          = bmp.get_scanline_total_bytes();
    int height_counter        = 0;
    int width_counter         = 0;

    uint8_t current_pixel_hue = 0;
    uint8_t r                 = 0;
    uint8_t g                 = 0;
    uint8_t b                 = 0;

    for(int i = (int)bmp.get_image_size()-1; i >= 0; i--)
    {
        if (byte_counter == 0) // End of the scanline has been reached
        {
            byte_counter = bmp.get_scanline_total_bytes(); // Reset byte_counter
            height_counter++;
            width_counter = 0;

            if (bmp.get_scanline_padding_width() != 0)
                for (int p = (int)bmp.get_scanline_padding_width(); p >=0; p--)
                    i--;
        }

        if (byte_counter <= bmp.get_scanline_byte_width())
        {
            switch (current_pixel_hue)
            {
            case 0:
                r = bmp.get_all_pixels()[i];
                current_pixel_hue++;
                break;

            case 1:
                g = bmp.get_all_pixels()[i];
                current_pixel_hue++;
                break;

            case 2:
                b = bmp.get_all_pixels()[i];
                current_pixel_hue = 0;
                greyscale_image[width_counter][height_counter] = ((r + g + b) / 3);
                width_counter++;
                break;

            default:
                cout << "Error: Could not determine which hue is represented by the current byte: " << (int)(uint8_t)bmp.get_all_pixels()[i] << endl;
            }
            byte_counter--;
        }
        else
            byte_counter--;
    }

    for (int y = 0; y <= (int)bmp.get_image_height()-1; y++)
    {
        for (int x = (int)bmp.get_image_width()-1; x >= 0; x--)
            cout << grey_pixel(greyscale_image[x][y]) << " ";

        cout << endl;
    }
}

char greyscale::grey_pixel(unsigned char lightness)
{
    if (lightness > 0 && lightness <= 32)
        return ' ';

    if (lightness > 32 && lightness <= 64)
        return '.';

    if (lightness > 64 && lightness <= 128)
        return '_';

    if (lightness > 128 && lightness <= 192)
        return 'O';

    if (lightness > 192 && lightness <= 224)
        return '$';

    if (lightness > 224 && lightness <= 256)
        return '@';
}
