//
// Created by xyzxqs on 9/26/16.
//

#include <android/log.h>
#include "_log.h"

void _log_v(const char *tag, const char *fmt, ...) {
#ifdef PRINT_DEBUG_LOG
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_VERBOSE, tag, fmt, args);
    va_end(args);
#endif
}

void _log_d(const char *tag, const char *fmt, ...) {
#ifdef PRINT_DEBUG_LOG
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_DEBUG, tag, fmt, args);
    va_end(args);
#endif
}

void _log_i(const char *tag, const char *fmt, ...) {
#ifdef PRINT_DEBUG_LOG
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_INFO, tag, fmt, args);
    va_end(args);
#endif
}

void _log_w(const char *tag, const char *fmt, ...) {
#ifdef PRINT_DEBUG_LOG
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_WARN, tag, fmt, args);
    va_end(args);
#endif
}

void _log_e(const char *tag, const char *fmt, ...) {
#ifdef PRINT_DEBUG_LOG
    va_list args;
    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_ERROR, tag, fmt, args);
    va_end(args);
#endif
}









