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
// Created by xyzxqs on 9/22/16.
//

#ifndef XLOWPOLY_LOW_POLY_H
#define XLOWPOLY_LOW_POLY_H

#ifdef __cplusplus
extern "C" {
#endif //__cplusplus

void get_triangles(const int *pixels, int size_pixels, int w, int h, int threshold,
                   float alpha_pointcount, int *result, int *size_result, unsigned char lowpoly);


#ifdef __cplusplus
};
#endif //__cplusplus

#endif //XLOWPOLY_LOW_POLY_H
