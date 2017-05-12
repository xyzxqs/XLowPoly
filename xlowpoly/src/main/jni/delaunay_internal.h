//
// Created by xyzxqs on 5/12/17.
//

#ifndef XLOWPOLY_DELAUNAY_INTERNAL_H
#define XLOWPOLY_DELAUNAY_INTERNAL_H

#include "point.h"
#include "delaunay.h"

//debugging will  affect performance seriously
#define DEBUG_DELAUNAY 0

//Local Optimization Procedure
#define USE_LOP 0

typedef struct Arc_ {
    //vector:<nock --> arrow>, nock_index > arrow_index
    int nock_vertex;
    int arrow_vertex;
    struct Arc_ *next;
} Arc;

typedef struct Triangle_ {
    Arc *subtense;
    struct Triangle_ *next;
} Triangle;

typedef struct {
    const Point *vertices;
    //arcs linked lists heads array
    Arc **arcs_heads;
    //triangles linked lists heads array
    Triangle **triangles_heads;
    //array.length = vertices.length = size_vertices + 4 (super-square)
    int length;
} TriNet;

//Independent Triangle, do not need to get vertex from the TriNet,
//use for temporary linked list.
typedef struct AngNode_ {
    int vertex;
    Arc *subtense;
    struct AngNode_ *next;
} AngNode;

typedef struct ArcNode_ {
    Arc *arc;
    struct ArcNode_ *next;
} ArcNode;


TriNet *net_init(Point *vertices, int size_vertices, int w, int h);

void trinet_point_add(const int target_point_index, const TriNet *triNet);

void arc_add(const TriNet *net, int start_vertex, int end_vertices);

void arc_remove(Arc *head, int end_vertices);

void triangle_add(int index_vertex, Arc *subtense, const TriNet *net);

void triangle_remove(int index_vertex, Arc *subtense, const TriNet *net);

void arces_free(Arc *head);

void triangles_free(Triangle *head);

void net_free(TriNet *tri_net);

bool in_circumcircle(const int target_point_index, const int vertex, const Arc *arc,
                     const TriNet *net);

#if USE_LOP

void LOP(AngNode *target_arc, const TriNet *net);

#endif

void angnode_add(AngNode *head, int vertex, Arc *subtense);

void angnode_free(AngNode *head);

void arcnode_add(ArcNode *head, Arc *arc);

void arcnode_remove(ArcNode *head, Arc *arc);

void arcnode_free(ArcNode *head);

void pnode_unique_add(PNode *head, int index);

void pnode_add(PNode *head, int index);

void pnode_free(PNode *head);

Arc *get_arc(Arc *head, int end);

#if DEBUG_DELAUNAY

void _print_triNet(const TriNet *triNet);

void _print_angnode(const AngNode *head, const TriNet *net);

void _print_arcnode(const ArcNode *head);

void _print_pointnode(const PNode *head);

#endif
#endif //XLOWPOLY_DELAUNAY_INTERNAL_H
