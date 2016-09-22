//
// Created by tsingshan on 9/22/16.
//

#include <stdint.h>
#include <math.h>
#include "delaunay.h"
#include "array_util.h"

const float EPSILON = 1.0f / 1048576.0f;
typedef struct {
    int i, j, k;
    float x, y, r;
} Circumcircle;

int dedup(int *edges, int size);

Circumcircle circumcircle(int **vertices, int v_size, int i, int j, int k);

int supertriangle(int **vertices, int v_size, int **result);

/////////////////


int triangulate(int **vertices, int v_size, int *result) {

    return 0;
}

int dedup(int *edges, int size) {
    int a, b, m, n;
    for (int j = size; j > 0;/**/) {
        if (j > size) {
            j = size;
        }

        if (j <= 0) {
            break;
        }

        b = edges[--j];
        a = edges[--j];

        for (int i = j; i > 0;) {
            n = edges[--i];
            m = edges[--i];

            if ((a == m && b == n) || (a == n && b == m)) {
                if (j + 1 < size) {
                    size = array_remove(edges, size, j + 1);
                }

                size = array_remove(edges, size, j);

                if (i + 1 < size) {
                    size = array_remove(edges, size, i + 1);
                }

                size = array_remove(edges, size, i);
                break;
            }
        }
    }
    return size;
}

Circumcircle circumcircle(int **vertices, int v_size, int i, int j, int k) {
    Circumcircle result;
    return result;
}

int supertriangle(int **vertices, int v_size, int **result) {
    int xmin = INT32_MAX;
    int ymin = INT32_MAX;
    int xmax = INT32_MIN;
    int ymax = INT32_MIN;

    float dx, dy, dmax, xmid, ymid;
    for (int i = (int) (v_size - 1); i >= 0; --i) {
        int *p = vertices[i];
        if (p[0] < xmin) xmin = p[0];
        if (p[0] > xmax) xmax = p[0];
        if (p[1] < ymin) ymin = p[1];
        if (p[1] > ymax) ymax = p[1];
    }

    dx = xmax - xmin;
    dy = ymax - ymin;

    dmax = fmaxf(dx, dy);

    xmid = (xmin + dx * 0.5f);
    ymid = (ymin + dy * 0.5f);
    return 0;
}







