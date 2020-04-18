#ifndef BITMAP_H
#define BITMAP_H
#include <iostream>

class bitmap
{
    public:

        bitmap();
        bitmap(const char* filename);

        // setters
        void set_file_size(uint32_t file_size);
        void set_pixel_data_offset(uint32_t pixel_data_offset);
        void set_image_width(uint32_t image_width);
        void set_image_height(uint32_t image_height);
        void set_bits_per_pixel(uint16_t bits_per_pixel);
        void set_image_size(uint32_t image_size);

        void set_scanline_byte_width(int scanline_byte_width);
        void set_scanline_padding_width(int scanline_padding_width);
        void set_scanline_total_bytes(int scanline_total_bytes);

        void set_filename(const char* filename);
        void set_all_pixels(char* all_pixels);

        // getters
        uint32_t get_file_size();
        uint32_t get_pixel_data_offset();
        uint32_t get_image_width();
        uint32_t get_image_height();
        uint16_t get_bits_per_pixel();
        uint32_t get_image_size();

        int get_scanline_byte_width();
        int get_scanline_padding_width();
        int get_scanline_total_bytes();

        const char* get_filename();
        char* get_all_pixels();

    private:
        void retrieve_bitmap_data();

        uint32_t file_size;
        uint32_t pixel_data_offset;
        uint32_t image_width;
        uint32_t image_height;
        uint16_t bits_per_pixel;
        uint32_t image_size;

        int scanline_byte_width;
        int scanline_padding_width;
        int scanline_total_bytes;

        const char* filename;
        char* all_pixels;
};

#endif // BITMAP_H
