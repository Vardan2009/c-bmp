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
            int pixel_index = (y * img.infoHeader.width + x) * (img.infoHeader.bitsPerPixel / 8);
            
            unsigned char blue = img.imageData[pixel_index];
            unsigned char green = img.imageData[pixel_index + 1];
            unsigned char red = img.imageData[pixel_index + 2];

            unsigned char pixavg = (red+green+blue)/3;

            img.imageData[pixel_index] = pixavg;
            img.imageData[pixel_index + 1] = pixavg;
            img.imageData[pixel_index + 2] = pixavg;
        }
    }

    writeBMP("tests/0out.bmp",img);
}