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

#include "point.h"

#ifndef XLOWPOLY_SPARSE_H
#define XLOWPOLY_SPARSE_H

void dilution(const Point *points, int size_points, int width, int height, float alpha,
              Point *result_points, int *size_result);

#endif //XLOWPOLY_SPARSE_H
