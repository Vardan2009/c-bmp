#include <stdio.h>
#include <stdlib.h>

#pragma pack(push, 1)

typedef struct {
    unsigned char signature[2];
    unsigned int fileSize;
    unsigned short reserved1;
    unsigned short reserved2;
    unsigned int dataOffset;
} BMPHeader;

typedef struct {
    unsigned int headerSize;
    int width;
    int height;
    unsigned short planes;
    unsigned short bitsPerPixel;
    unsigned int compression;
    unsigned int imageSize;
    int xPixelsPerMeter;
    int yPixelsPerMeter;
    unsigned int colorsUsed;
    unsigned int colorsImportant;
} BMPInfoHeader;

typedef struct {
    int x,y;
    unsigned char r,g,b;
} Pixel;


typedef struct {
    BMPHeader header;
    BMPInfoHeader infoHeader;
    unsigned char *imageData;
} BMPImage;

#pragma pack(pop)

void writeBMP(const char *filename, BMPImage bmp);
BMPImage readBMP(const char *filepath);
Pixel getPixel(BMPImage* img, int x, int y);
void setPixel(BMPImage * img, int x, int y, Pixel pix);