#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "panorama_check.h"

using namespace cv;
using namespace std;


vector<String> img_names = {"/home/baihao/Stitch/try_new/1.jpeg", "/home/baihao/Stitch/try_new/2.jpeg", "/home/baihao/Stitch/try_new/3.jpeg"};
int main()
{
    int num_images = static_cast<int>(img_names.size());

    Mat pre_frame = imread(img_names[0]);
    if (pre_frame.empty()){
        return -2;
    }
    // store each image feature data
//    vector<featuredata_pano> feature_data_list;
//    vector<MatchesInfo> pairwise_matches;
//    vector<ImageFeatures> features;
//    // get first image
//    featuredata_pano feature_pano;
//    get_combined_feature(feature_pano,pre_frame, 0);
//    feature_data_list.push_back(feature_pano);
//    features.push_back(feature_pano.features) ;
//    Mat result_img;
//    vector<Mat> full_imgs;
//
//    full_imgs.push_back(pre_frame);
    vector<string> image_names_temp;
    store_each all_param;
//    all_param.img_names.push_back(img_names[0]);
    all_param.full_imgs.push_back(pre_frame);
    all_param = generate_result(all_param, 0);
    for (int i = 1; i < num_images; ++i)
    {
        Mat pre_frame = imread(img_names[i]);
        all_param.full_imgs.push_back(pre_frame);

        all_param = generate_result(all_param, i);
    }

    return 1;
}

//int main() {
//    //读取视频或摄像头
//    VideoCapture capture(0);
//    Mat pre_frame;
//    capture >> pre_frame;
//    while (true) {
//        Mat curr_frame;
//        capture >> curr_frame;
//        if (curr_frame.empty()){
//            cout << "not read the frame\n";
//            return 1;
//        }
//        imshow("读取视频", curr_frame);
//        waitKey(30);    //延时30
//        curr_frame.copyTo(pre_frame);
//    }
//    return 0;
//}