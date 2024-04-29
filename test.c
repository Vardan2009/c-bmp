#include <stdio.h>

//including the library
#include "src/bmp.c"


//testing Bitmap library
// taking image file as input and grayscaling it
int main()
{
    BMPImage img = readBMP("tests/0.bmp");

    for (int y = 0; y < img.infoHeader.height; y++) {
        for (int x = 0; x < img.infoHeader.width; x++) {
            Pixel p = getPixel(&img,x,y);
            unsigned char pixavg = (p.r+p.g+p.b)/3;
            p.r = pixavg;
            p.g = pixavg;
            p.b = pixavg;
            setPixel(&img,x,y,p);
        }
    }

    writeBMP("tests/0out.bmp",img);
}