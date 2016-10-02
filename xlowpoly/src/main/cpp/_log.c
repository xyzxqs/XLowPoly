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









