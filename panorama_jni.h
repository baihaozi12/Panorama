//
// Created by Hao Bai on 2020/5/9.
//
#include "panorama_check.h"
#include "stitch.h"
#include <android/log.h>

extern "C"{
JNIEXPORT jintArray JNICALL
Java_com_trax_jcall_AlgorithmNativeCarrier_generateResult(JNIEnv *,
                                                                         jobject,
                                                                         jobject,
                                                                         jint);

JNIEXPORT jint JNICALL
Java_com_trax_jcall_AlgorithmNativeCarrier_resetStitch(JNIEnv *,jobject);

JNIEXPORT jint JNICALL
Java_com_trax_jcall_AlgorithmNativeCarrier_rollBack(JNIEnv *,jobject);


}
#ifndef PANORAMA_PANORAMA_JNI_H
#define PANORAMA_PANORAMA_JNI_H

#endif //PANORAMA_PANORAMA_JNI_H
