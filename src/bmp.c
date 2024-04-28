#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void writeBMP(const char *filename, BMPImage bmp) {
    FILE *file = fopen(filename, "wb");

    if (!file) {
        printf("Error opening file for writing.\n");
        return;
    }

    unsigned char *imageData = bmp.imageData;
    int width = bmp.infoHeader.width;
    int height = bmp.infoHeader.height;
    int bitsPerPixel = bmp.infoHeader.bitsPerPixel;

    // BMP header
    BMPHeader header;
    header.signature[0] = 'B';
    header.signature[1] = 'M';
    header.fileSize = sizeof(BMPHeader) + sizeof(BMPInfoHeader) + width * height * (bitsPerPixel / 8);
    header.reserved1 = 0;
    header.reserved2 = 0;
    header.dataOffset = sizeof(BMPHeader) + sizeof(BMPInfoHeader);

    fwrite(&header, sizeof(BMPHeader), 1, file);

    // BMP info header
    BMPInfoHeader infoHeader;
    infoHeader.headerSize = sizeof(BMPInfoHeader);
    infoHeader.width = width;
    infoHeader.height = height;
    infoHeader.planes = 1;
    infoHeader.bitsPerPixel = bitsPerPixel;
    infoHeader.compression = 0;
    infoHeader.imageSize = width * height * (bitsPerPixel / 8);
    infoHeader.xPixelsPerMeter = 0;
    infoHeader.yPixelsPerMeter = 0;
    infoHeader.colorsUsed = 0;
    infoHeader.colorsImportant = 0;

    fwrite(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    // Write pixel data
    fwrite(imageData, sizeof(unsigned char), width * height * (bitsPerPixel / 8), file);

    fclose(file);
}

BMPImage readBMP(const char *filepath)
{
    FILE* file = fopen(filepath,"rb");

    if(!file)
    {
        printf("Error opening file\n");
        exit(1);
    }

    BMPHeader header;
    fread(&header,sizeof(BMPHeader),1,file);

    if (header.signature[0] != 'B' || header.signature[1] != 'M') {
        printf("Not a BMP file.\n");
        fclose(file);
        exit(1);
    }

    BMPInfoHeader infoHeader;
    fread(&infoHeader, sizeof(BMPInfoHeader), 1, file);

    fseek(file, header.dataOffset, SEEK_SET);

    int padding = (4 - (infoHeader.width * (infoHeader.bitsPerPixel / 8)) % 4) % 4;

    unsigned char *imageData = (unsigned char *)malloc(infoHeader.width * infoHeader.height * (infoHeader.bitsPerPixel / 8));

    fread(imageData, sizeof(unsigned char), infoHeader.width * infoHeader.height * (infoHeader.bitsPerPixel / 8), file);

    fclose(file);

    BMPImage bmp;
    bmp.header = header;
    bmp.infoHeader = infoHeader;
    bmp.imageData = imageData;

    return bmp;
}