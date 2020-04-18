#include "bitmap.h"
#include <iostream>
#include <fstream>

using namespace std;

bitmap::bitmap()
{
    // Constructor
}

bitmap::bitmap(const char* filename)
{
    this->set_filename(filename);
    this->retrieve_bitmap_data();
}

void bitmap::retrieve_bitmap_data()
{
    ifstream file (this->filename, ios::in|ios::binary|ios::ate);

    if (file.is_open())
    {
        char* w_b   = new char[1]; // 2-byte buffer
        char* dw_b  = new char[3]; // 4-byte buffer

        file.seekg                   (0x02, ios::beg);
        file.read                    (dw_b, sizeof(dw_b));
        this->set_file_size          ((uint8_t)dw_b[3] << 24 | (uint8_t)dw_b[2] << 16 | (uint8_t)dw_b[1] << 8 | (uint8_t)dw_b[0]);

        file.seekg                   (0x04, ios::cur);
        file.read                    (dw_b, sizeof(dw_b));
        this->set_pixel_data_offset  ((uint8_t)dw_b[3] << 24 | (uint8_t)dw_b[2] << 16 | (uint8_t)dw_b[1] << 8 | (uint8_t)dw_b[0]);

        file.seekg                   (0x04, ios::cur);
        file.read                    (dw_b, sizeof(dw_b));
        this->set_image_width        ((uint8_t)dw_b[3] << 24 | (uint8_t)dw_b[2] << 16 | (uint8_t)dw_b[1] << 8 | (uint8_t)dw_b[0]);

        file.seekg                   (0x00, ios::cur);
        file.read                    (dw_b, sizeof(dw_b));
        this->set_image_height       ((uint8_t)dw_b[3] << 24 | (uint8_t)dw_b[2] << 16 | (uint8_t)dw_b[1] << 8 | (uint8_t)dw_b[0]);

        file.seekg                   (0x02, ios::cur);
        file.read                    (w_b, sizeof(w_b));
        this->set_bits_per_pixel     ((uint8_t)w_b[1] << 8 | (uint8_t)w_b[0]);

        delete[] w_b;
        delete[] dw_b;

        this->set_image_size         (this->get_file_size() - this->get_pixel_data_offset());
        this->set_all_pixels         (new char[(int)this->get_image_size()]);

        file.seekg                   ((int)this->get_pixel_data_offset(), ios::beg);
        file.read                    (this->all_pixels, (int)this->get_image_size());
        file.close();

        this->set_scanline_byte_width         ((int)this->get_image_width() * 3);
        this->set_scanline_padding_width      ((int)this->get_scanline_byte_width() % 4);
        this->set_scanline_total_bytes        ((int)this->get_scanline_byte_width() + (int)this->get_scanline_padding_width());

    }
    else
        cout << "Error: Could not open file." << endl;
}

uint32_t bitmap::get_file_size()
{
    return this->file_size;
}

uint32_t bitmap::get_pixel_data_offset()
{
    return this->pixel_data_offset;
}

uint32_t bitmap::get_image_width()
{
    return this->image_width;
}

uint32_t bitmap::get_image_height()
{
    return this->image_height;
}

uint16_t bitmap::get_bits_per_pixel()
{
    return this->bits_per_pixel;
}

uint32_t bitmap::get_image_size()
{
    return this->image_size;
}

int bitmap::get_scanline_byte_width()
{
    return this->scanline_byte_width;
}

int bitmap::get_scanline_padding_width()
{
    return this->scanline_padding_width;
}

int bitmap::get_scanline_total_bytes()
{
    return this->scanline_total_bytes;
}

const char* bitmap::get_filename()
{
    return this->filename;
}

char* bitmap::get_all_pixels()
{
    return this->all_pixels;
}

void bitmap::set_file_size(uint32_t file_size)
{
    this->file_size = file_size;
}

void bitmap::set_pixel_data_offset(uint32_t pixel_data_offset)
{
    this->pixel_data_offset = pixel_data_offset;
}

void bitmap::set_image_width(uint32_t image_width)
{
    this->image_width = image_width;
}

void bitmap::set_image_height(uint32_t image_height)
{
    this->image_height = image_height;
}

void bitmap::set_bits_per_pixel(uint16_t bits_per_pixel)
{
    this->bits_per_pixel = bits_per_pixel;
}

void bitmap::set_image_size(uint32_t image_size)
{
    this->image_size = image_size;
}

void bitmap::set_scanline_byte_width(int scanline_byte_width)
{
    this->scanline_byte_width = scanline_byte_width;
}

void bitmap::set_scanline_padding_width(int scanline_padding_width)
{
    this->scanline_padding_width = scanline_padding_width;
}

void bitmap::set_scanline_total_bytes(int scanline_total_bytes)
{
    this->scanline_total_bytes = scanline_total_bytes;
}

void bitmap::set_filename(const char* filename)
{
    this->filename = filename;
}

void bitmap::set_all_pixels(char* all_pixels)
{
    this->all_pixels = all_pixels;
}
