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

#include <jni.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif

#include "lowpoly.h"

JNIEXPORT jintArray JNICALL
Java_io_github_xyzxqs_xlowpoly_LowPoly_getTriangles(JNIEnv *env, jclass type,
                                                    jintArray pixels_,
                                                    jint width,
                                                    jint height,
                                                    jint threshold,
                                                    jfloat alpha_count,
                                                    jboolean lowPoly) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);
    jint size = env->GetArrayLength(pixels_);

    jintArray tmpArray_ = env->NewIntArray(size);
    jint *tmpArray = env->GetIntArrayElements(tmpArray_, NULL);

    int tmpSize = 0;

    get_triangles(pixels, size, width, height, threshold, alpha_count, tmpArray, &tmpSize, lowPoly);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    jintArray result = env->NewIntArray(tmpSize);

    env->SetIntArrayRegion(result, 0, tmpSize, tmpArray);

    env->ReleaseIntArrayElements(tmpArray_, tmpArray, 0);
    return result;
}


#ifdef __cplusplus
};
#endif
