#include <stdio.h>
#include <stdlib.h>
#include "image-builder.h"


int imgCreate(Image **img, int width, int height) {
  *img = (Image*) malloc(sizeof(Image));
  if (!img) {
    return 0;
  }
  (*img)->width = width;
  (*img)->height = height;
  (*img)->pixels = (Pixel*) calloc(width * height, sizeof(Pixel));
  if (!(*img)->pixels) {
    return 0;
  }
  return 1;
}

int imgSetPixel(Image *img, int x, int y, Pixel pixel) {
  if (x < 0 || x >= img->width || y < 0 || y >= img->height) {
    return 0;
  }
  img->pixels[img->width * y + x] = pixel;
  return 1;
}

int imgSave(Image *img, const char *file_name, Format format) {
  FILE *fp = fopen(file_name, "w");
  if (!fp) {
    return 0;
  }
  switch (format) {
    case BMP: {
      break;
    }
    default: {
      fclose(fp);
      return 0;
    }
  }
  fclose(fp);
  return 1;
}

void imgDelete(Image *img) {
  free(img->pixels);
  free(img);
}
