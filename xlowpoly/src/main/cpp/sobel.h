//
// Created by xyzxqs on 9/21/16.
//

#ifndef XLOWPOLY_SOBEL_H
#define XLOWPOLY_SOBEL_H

//if define ALPHA_CHANNEL, then contain alpha channel.
#define ALPHA_CHANNEL

#include <stdbool.h>
#include "point.h"


typedef bool (*Filter)(int magnitude, int x, int y);

void sobel(const int *pixel, int w, int h, Filter filter, Point *points, int *len);


#endif //XLOWPOLY_SOBEL_H
