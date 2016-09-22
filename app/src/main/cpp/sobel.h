//
// Created by tsingshan on 9/21/16.
//

#ifndef XLOWPOLY_SOBEL_H
#define XLOWPOLY_SOBEL_H

typedef void (*Call_back)(int magnitude, int x, int y);

void sobel(int *pixel, int w, int h, Call_back call_back);

#endif //XLOWPOLY_SOBEL_H
