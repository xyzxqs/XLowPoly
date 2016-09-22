//
// Created by tsingshan on 9/22/16.
//

#include <stdlib.h>
#include "low_poly.h"
#include "array_util.h"
#include "sobel.h"
#include "delaunay.h"

void call(int magnitude, int x, int y);

long get_random();


///////////////////

int *collectors;
int size_c;

int getTriangles(int *pixels, int size, int w, int h, int pointNum, int *result) {
    collectors = (int *) malloc(size * sizeof(int));
    sobel(pixels, w, h, &call);


    int *particles;
    int size_p = 0;
    particles = malloc((size + 200 + 8) * sizeof(int));
    for (int i = 0; i < 100; ++i) {
        size_p = array_add(particles, size_p, size_p, (int) (get_random() * w));
        size_p = array_add(particles, size_p, size_p, (int) (get_random() * h));
    }

    int len = size_c / pointNum;
    for (int i = 0; i < len; ++i) {
        int random = (int) (get_random() * size_c);
        size_p = array_add(particles, size_p, size_p, collectors[random]);
        size_c = array_remove(collectors, size_c, random);
    }

    size_p = array_add(particles, size_p, size_p, 0);
    size_p = array_add(particles, size_p, size_p, 0);

    size_p = array_add(particles, size_p, size_p, 0);
    size_p = array_add(particles, size_p, size_p, h);

    size_p = array_add(particles, size_p, size_p, w);
    size_p = array_add(particles, size_p, size_p, 0);

    size_p = array_add(particles, size_p, size_p, w);
    size_p = array_add(particles, size_p, size_p, h);

//    free(collectors);
//    free(particles);
    return 0;
}

void call(int magnitude, int x, int y) {
    if (magnitude > 40) {
        size_c = array_add(collectors, size_c, size_c, x);
        size_c = array_add(collectors, size_c, size_c, y);
    }
}

long get_random() {
    return random() / RAND_MAX;
}



