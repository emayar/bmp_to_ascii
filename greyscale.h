#ifndef GREYSCALE_H
#define GREYSCALE_H
#include "bitmap.h"

class greyscale
{
    public:
        greyscale(bitmap bmp);

    private:
        char grey_pixel(unsigned char lightness);
};

#endif // GREYSCALE_H
