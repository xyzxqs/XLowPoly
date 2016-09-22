#include <jni.h>
#include <string>

#ifdef __cplusplus
extern "C" {
#endif
#include "low_poly.h"


JNIEXPORT jintArray JNICALL
Java_io_github_xyzxqs_apps_xlowpoly_LowPoly_getTriangles(JNIEnv *env, jclass type,
                                                         jintArray pixels_, jint width, jint height,
                                                         jint pointNum) {
    jint *pixels = env->GetIntArrayElements(pixels_, NULL);
    jint size = env->GetArrayLength(pixels_);

    jintArray tmpArray_ = env->NewIntArray(size);
    jint *tmpArray = env->GetIntArrayElements(tmpArray_, NULL);

    size = getTriangles(pixels, size, width, height, pointNum, tmpArray);

    env->ReleaseIntArrayElements(pixels_, pixels, 0);

    jintArray result = env->NewIntArray(size);

    env->SetIntArrayRegion(result, 0, size, tmpArray);

    env->ReleaseIntArrayElements(tmpArray_, tmpArray, 0);
    return result;
}


#ifdef __cplusplus
};
#endif
