/*
 *  Copyright 2016 xyzxqs (xyzxqs@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

//
// Created by xyzxqs on 9/21/16.
//
#include <math.h>
#include "sobel.h"
#include "_log.h"

int color_average(const int *pixel, int w, int h, int x, int y);

//////////////////////

int const sobelOperatorX[3][3] = {{-1, 0, 1},
                                  {-2, 0, 2},
                                  {-1, 0, 1}};
int const sobelOperatorY[3][3] = {{-1, -2, -1},
                                  {0,  0,  0},
                                  {1,  2,  1}};


void sobel(const int *pixel, int w, int h, Filter filter, Point *points, int *len) {
    *len = 0;
    int size = w * h / 2;
    int i = 0;
    for (int y = 1; y < h; ++y) {
        for (int x = 1; x < w; ++x) {
            int pixelX = (
                    (sobelOperatorX[0][0] * color_average(pixel, w, h, x - 1, y - 1)) +
                    (sobelOperatorX[0][1] * color_average(pixel, w, h, x, y - 1)) +
                    (sobelOperatorX[0][2] * color_average(pixel, w, h, x + 1, y - 1)) +

                    (sobelOperatorX[1][0] * color_average(pixel, w, h, x - 1, y)) +
                    (sobelOperatorX[1][1] * color_average(pixel, w, h, x, y)) +
                    (sobelOperatorX[1][2] * color_average(pixel, w, h, x + 1, y)) +

                    (sobelOperatorX[2][0] * color_average(pixel, w, h, x - 1, y + 1)) +
                    (sobelOperatorX[2][1] * color_average(pixel, w, h, x, y + 1)) +
                    (sobelOperatorX[2][2] * color_average(pixel, w, h, x + 1, y + 1))
            );

            int pixelY = (
                    (sobelOperatorY[0][0] * color_average(pixel, w, h, x - 1, y - 1)) +
                    (sobelOperatorY[0][1] * color_average(pixel, w, h, x, y - 1)) +
                    (sobelOperatorY[0][2] * color_average(pixel, w, h, x + 1, y - 1)) +

                    (sobelOperatorY[1][0] * color_average(pixel, w, h, x - 1, y)) +
                    (sobelOperatorY[1][1] * color_average(pixel, w, h, x, y)) +
                    (sobelOperatorY[1][2] * color_average(pixel, w, h, x + 1, y)) +

                    (sobelOperatorY[2][0] * color_average(pixel, w, h, x - 1, y + 1)) +
                    (sobelOperatorY[2][1] * color_average(pixel, w, h, x, y + 1)) +
                    (sobelOperatorY[2][2] * color_average(pixel, w, h, x + 1, y + 1))
            );

            int magnitude = (int) sqrt(pixelX * pixelX + pixelY * pixelY);
            if ((*filter)(magnitude, x, y)) {
                int index = i++;
                if (index < size) {
                    *(len) = i;
                    Point *p = &(points[index]);
                    p->x = x;
                    p->y = y;
                } else {
                    _log_e("sobel", "out of bound (w=%d,h=%d)(x=%d,y=%d) index=%d", w, h, x, y,
                           index);
                    return;
                }
            }
        }
    }
}

int color_average(const int *pixel, int w, int h, int x, int y) {
    if (x >= w || y >= h) {
        return 0;
    }
    int color = pixel[w * y + x];
    int blue = color & 0xFF;
    int green = (color >> 8) & 0xFF;
    int red = (color >> 16) & 0xFF;
#ifdef ALPHA_CHANNEL
    int alpha = (color >> 24) & 0xFF;
    float a = alpha / 255.0f;
    float sum = (blue + green + red) * a;
    return (int) (sum / 3);
#else
    return (blue + green + red) / 3;
#endif
}





