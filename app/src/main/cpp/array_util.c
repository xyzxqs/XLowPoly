//
// Created by tsingshan on 9/22/16.
//

#include "array_util.h"

int array_add(int *array, int size, int index, int value) {
    if (index >= size) {
        array[size] = value;
    } else {
        for (int i = size; i > index; --i) {
            array[i] = array[i - 1];
        }
        array[index] = value;
    }

    ++size;
    return size;
}

int array_remove(int *array, int size, int index) {
    if (index >= size) {
        return size;
    } else {
        for (int i = index; i < size; ++i) {
            array[i] = array[i + 1];
        }
        array[size] = 0;

        --size;
        return size;
    }
}



