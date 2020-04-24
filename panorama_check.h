//
// Created by Hao Bai on 2020/4/24.
//
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "opencv2/stitching/detail/blenders.hpp"
#include "opencv2/stitching/detail/camera.hpp"
#include "opencv2/stitching/detail/exposure_compensate.hpp"
#include "opencv2/stitching/detail/matchers.hpp"
#include "opencv2/stitching/detail/motion_estimators.hpp"
#include "opencv2/stitching/detail/seam_finders.hpp"
#include "opencv2/stitching/detail/warpers.hpp"
#include "opencv2/stitching/warpers.hpp"
#include "opencv2/xfeatures2d.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include "opencv2/opencv_modules.hpp"
#include <opencv2/core/utility.hpp>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/stitching/detail/autocalib.hpp"

#ifndef PANORAMA_PANORAMA_CHECK_H
#define PANORAMA_PANORAMA_CHECK_H

#endif //PANORAMA_PANORAMA_CHECK_H

using namespace cv;
using namespace cv::detail;
using namespace std;

struct featuredata_pano
{
    Mat resized_img;
    ImageFeatures features;
};

struct result_return{
    Mat result_img;

};

int get_combined_feature(featuredata_pano &result, Mat full_img, int img_idx);

void f2_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &f2_matches);

int match_features(vector<featuredata_pano> feature_data_list, vector<MatchesInfo> &pairwise_matches);

int estimate_homo(vector<featuredata_pano> featuredata_pano_list, vector<ImageFeatures> features, vector<MatchesInfo> pairwise_matches, vector<Mat> full_imgs, int step, Mat &result_img);

