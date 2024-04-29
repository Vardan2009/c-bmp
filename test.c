#include <stdio.h>

//including the library
#include "src/bmp.c"


unsigned char clamp(int value, int min, int max) {
    if (value < min)
        return (unsigned char)min;
    else if (value > max)
        return (unsigned char)max;
    else
        return (unsigned char)value;
}


//testing Bitmap library

// taking image as input and grayscaling it
void grayscale(BMPImage* img)
{
    for (int y = 0; y < img->infoHeader.height; y++) {
        for (int x = 0; x < img->infoHeader.width; x++) {
            Pixel p = getPixel(img,x,y);
            unsigned char pixavg = (p.r+p.g+p.b)/3;
            p.r = pixavg;
            p.g = pixavg;
            p.b = pixavg;
            setPixel(img,x,y,p);
        }
    }
}

// taking image as input and adding brightness to each pixel
void invert(BMPImage* img)
{
    for (int y = 0; y < img->infoHeader.height; y++) {
        for (int x = 0; x < img->infoHeader.width; x++) {
            Pixel p = getPixel(img,x,y);
            p.r = 255 - p.r;
            p.g = 255 - p.g;
            p.b = 255 - p.b;
            setPixel(img,x,y,p);
        }
    }
}

void vintage(BMPImage* img)
{
    for (int y = 0; y < img->infoHeader.height; y++) {
        for (int x = 0; x < img->infoHeader.width; x++) {
            Pixel p = getPixel(img, x, y);

            p.b = (unsigned char)(p.b * 0.5);
            p.g = (unsigned char)(p.g * 0.7);

            setPixel(img, x, y, p);
        }
    }
}


int main()
{
    BMPImage img = readBMP("tests/0.bmp");

    grayscale(&img);
    vintage(&img);

    writeBMP("tests/0out.bmp",img);
}