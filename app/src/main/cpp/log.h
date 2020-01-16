//
// Created by Administrator on 2019/8/26.
//

#ifndef NATIVEDEMO_LOG_H
#define NATIVEDEMO_LOG_H

#include <android/log.h>
#include <jni.h>

// 定义输出的TAG
#define LOG_TAG "log_native"
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)


#endif //NATIVEDEMO_LOG_H
