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
// Created by xyzxqs on 9/24/16.
//

#ifndef XLOWPOLY_POINT_H
#define XLOWPOLY_POINT_H

#include <stdbool.h>

typedef struct {
    int x;
    int y;
} Point;

bool point_remove(Point *array, int *size, int index);

#endif //XLOWPOLY_POINT_H
