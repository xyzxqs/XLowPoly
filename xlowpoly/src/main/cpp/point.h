//
// Created by xyzxqs on 9/24/16.
//

#ifndef XLOWPOLY_POINT_H
#define XLOWPOLY_POINT_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Point;

bool point_remove(Point *array, int *size, int index);

#endif //XLOWPOLY_POINT_H
