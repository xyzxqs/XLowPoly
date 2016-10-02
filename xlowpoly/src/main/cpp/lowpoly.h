//
// Created by xyzxqs on 9/22/16.
//

#ifndef XLOWPOLY_LOW_POLY_H
#define XLOWPOLY_LOW_POLY_H

void get_triangles(const int *pixels, int size_pixels, int w, int h, int threshold,
                   float alpha_pointcount, int *result, int *size_result, unsigned char lowpoly);

#endif //XLOWPOLY_LOW_POLY_H
