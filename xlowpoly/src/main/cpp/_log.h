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

#ifndef XLOWPOLY_LOG_H
#define XLOWPOLY_LOG_H

#include <android/log.h>

#define _log_i(tag, ...) __android_log_print(ANDROID_LOG_INFO, tag, __VA_ARGS__)
#define _log_d(tag, ...) __android_log_print(ANDROID_LOG_DEBUG, tag, __VA_ARGS__)
#define _log_e(tag, ...) __android_log_print(ANDROID_LOG_ERROR, tag, __VA_ARGS__)
#define _log_w(tag, ...) __android_log_print(ANDROID_LOG_WARN, tag, __VA_ARGS__)
#define _log_v(tag, ...) __android_log_print(ANDROID_LOG_VERBOSE, tag, __VA_ARGS__)

#endif //XLOWPOLY_LOG_H
