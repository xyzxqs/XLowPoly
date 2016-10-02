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