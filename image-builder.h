#ifndef IMAGE_BUILDER_H
#define IMAGE_BUILDER_H

typedef enum Format { BMP } Format;

typedef struct Pixel {
  unsigned char r;
  unsigned char g;
  unsigned char b;
} Pixel;

typedef struct Image {
  int width;
  int height;
  Pixel *pixels;
} Image;

int imgCreate(Image **img, int width, int height);

int imgSetPixel(Image *img, int x, int y, Pixel pixel);

int imgSave(Image *img, const char *file_name, Format format);

void imgDelete(Image *img);

#endif
