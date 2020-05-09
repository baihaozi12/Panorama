//
// Created by Hao Bai on 2020/5/9.
//
#include "panorama_check.h"
#include <android/log.h>

extern "C"{
JNIEXPORT jboolean JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_Pano(JNIEnv *,
                                                                         jobject,
                                                                         jobject,
                                                                         jint);
Java_com_data100_taskmobile_ui_main_activity_MainActivity_Return_Pano(JNIEnv *,
                                                                        jobject,
                                                                        jobject,
                                                                        jint);

Java_com_data100_taskmobile_ui_main_activity_MainActivity_Release(JNIEnv *,
jobject,
jobject,
jint);
}
#ifndef PANORAMA_PANORAMA_JNI_H
#define PANORAMA_PANORAMA_JNI_H

#endif //PANORAMA_PANORAMA_JNI_H
