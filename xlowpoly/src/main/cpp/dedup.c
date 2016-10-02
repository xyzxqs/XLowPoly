//
// Created by xyzxqs on 9/26/16.
//

#include <stdlib.h>
#include "dedup.h"

int qsorter(const void *lft, const void *rft);

/////////////////////////

void dedup(Point *points, int *size) {
    Point *pl, *pr;
    qsort(points, (size_t)(*size), sizeof(Point), qsorter);
    for (int i = 0; i + 1 < (*size); ++i) {
        pl = &(points[i]);
        for (int j = i + 1; j + 1 < (*size); ++j) {
            pr = &(points[j]);
            if (pr->x == pl->x) {
                if (pr->y == pl->y) {
                    point_remove(points, size, j);
                    j--;
                } else {
                    break;
                }
            } else {
                break;
            }
        }
    }
}

int qsorter(const void *lft, const void *rft) {
    Point *l = (Point *) lft, *r = (Point *) rft;
    if ((l->x) == (r->x)) {
        return (l->y) - (r->y);
    } else {
        return (l->x) - (r->x);
    }
}