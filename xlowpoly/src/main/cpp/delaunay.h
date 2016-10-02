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
// Created by xyzxqs (xyzxqs@gmail.com) on 9/22/16.
//

#ifndef XLOWPOLY_DELAUNAY_H
#define XLOWPOLY_DELAUNAY_H

#include "point.h"

typedef struct PointNode_ {
    int index;
    struct PointNode_ *next;
} PNode;

void pnode_free(PNode *head);

//vertices.length should >= size_vertices
void triangulate(Point *vertices, int size_vertices, int w, int h, PNode *head);

#endif //XLOWPOLY_DELAUNAY_H
