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

#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "delaunay.h"
#include "_log.h"
#include "delaunay_internal.h"


/////////////////////

//Intrinsically, this func is sort, but result_size > vertices_size
void triangulate(Point *vertices, int size_vertices, int w, int h, PNode *head) {
    TriNet *triNet = net_init(vertices, size_vertices, w, h);
    for (int i = 0; i < size_vertices; ++i) {
        trinet_point_add(i, triNet);
    }
    Triangle **pTriangle = triNet->triangles_heads;
    for (int i = 0, n = triNet->length; i < n; i++) {
        Triangle *arc_head = pTriangle[i];
        for (Triangle *p = arc_head->next; p != NULL;) {
            int v1 = p->subtense->arrow_vertex;
            int v2 = p->subtense->nock_vertex;
            pnode_add(head, i);
            pnode_add(head, v1);
            pnode_add(head, v2);
            p = p->next;
        }
    }
    net_free(triNet);
}

TriNet *net_init(Point *vertices, int size_vertices, int w, int h) {
    TriNet *triNet = (TriNet *) malloc(sizeof(TriNet));
    triNet->length = size_vertices + 4;
    triNet->arcs_heads = (Arc **) malloc(sizeof(Arc *) * (size_vertices + 4));
    triNet->triangles_heads = (Triangle **) malloc(sizeof(Triangle *) * (size_vertices + 4));
    triNet->vertices = vertices;

    for (int i = 0; i < size_vertices + 4; ++i) {
        (triNet->arcs_heads)[i] = (Arc *) malloc(sizeof(Arc));
        (triNet->arcs_heads)[i]->next = NULL;
        (triNet->arcs_heads)[i]->arrow_vertex = -1;
        (triNet->triangles_heads)[i] = (Triangle *) malloc(sizeof(Triangle));
        (triNet->triangles_heads)[i]->next = NULL;
        (triNet->triangles_heads)[i]->subtense = NULL;
    }

    Point *p = &(vertices[size_vertices]);
    p->x = 0;
    p->y = 0;

    p = &(vertices[size_vertices + 1]);
    p->x = 0;
    p->y = h - 1;

    p = &(vertices[size_vertices + 2]);
    p->x = w - 1;
    p->y = 0;

    p = &(vertices[size_vertices + 3]);
    p->x = w - 1;
    p->y = h - 1;

#if DEBUG_DELAUNAY
    for (int i = 0; i < size_vertices + 4; ++i) {
        _log_i("delaunay", "-->node%d:(%d,%d)", i, vertices[i].x, vertices[i].y);
    }
#endif
    arc_add(triNet, size_vertices + 1, size_vertices);
    arc_add(triNet, size_vertices + 2, size_vertices);
    arc_add(triNet, size_vertices + 2, size_vertices + 1);
    arc_add(triNet, size_vertices + 3, size_vertices + 1);
    arc_add(triNet, size_vertices + 3, size_vertices + 2);

    triangle_add(size_vertices + 2,
                 get_arc(triNet->arcs_heads[size_vertices + 1], size_vertices),
                 triNet);
    triangle_add(size_vertices + 3,
                 get_arc(triNet->arcs_heads[size_vertices + 2], size_vertices + 1),
                 triNet);
    return triNet;
}

void trinet_point_add(const int target_point_index, const TriNet *triNet) {
#if DEBUG_DELAUNAY
    _log_d("delaunay", "start trinet_point_add node %d", target_point_index);
    _print_triNet(triNet);
    _log_d("delaunay", "遍历图中已有三角形,获取影响三角形链表");
#endif
    AngNode *angs_head = (AngNode *) malloc(sizeof(AngNode));
    angs_head->subtense = NULL;
    angs_head->vertex = -1;
    angs_head->next = NULL;
    for (int vertex = 0, n = triNet->length; vertex < n; vertex++) {
        Triangle *head = triNet->triangles_heads[vertex];
        if (head != NULL) {
            for (Triangle *p = head->next; p != NULL;) {
                if (in_circumcircle(target_point_index, vertex, p->subtense, triNet)) {
                    angnode_add(angs_head, vertex, p->subtense);
                }
                p = p->next;
            }

        } else {
            _log_e("delaunay", "point_add: head can not be NULL");
        }
    }
#if DEBUG_DELAUNAY
    _print_angnode(angs_head, triNet);
    _log_d("delaunay", "遍历影响三角形链表，删除影响三角形，获取公共边链表,非公共边链表和待连接点链表");
#endif
    ArcNode *arcs_head = (ArcNode *) malloc(sizeof(ArcNode));
    arcs_head->next = NULL;
    arcs_head->arc = NULL;

    PNode *points_head = (PNode *) malloc(sizeof(PNode));
    points_head->next = NULL;
    points_head->index = -1;

#if DEBUG_DELAUNAY
    _log_d("delaunay", "->1.把三角形的<点边>换成<边边边>,无重复添加待连接点链表，同时删除影响三角形");
#endif
    for (AngNode *p = angs_head->next; p != NULL;) {
        triangle_remove(p->vertex, p->subtense, triNet);
        int nock = p->subtense->nock_vertex;
        int arrow = p->subtense->arrow_vertex;
        arcnode_add(arcs_head, p->subtense);
        Arc *head = (triNet->arcs_heads)[p->vertex];
        pnode_unique_add(points_head, p->vertex);
        for (Arc *pa = head->next; pa != NULL;) {
            if (pa->arrow_vertex == arrow) {
                arcnode_add(arcs_head, pa);
                pnode_unique_add(points_head, pa->arrow_vertex);
            }
            if (pa->arrow_vertex == nock) {
                arcnode_add(arcs_head, pa);
                pnode_unique_add(points_head, pa->arrow_vertex);
            }
            pa = pa->next;
        }
        p = p->next;
    }
    angnode_free(angs_head);
    free(angs_head);
    angs_head = NULL;
#if DEBUG_DELAUNAY
    _print_pointnode(points_head);
    _print_triNet(triNet);
    _log_d("delaunay", "->2.找到公共边链表");
#endif
    ArcNode *comm_arcs_head = (ArcNode *) malloc(sizeof(ArcNode));
    comm_arcs_head->next = NULL;
    comm_arcs_head->arc = NULL;
    for (ArcNode *p = arcs_head->next; p != NULL;) {
        for (ArcNode *np = p->next; np != NULL;) {
            if (p->arc == np->arc) {
                arcnode_add(comm_arcs_head, p->arc);
            }
            np = np->next;
        }
        p = p->next;
    }
#if DEBUG_DELAUNAY
    _print_arcnode(comm_arcs_head);
    _log_d("delaunay", "->3.找到非公共边链表");
#endif
    for (ArcNode *p = comm_arcs_head->next; p != NULL;) {
        for (ArcNode *pd = arcs_head->next; pd != NULL;) {
            if (pd->arc == p->arc) {
                arcnode_remove(arcs_head, pd->arc);
                break;
            }
            pd = pd->next;
        }
        p = p->next;
    }
#if DEBUG_DELAUNAY
    _print_arcnode(arcs_head);
    _log_d("delaunay", "遍历公共边链表删除公共边");
#endif
    for (ArcNode *p = comm_arcs_head->next; p != NULL;) {
        Arc *ah = triNet->arcs_heads[p->arc->nock_vertex];
        arc_remove(ah, p->arc->arrow_vertex);
        p = p->next;
    }
    arcnode_free(comm_arcs_head);
    free(comm_arcs_head);
    comm_arcs_head = NULL;
#if DEBUG_DELAUNAY
    _print_triNet(triNet);
    _log_d("delaunay", "遍历待连接点链表添加新的边");
#endif
    for (PNode *p = points_head->next; p != NULL;) {
        arc_add(triNet, target_point_index, p->index);
        p = p->next;
    }
    pnode_free(points_head);
    free(points_head);
    points_head = NULL;
#if DEBUG_DELAUNAY
    _print_triNet(triNet);
    _log_d("delaunay", "遍历非重复边链表添加三角形并获取新三角形链表");
#endif

#if USE_LOP
    AngNode *new_ang_head = (AngNode *) malloc(sizeof(AngNode));
    new_ang_head->next = NULL;
    new_ang_head->vertex = -1;
    new_ang_head->subtense = NULL;
#endif

    for (ArcNode *p = arcs_head->next; p != NULL;) {
        triangle_add(target_point_index, p->arc, triNet);
#if USE_LOP
        angnode_add(new_ang_head, target_point_index, p->arc);
#endif
        p = p->next;
    }
    arcnode_free(arcs_head);
    free(arcs_head);
    arcs_head = NULL;
#if USE_LOP
#if DEBUG_DELAUNAY
    _print_angnode(new_ang_head, triNet);
    _print_triNet(triNet);
    _log_d("delaunay", "遍历新获取三角形链表进行LOP优化");
#endif
    for (AngNode *p = new_ang_head->next; p != NULL;) {
        LOP(p, triNet);
        p = p->next;
    }
    angnode_free(new_ang_head);
    free(new_ang_head);
    new_ang_head = NULL;
#endif

#if DEBUG_DELAUNAY
    _log_d("delaunay", "end trinet_point_add node %d", target_point_index);
#endif
}

void arc_add(const TriNet *net, int start_vertex, int end_vertices) {
    Arc *head = net->arcs_heads[start_vertex];
    if (head == NULL) {
        _log_e("delaunay", "arc_add: head can not be NULL");
    } else {
        Arc *arc = (Arc *) malloc(sizeof(Arc));
        arc->nock_vertex = start_vertex;
        arc->arrow_vertex = end_vertices;
        arc->next = head->next;
        head->next = arc;
    }
}

void arc_remove(Arc *head, int end_vertices) {
    if (head == NULL) {
        _log_e("delaunay", "arc_remove: can not be NULL");
        return;
    } else {
        for (Arc *p = head; p->next != NULL;) {
            if (p->next->arrow_vertex == end_vertices) {
                Arc *pn = p->next;
                p->next = pn->next;
                free(pn);
            } else {
                p = p->next;
            }
        }
    }
}

void triangle_add(int index_vertex, Arc *subtense, const TriNet *net) {
    Triangle *head = net->triangles_heads[index_vertex];
    if (head == NULL) {
        _log_e("delaunay", "triangle_add head can not be NULL");
        return;
    } else {
        Triangle *angle = (Triangle *) malloc(sizeof(Triangle));
        angle->subtense = subtense;
        angle->next = head->next;
        head->next = angle;
    }
}

void triangle_remove(int index_vertex, Arc *subtense, const TriNet *net) {
    Triangle *head = net->triangles_heads[index_vertex];
    for (Triangle *p = head; p->next != NULL;) {
        if (p->next->subtense == subtense) {
            Triangle *pn = p->next;
            p->next = pn->next;
            free(pn);
        } else {
            p = p->next;
        }
    }
}

void arces_free(Arc *head) {
    if (head == NULL) {
        _log_e("delaunay", "arces_free: head can not be NULL");
        return;
    } else {
        Arc *pn = NULL;
        for (Arc *p = head; p->next != NULL;) {
            pn = p->next;
            p->next = pn->next;
            free(pn);
        }
    }
}

void triangles_free(Triangle *head) {
    if (head == NULL) {
        _log_e("delaunay", "arces_free: head can not be NULL");
        return;
    } else {
        Triangle *pn = NULL;
        for (Triangle *p = head; p->next != NULL;) {
            pn = p->next;
            p->next = pn->next;
            free(pn);
        }
    }
}

void net_free(TriNet *net) {
    for (int i = 0, n = net->length; i < n; ++i) {
        arces_free(net->arcs_heads[i]);
        free(net->arcs_heads[i]);
        triangles_free(net->triangles_heads[i]);
        free(net->triangles_heads[i]);
    }
    free(net);
}

bool in_circumcircle(const int target_point_index, const int vertex, const Arc *arc,
                     const TriNet *net) {
    int arrow = arc->arrow_vertex;
    int nock = arc->nock_vertex;
    const Point p = net->vertices[target_point_index];
    const Point v1 = net->vertices[vertex];
    const Point v2 = net->vertices[arrow];
    const Point v3 = net->vertices[nock];

    float w = 2 * (v2.x - v1.x);
    float h = 2 * (v2.y - v1.y);
    float a = 2 * (v3.x - v2.x);
    float t = 2 * (v3.y - v2.y);
    float f = powf(v2.x, 2.0f) + powf(v2.y, 2.0f);
    float f_ = powf(v1.x, 2.0f) + powf(v1.y, 2.0f) - f;
    float f__ = f - powf(v3.x, 2.0f) - powf(v3.y, 2.0f);
    float u = (f__ * h - f_ * t) / (t * w - h * a);
    float c = (w * f__ - a * f_) / (a * h - w * t);
    float k = powf(v1.x - u, 2.0f) + powf(v1.y - c, 2.0f);

#if DEBUG_DELAUNAY
    bool in_c = powf(p.x - u, 2.0f) + powf(p.y - c, 2.0f) < k;
    _log_d("delaunay", "in_circumcircle :(%d) <%d, %d, %d>|%s", target_point_index,
           vertex, nock, arrow, in_c ? "true" : "false");
    return in_c;
#else
    return powf(p.x - u, 2.0f) + powf(p.y - c, 2.0f) < k;
#endif
}

#if USE_LOP

void LOP(AngNode *target_arc, const TriNet *net) {
    //Unwanted
    _log_w("delaunay", "LOP not impl");
}

#endif

void angnode_add(AngNode *head, int vertex, Arc *subtense) {
    if (head == NULL) {
        _log_e("delaunay", "angnode_add: head can not be NULL");
        return;
    } else {
        AngNode *node = (AngNode *) malloc(sizeof(AngNode));
        node->vertex = vertex;
        node->subtense = subtense;
        node->next = head->next;
        head->next = node;
    }
}

void angnode_free(AngNode *head) {
    if (head == NULL) {
        _log_e("delaunay", "angnode_free: head can not be NULL");
    } else {
        AngNode *pn = NULL;
        for (AngNode *p = head; p->next != NULL;) {
            pn = p->next;
            p->next = pn->next;
            free(pn);
        }
    }
}

void arcnode_add(ArcNode *head, Arc *arc) {
    if (head == NULL) {
        _log_e("delaunay", "arcnode_add: head can not be NULL");
        return;
    } else {
        ArcNode *node = (ArcNode *) malloc(sizeof(ArcNode));
        node->arc = arc;
        node->next = head->next;
        head->next = node;
    }
}

void arcnode_remove(ArcNode *head, Arc *arc) {
    if (head == NULL) {
        _log_e("delaunay", "arcnode_remove: head can not be NULL");
        return;
    } else {
        for (ArcNode *p = head; p->next != NULL;) {
            if (p->next->arc == arc) {
                ArcNode *pn = p->next;
                p->next = pn->next;
                free(pn);
            } else {
                p = p->next;
            }
        }
    }
}

void arcnode_free(ArcNode *head) {
    if (head == NULL) {
        _log_e("delaunay", "arcnode_free: head can not be NULL");
        return;
    } else {
        ArcNode *pn = NULL;
        for (ArcNode *p = head; p->next != NULL;) {
            pn = p->next;
            p->next = pn->next;
            free(pn);
        }
    }
}

void pnode_unique_add(PNode *head, int index) {
    bool has = false;
    for (PNode *p = head->next; p != NULL;) {
        if (p->index == index) {
            has = true;
            break;
        }
        p = p->next;
    }
    if (!has) {
        PNode *node = (PNode *) malloc(sizeof(PNode));
        node->index = index;
        node->next = head->next;
        head->next = node;
    }
}

void pnode_free(PNode *head) {
    if (head == NULL) {
        _log_e("delaunay", "arcnode_free: head can not be NULL");
        return;
    } else {
        PNode *pn = NULL;
        for (PNode *p = head; p->next != NULL;) {
            pn = p->next;
            p->next = pn->next;
            free(pn);
        }
    }
}

Arc *get_arc(Arc *head, int end) {
    if (head == NULL) {
        _log_e("delaunay", "get_arc: head can not be NULL");
        return NULL;
    } else {
        for (Arc *p = head->next; p != NULL;) {
            if (p->arrow_vertex == end) {
                return p;
            }
            p = p->next;
        }
    }
    _log_e("delaunay", "get_arc: not found");
    return NULL;
}

void pnode_add(PNode *head, int index) {
    if (head == NULL) {
        _log_e("delaunay", "pnode_add: head can not be NULL");
    } else {
        PNode *node = (PNode *) malloc(sizeof(PNode));
        node->index = index;
        node->next = head->next;
        head->next = node;
    }
}

#if DEBUG_DELAUNAY

void _print_triNet(const TriNet *triNet) {
    _log_d("delaunay", "start _print_triNet");
    _log_d("delaunay", "arc: ");
    Arc **pArc = triNet->arcs_heads;
    for (int i = 0, n = triNet->length; i < n; i++) {
        _log_d("delaunay", "TriNet--> node %d:", i);
        Arc *arc_head = pArc[i];
        for (Arc *p = arc_head->next; p != NULL;) {
            _log_d("delaunay", "TriNet-------> %d-%d  :%x", i, p->arrow_vertex, p);
            p = p->next;
        }
    }
    _log_d("delaunay", "triangle: ");
    Triangle **pTriangle = triNet->triangles_heads;
    for (int i = 0, n = triNet->length; i < n; i++) {
        _log_d("delaunay", "TriNet--> node %d:", i);
        Triangle *arc_head = pTriangle[i];
        for (Triangle *p = arc_head->next; p != NULL;) {
            int v1 = p->subtense->arrow_vertex;
            int v2 = p->subtense->nock_vertex;
            _log_d("delaunay", "TriNet-------> <%d, %d, %d>", i, v2, v1);
            p = p->next;
        }
    }
    _log_d("delaunay", "end _print_triNet");
}

void _print_angnode(const AngNode *head, const TriNet *net) {
    _log_d("delaunay", "start _print_angnode");
    if (head != NULL) {
        for (AngNode *p = head->next; p != NULL;) {
            _log_d("delaunay", "<%d,%d,%d>",
                   p->vertex, p->subtense->nock_vertex, p->subtense->arrow_vertex);
            p = p->next;
        }
    } else {
        _log_e("delaunay", "_print_angnode...");
    }
    _log_d("delaunay", "end _print_angnode");
}

void _print_arcnode(const ArcNode *head) {
    _log_d("delaunay", "start _print_arcnode");
    if (head != NULL) {
        for (ArcNode *p = head->next; p != NULL;) {
            _log_d("delaunay", "%d-%d", p->arc->nock_vertex, p->arc->arrow_vertex);
            p = p->next;
        }
    } else {
        _log_e("delaunay", "_print_arcnode...");
    }
    _log_d("delaunay", "end _print_arcnode");
}

void _print_pointnode(const PNode *head) {
    _log_d("delaunay", "start _print_pointnode");
    if (head != NULL) {
        for (PNode *p = head->next; p != NULL;) {
            _log_d("delaunay", "(%d)", p->index);
            p = p->next;
        }
    } else {
        _log_e("delaunay", "_print_pointnode...");
    }
    _log_d("delaunay", "end _print_pointnode");
}

#endif
