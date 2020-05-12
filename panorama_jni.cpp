//
// Created by Hao Bai on 2020/5/9.
//

#include "panorama_jni.h"

store_each *all_param = new store_each();
// store_each all_param_result;
extern "C" {
jintArray matToBitmapArray(JNIEnv *env, const cv::Mat &image) {
    jintArray resultImage = env->NewIntArray(image.total()+2);
    jint *_data = new jint[image.total()+2];
    for (int i = 0; i < image.total(); i++) {
        char r = image.data[3 * i + 2];
        char g = image.data[3 * i + 1];
        char b = image.data[3 * i + 0];
        char a = (char) 255;
        _data[i] = (((jint) a << 24) & 0xFF000000) + (((jint) r << 16) & 0x00FF0000) +
                   (((jint) g << 8) & 0x0000FF00) + ((jint) b & 0x000000FF);
    }
    _data[image.total()+1] = image.rows;
    _data[image.total()] = image.cols;
    env->SetIntArrayRegion(resultImage, 0, image.total()+2, _data);
    delete[]_data;

    return resultImage;
}



JNIEXPORT jintArray JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_generateResult(JNIEnv *env,
                                                                         jobject obj,
                                                                         jobject image,
                                                                         jint image_num) {
    try {
        jclass jmat = (env)->FindClass("org/opencv/core/Mat");
        jmethodID getNativeObjAddr = (env)->GetMethodID(jmat, "getNativeObjAddr", "()J");
        jlong getimage = (env)->CallLongMethod(image, getNativeObjAddr, NULL);
        Mat myimage = Mat();
        myimage = *(Mat *) getimage;
//        jintArray result = matToBitmapArray(env, myimage);
//        return result;
        if (myimage.empty()) {
            jbyteArray errorArray = env->NewByteArray(1);
            return errorArray;
        }
        store_each temop_all_param(*all_param);
        all_param->full_imgs.push_back(myimage);
        generate_result(*all_param, image_num);
        myimage.release();
        if (image_num == 0) {
            jintArray zeroArray = env->NewIntArray(1);
            return zeroArray;
        }
// if status is 1 error re run
        if (all_param->status == 1) {
            *all_param = temop_all_param;
            jintArray errorArray = env->NewIntArray(1);

            return errorArray;
        } else if (all_param->status == 0) {
            jintArray result = matToBitmapArray(env, all_param->result_stitched_img);

            return result;
        }

    } catch (...) {
        jintArray errorArray = env->NewIntArray(1);
        return errorArray;
    }

}
}
