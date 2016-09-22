//
// Created by tsingshan on 9/21/16.
//
#include <math.h>
#include "sobel.h"

int const kernelX[3][3] = {{-1, 0, 1},
                           {-2, 0, 2},
                           {-1, 0, 1}};
int const kernelY[3][3] = {{-1, -2, -1},
                           {0,  0,  0},
                           {1,  2,  1}};

int get_avg(int *pixel, int w, int h, int x, int y);

void sobel(int *pixel, int w, int h, Call_back call_back) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            int pixelX = (
                    (kernelX[0][0] * get_avg(pixel, w, h, x - 1, y - 1)) +
                    (kernelX[0][1] * get_avg(pixel, w, h, x, y - 1)) +
                    (kernelX[0][2] * get_avg(pixel, w, h, x + 1, y - 1)) +

                    (kernelX[1][0] * get_avg(pixel, w, h, x - 1, y)) +
                    (kernelX[1][1] * get_avg(pixel, w, h, x, y)) +
                    (kernelX[1][2] * get_avg(pixel, w, h, x + 1, y)) +

                    (kernelX[2][0] * get_avg(pixel, w, h, x - 1, y + 1)) +
                    (kernelX[2][1] * get_avg(pixel, w, h, x, y + 1)) +
                    (kernelX[2][2] * get_avg(pixel, w, h, x + 1, y + 1))
            );

            int pixelY = (
                    (kernelY[0][0] * get_avg(pixel, w, h, x - 1, y - 1)) +
                    (kernelY[0][1] * get_avg(pixel, w, h, x, y - 1)) +
                    (kernelY[0][2] * get_avg(pixel, w, h, x + 1, y - 1)) +

                    (kernelY[1][0] * get_avg(pixel, w, h, x - 1, y)) +
                    (kernelY[1][1] * get_avg(pixel, w, h, x, y)) +
                    (kernelY[1][2] * get_avg(pixel, w, h, x + 1, y)) +

                    (kernelY[2][0] * get_avg(pixel, w, h, x - 1, y + 1)) +
                    (kernelY[2][1] * get_avg(pixel, w, h, x, y + 1)) +
                    (kernelY[2][2] * get_avg(pixel, w, h, x + 1, y + 1))
            );

            int magnitude = (int) sqrt(pixelX * pixelX + pixelY * pixelY);
            (*call_back)(magnitude, x, y);
        }
    }
}

int get_avg(int *pixel, int w, int h, int x, int y) {
    if (x >= w || y >= h) {
        return 0;
    }
    int color = pixel[w * y + x];
    int blue = color & 0xFF;
    int green = (color >> 8) & 0xFF;
    int red = (color >> 16) & 0xFF;
    return (blue + green + red) / 3;
}





