#include <jni.h>
#include "react-native-rssdk.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_rssdk_RssdkModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return rssdk::multiply(a, b);
}
