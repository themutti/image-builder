#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "image-builder.h"


void decToHexArray(int dec, int hex_size, char hex[]) {
  for (int i = 0; i < hex_size; i++) {
    hex[i] = (dec >> 8*i) & 0xFF;
  }
}

void writeField(FILE *fp, int size, ...) {
  va_list ap;
  va_start(ap, size);
  for (int i = 0; i < size; i++) {
    fprintf(fp, "%c", va_arg(ap, int));
  }
  va_end(ap);
}

void buildBmp(FILE *fp, Image *img) {
  // BMP file structure: https://en.wikipedia.org/wiki/BMP_file_format
  char hex_buff[4];
  int padding = 4 - (img->width*3) % 4;

  // Format
  writeField(fp, 2, 0x42, 0x4D);
  // Size of the file
  decToHexArray(54 + img->width * img->height * 3 + img->width * padding, 4, hex_buff);
  writeField(fp, 4, hex_buff[0], hex_buff[1], hex_buff[2], hex_buff[3]);
  // Reserved
  writeField(fp, 4, 0x00, 0x00, 0x00, 0x00);
  // Offset of pixel array
  writeField(fp, 4, 0x36, 0x00, 0x00, 0x00);

  // Size of dib header
  writeField(fp, 4, 0x28, 0x00, 0x00, 0x00);
  // Width
  decToHexArray(img->width, 4, hex_buff);
  writeField(fp, 4, hex_buff[0], hex_buff[1], hex_buff[2], hex_buff[3]);
  // Height
  decToHexArray(img->height, 4, hex_buff);
  writeField(fp, 4, hex_buff[0], hex_buff[1], hex_buff[2], hex_buff[3]);
  // Number of color planes
  writeField(fp, 2, 0x01, 0x00);
  // Number of bits per pixel
  writeField(fp, 2, 0x18, 0x00);
  // Type of compression
  writeField(fp, 4, 0x00, 0x00, 0x00, 0x00);
  // Size of pixel array
  decToHexArray(img->width * img->height * 4, 4, hex_buff);
  writeField(fp, 4, hex_buff[0], hex_buff[1], hex_buff[2], hex_buff[3]);
  // Horizontal resolution
  writeField(fp, 4, 0x13, 0x0B, 0x00, 0x00);
  // Vertical resolution
  writeField(fp, 4, 0x13, 0x0B, 0x00, 0x00);
  // Number of colors in the palette
  writeField(fp, 4, 0x00, 0x00, 0x00, 0x00);
  // Number of important colors
  writeField(fp, 4, 0x00, 0x00, 0x00, 0x00);

  // Pixel array
  for (int y = img->height-1; y >= 0; y--) {
    for (int x = 0; x < img->width; x++) {
      Pixel pxl = img->pixels[img->width*y + x];
      writeField(fp, 3, pxl.b, pxl.g, pxl.r);
    }
    // Padding to make each line of pixels a multiple of 4
    for (int i = 0; i < padding; i++) {
      writeField(fp, 1, 0x00);
    }
  }
}


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
      buildBmp(fp, img);
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
