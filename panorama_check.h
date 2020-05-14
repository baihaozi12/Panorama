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
//#include "opencv2/core/o"
//#include <>
//#include <boost/thread.hpp>
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

struct store_each{
    double work_megapix = 0.6;
    double seam_megapix = 0.1;
    double compose_megapix = -1;
    float conf_thresh = 1.f;
    float match_conf = 0.3f;
    float blend_strength = 5;
    double work_scale = 1;
    double seam_scale = 1;
    double compose_scale = 1;
    double seam_work_aspect = 1;
    bool is_work_scale_set = false;
    bool is_seam_scale_set = false;
    bool is_compose_scale_set = false;

    vector<Mat> full_imgs;
//    vector<string> img_names;
    vector<Size> full_img_sizes;
    vector<Mat> resized_imgs;
    ImageFeatures temp_feature;
    vector<ImageFeatures> features;
    vector<MatchesInfo> pairwise_matches;
    Ptr<FeaturesMatcher>  matcher = makePtr<BestOf2NearestMatcher>(false, match_conf);
    Ptr<Estimator> estimator = makePtr<HomographyBasedEstimator>();
    vector<CameraParams> cameras;
    Ptr<detail::BundleAdjusterBase> adjuster = makePtr<detail::BundleAdjusterRay>();
    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);

    vector<double> focals;
    float warped_image_scale;
//    Ptr<WarperCreator> warper_creator = makePtr<cv::PlaneWarper>();
    Ptr<WarperCreator> warper_creator = makePtr<cv::CylindricalWarper>();
//    Ptr<WarperCreator> warper_creator = makePtr<cv::FisheyeWarper>();
    //! 计算曝光度，调整图像曝光，减少亮度差异
    Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
    // 找接缝 图切割法
    Ptr<SeamFinder> seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR);
    // 不找了 朋友, 快一点
//    Ptr<SeamFinder> seam_finder = makePtr<detail::NoSeamFinder>();
    double compose_work_aspect = 1;

    Mat result_stitched_img;
    Mat result_stitched_img_mask;

    int status;
};


int get_combined_feature(featuredata_pano &result, Mat full_img, int img_idx);

void f2_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &f2_matches);

int match_features(vector<featuredata_pano> feature_data_list, vector<MatchesInfo> &pairwise_matches);

int estimate_homo(vector<featuredata_pano> featuredata_pano_list, vector<ImageFeatures> features, vector<MatchesInfo> pairwise_matches, vector<Mat> full_imgs, int step, Mat &result_img);

void i_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &pairwise_matches);

int generate_result(store_each &all_param, int index);
int generatePanoResult(store_each *all_param, int index);

store_each enmty_struct(store_each all_param);

int roll_back(store_each &all_param);

int free_it(store_each *all_param);
int reset_it(store_each &all_param);