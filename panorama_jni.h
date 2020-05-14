//
// Created by Hao Bai on 2020/5/9.
//
#include "panorama_check.h"
#include "stitch.h"
#include <android/log.h>

extern "C"{
JNIEXPORT jintArray JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_generateResult(JNIEnv *,
                                                                         jobject,
                                                                         jobject,
                                                                         jint);

JNIEXPORT jintArray JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_Reset(JNIEnv *,
                                                                jobject);

JNIEXPORT jintArray JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_RollBack(JNIEnv *,
                                                                jobject);

//JNIEXPORT jintArray JNICALL
//Java_com_data100_taskmobile_ui_main_activity_MainActivity_DeleteAndFree(JNIEnv *,
//                                                                   jobject);

}
#ifndef PANORAMA_PANORAMA_JNI_H
#define PANORAMA_PANORAMA_JNI_H

#endif //PANORAMA_PANORAMA_JNI_H
