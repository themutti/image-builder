#include <stdio.h>
#include "image-builder.h"

#define WIDTH 3
#define HEIGHT 2

int main() {
  Image *img;
  imgCreate(&img, WIDTH, HEIGHT);
  Pixel pxl = { 0xFF, 0xFF, 0xFF };
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      imgSetPixel(img, x, y, pxl);
    }
  }
  imgSave(img, "image.bmp", BMP);
  imgDelete(img);
  return 0;
}
