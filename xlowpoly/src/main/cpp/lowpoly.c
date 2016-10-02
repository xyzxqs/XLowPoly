//
// Created by xyzxqs (xyzxqs@gmail.com) on 9/22/16.
//

#include <stdlib.h>
#include <stdbool.h>
#include "lowpoly.h"
#include "sobel.h"
#include "delaunay.h"
#include "dilution.h"
#include "dedup.h"
#include "_log.h"
#include "point.h"



//sobel callback madthod
bool call(int magnitude, int x, int y);

///////////////////

int threshold = 40;

void get_triangles(const int *pixels, int size, int w, int h, int thre, float alpha,
                   int *result, int *size_result, unsigned char lowpoly) {
    threshold = thre;

    Point *collectors = (Point *) malloc((size / 2 + 1) * sizeof(Point));
    int size_collectors = 0;

    sobel(pixels, w, h, &call, collectors, &size_collectors);

    Point *vertices = (Point *) malloc((size_collectors + 4) * sizeof(Point));
    int size_vertices = 0;

    dilution(collectors, size_collectors, w, h, alpha, vertices, &size_vertices);

    free(collectors);

    if (alpha > 1.0f) {
        dedup(vertices, &size_vertices);
    }
    if (lowpoly) {
        PNode *triangles = (PNode *) malloc(sizeof(PNode));
        triangles->index = -1;
        triangles->next = NULL;

        triangulate(vertices, size_vertices, w, h, triangles);

        *size_result = 0;
        for (PNode *p = triangles->next; p != NULL;) {
            Point *pi = &(vertices[p->index]);
            result[(*size_result)++] = pi->x;
            result[(*size_result)++] = pi->y;
            p = p->next;
        }
        free(vertices);

        pnode_free(triangles);
        free(triangles);
        triangles = NULL;
    } else {
        for (int i = 0; i < size_vertices; i++) {
            Point *pi = &(vertices[i]);
            result[(*size_result)++] = pi->x;
            result[(*size_result)++] = pi->y;
        }
    }
}

bool call(int magnitude, int x, int y) {
    if (magnitude > threshold) {
        return true;
    } else {
        return false;
    }
}






