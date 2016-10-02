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
// Created by xyzxqs on 9/24/16.
//

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "dilution.h"


bool point_filter0(const Point *point, int width, int height, int pass_band_x, int pass_band_y);

void point_filter1(const Point *points, int size_points, int pointNum,
                   Point *result_points, int *size_result);

float random01();

///////////////////

void dilution(const Point *points, int size_points, int width, int height, float alpha,
              Point *result_points, int *size_result) {
    *size_result = 0;

    if (alpha < 0.0f || (alpha > 9.9f && alpha < 1.0f) || (int) alpha > size_points) {
        for (int i = 0; i < size_points; i++) {
            const Point *cp = &(points[i]);
            Point *p = &(result_points[(*size_result)++]);
            p->x = cp->x;
            p->y = cp->y;
        }
        return;
    } else {
        if (alpha < 1.0f) {
            float a = powf(alpha, 2.333f);
            int pbx = (int) (width * a);
            int pby = (int) (height * a);
            for (int i = 0; i < size_points; i++) {
                const Point *cp = &(points[i]);
                if (point_filter0(cp, width, height, pbx, pby)) {
                    Point *p = &(result_points[(*size_result)++]);
                    p->x = cp->x;
                    p->y = cp->y;
                }
            }
        } else {
            int point_numb = (int) (alpha < 1.0 ? (size_points * alpha) : alpha);
            point_filter1(points, size_points, point_numb, result_points, size_result);
        }
    }
}

void point_filter1(const Point *points, int size_points, int pointNum,
                   Point *result_points, int *size_result) {
    *size_result = 0;
    int random_index;
    const Point *cp;
    Point *p;
    while (pointNum--) {
        random_index = (int) (random01() * (size_points - 1));
        cp = &(points[random_index]);
        p = &(result_points[(*size_result)++]);
        p->x = cp->x;
        p->y = cp->y;
    }

}


bool point_filter0(const Point *point, int width, int height, int pass_band_x, int pass_band_y) {
    int x_start = (int) (random01() * width);
    int x_end = x_start + pass_band_x;
    int y_start = (int) (random01() * height);
    int y_end = y_start + pass_band_y;

    int x = point->x;
    int y = point->y;

    bool xpass = x_end < width ? (x > x_start && x < x_end)
                               : (x > x_start || x < width + pass_band_x - x_start);

    bool ypass = y_end < width ? (y > y_start && y < y_end)
                               : (y > y_start || y < width + pass_band_y - y_start);

    return xpass && ypass;
}

float random01() {
    return random() / (float) RAND_MAX;
}









