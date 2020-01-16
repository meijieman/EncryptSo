//
// Created by Administrator on 2020/1/16.
//

#include "auth.h"

#include <string.h>
#include <stdio.h>
#include "log.h"
#include "zip_util.h"

/**
 * http api 授权 key ，由服务端提供
 */
const char *AUTH_KEY = "0CC175B9C0F1B6A831C399E269772661";

/**
 * 发布的app 签名,只有和本签名一致的app 才会返回合法的 授权 key
 */
const char *RELEASE_SIGN = "308201dd30820146020101300d06092a864886f70d010105050030373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b3009060355040613025553301e170d3138303933303130333331315a170d3438303932323130333331315a30373116301406035504030c0d416e64726f69642044656275673110300e060355040a0c07416e64726f6964310b300906035504061302555330819f300d06092a864886f70d010101050003818d0030818902818100b3824043ab2201a14aa50f53ff2fa0b2e075e56186273bb6986ab2f5120d5c3342ae4a2b234f60caa4eea1ea9fa7fbd6a518c13fda94655020f8e1bb43667663afe3b8cc49b772eed46e19f9c855feca847a46b5cdf5f27419ca0a30db6d33e0133f7ebbc44e6be9ec23ec70c62829315d7201ddd64dbfd146b5a223899dec250203010001300d06092a864886f70d01010505000381810002f34c225ae7f798fd5e89f8f008ac1ccc52b44e8dfd313721ce24afa027c46d8465564b920aa8790aca1fe7d21bfc79eeacd287c0e41de3ec313400c94f9539a3f3d979924bac9a19d773234f22798941969118d3f4bb31f5873702221c66bc621ea420ae035ec3e812a654f901ef68853e7ec1ccd0f547da3a546eff2424b7";

/**
 * 本库文件版本号，每次打包需要更新
 */
const char *VERSION = "1.0.0";
/**
 * 拿到传入的app  的 签名信息，对比合法的app 签名，防止so文件被未知应用盗用
 */
static jclass contextClass;
static jclass signatureClass;
static jclass packageNameClass;
static jclass packageInfoClass;

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL
Java_com_lzpd_encryptso_JNI_getAuthKey(JNIEnv *env, jobject obj, jobject contextObject) {

    jmethodID getPackageManagerId = (env)->GetMethodID(contextClass, "getPackageManager",
                                                       "()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameId = (env)->GetMethodID(contextClass, "getPackageName",
                                                    "()Ljava/lang/String;");
    jmethodID signToStringId = (env)->GetMethodID(signatureClass, "toCharsString",
                                                  "()Ljava/lang/String;");
    jmethodID getPackageInfoId = (env)->GetMethodID(packageNameClass, "getPackageInfo",
                                                    "(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jobject packageManagerObject = (env)->CallObjectMethod(contextObject, getPackageManagerId);
    jstring packNameString = (jstring) (env)->CallObjectMethod(contextObject, getPackageNameId);
    LOGW("pkgName %s", env->GetStringUTFChars(packNameString, nullptr));

    jobject packageInfoObject = (env)->CallObjectMethod(packageManagerObject, getPackageInfoId,
                                                        packNameString, 64);
    jfieldID signaturefieldID = (env)->GetFieldID(packageInfoClass, "signatures",
                                                  "[Landroid/content/pm/Signature;");
    jobjectArray signatureArray = (jobjectArray) (env)->GetObjectField(packageInfoObject,
                                                                       signaturefieldID);
    jobject signatureObject = (env)->GetObjectArrayElement(signatureArray, 0);

    const char *signStrng = (env)->GetStringUTFChars(
            (jstring) (env)->CallObjectMethod(signatureObject, signToStringId), 0);
    // NDK层通过反射PackageManager获取签名信息进行对比，hook掉与PMS交互的IPackageManager即可完美破解
    if (strcmp(signStrng, RELEASE_SIGN) == 0) {
        LOGI("签名一致");
        //签名一致  返回合法的 api key，否则返回错误
        return (env)->NewStringUTF(AUTH_KEY);
    } else {
        LOGE("签名不一致");
        return (env)->NewStringUTF("error");
    }
}

// NDK层通过解压Apk包获取签名信息进行对比

JNIEXPORT jstring JNICALL
Java_com_lzpd_encryptso_JNI_getVer(JNIEnv *env, jclass clazz) {

    char *path = "";
    char *name = "";
    uncompress_apk(path, name);

    return env->NewStringUTF(VERSION);
}

JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK)
        return result;

    contextClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/Context"));
    signatureClass = (jclass) env->NewGlobalRef((env)->FindClass("android/content/pm/Signature"));
    packageNameClass = (jclass) env->NewGlobalRef(
            (env)->FindClass("android/content/pm/PackageManager"));
    packageInfoClass = (jclass) env->NewGlobalRef(
            (env)->FindClass("android/content/pm/PackageInfo"));


    //获取apk路径
    // android.app.ActivityThread
    jclass localClass = env->FindClass("android/app/ActivityThread");
    if (localClass != NULL) {
        jmethodID getapplication = env->GetStaticMethodID(localClass, "currentApplication",
                                                          "()Landroid/app/Application;");
        if (getapplication != NULL) {
            jobject application = env->CallStaticObjectMethod(localClass, getapplication);
            jclass context = env->GetObjectClass(application);
            jmethodID methodID_func = env->GetMethodID(context, "getPackageCodePath",
                                                       "()Ljava/lang/String;");
            jstring path = static_cast<jstring>(env->CallObjectMethod(application, methodID_func));
            const char *ch = env->GetStringUTFChars(path, 0);;
            LOGI("path %s, filename %s", env->GetStringUTFChars(path, nullptr), ch);
//            uncompress_apk(ch, "META-INF/CERT.RSA");//.SF
            env->ReleaseStringUTFChars(path, ch);
        }
    }

    return JNI_VERSION_1_4;
}

#ifdef __cplusplus
}
#endif
