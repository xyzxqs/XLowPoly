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
