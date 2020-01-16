//
// Created by Administrator on 2020/1/16.
//

#include <jni.h>

#ifndef ENCRYPTSO_AUTH_H
#define ENCRYPTSO_AUTH_H

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_lzpd_encryptso_JNI_getAuthKey(JNIEnv *, jobject , jobject );


JNIEXPORT jstring JNICALL
Java_com_lzpd_encryptso_JNI_getVer(JNIEnv *env, jclass clazz);

#ifdef __cplusplus
}
#endif

#endif //ENCRYPTSO_AUTH_H
