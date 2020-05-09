//
// Created by Hao Bai on 2020/5/9.
//

#include "panorama_jni.h"

store_each all_param = new store_each();
extern "C" {
JNIEXPORT jboolean JNICALL
Java_com_data100_taskmobile_ui_main_activity_MainActivity_Pano(JNIEnv * env ,
                                jobject obj,
                                jobject image ,
                                jint image_num,
                                )
{
    try
    {
    jclass jmat = (env)->FindClass("org/opencv/core/Mat");
    jmethodID getNativeObjAddr = (env)->GetMethodID(jmat, "getNativeObjAddr", "()J");
    jlong getimage = (env)->CallLongMethod(image, getNativeObjAddr, NULL);
    Mat myimage = Mat();
    myimage = *(Mat *) getimage;

    if ( myimage.empty())
    {
    jint a = 0;
    return ( jboolean ) a;
    }

    all_param.full_imgs.push_back(myimage);
    all_param_result = generate_result(all_param, image_num);
    myimage.release();
    // if status is 1 error re run
    if (all_param_result.status == 1)
        {
            delete all_param_result;
            jint a = 0;
            return (jboolean)a;
        }
    else if (all_param_result.status == 1)
    {
        all_param = all_param_result;
        delete all_param_result;
        jint a = 1;
        return (jboolean)a;
    }

    }

}

Java_com_data100_taskmobile_ui_main_activity_MainActivity_Return_Pano(JNIEnv * env ,
                                                                    jobject obj)
                                                                    {
//    jclass jmat = (env)->FindClass("org/opencv/core/Mat");
//    jmethodID getNativeObjAddr = (env)->GetMethodID(jmat, "getNativeObjAddr", "()J");
//    jlong getimage = (env)->CallLongMethod(image, getNativeObjAddr, NULL);

    return all_param.result_stitched_img;

}

Java_com_data100_taskmobile_ui_main_activity_MainActivity_Release(){
    delete all_param
    return 0;
}
}