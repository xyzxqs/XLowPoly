//
// Created by xyzxqs on 9/26/16.
//

#include "point.h"

bool point_remove(Point *array, int *size, int index) {
    if (index >= *size) {
        return false;
    } else {
        for (int i = index; i < *size; ++i) {
            array[i] = array[i + 1];
        }
        --(*size);
        return true;
    }
}