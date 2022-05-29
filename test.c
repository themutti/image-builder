#include <stdio.h>
#include "image-builder.h"

#define WIDTH 3
#define HEIGHT 2

const Pixel pixels[HEIGHT][WIDTH] = {
  {{ 0xFF, 0x00, 0x00 }, { 0x00, 0xFF, 0x00 }, { 0x00, 0x00, 0xFF }},
  {{ 0x00, 0x00, 0x00 }, { 0xFF, 0x00, 0xFF }, { 0xFF, 0xFF, 0xFF }}
};

int main() {
  Image *img;
  imgCreate(&img, WIDTH, HEIGHT);
  for (int y = 0; y < HEIGHT; y++) {
    for (int x = 0; x < WIDTH; x++) {
      imgSetPixel(img, x, y, pixels[y][x]);
    }
  }
  imgSave(img, "image.bmp", BMP);
  imgDelete(img);
  return 0;
}
