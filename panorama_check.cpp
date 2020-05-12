//
// Created by Hao Bai on 2020/4/24.
//

#include "panorama_check.h"



//double work_scale = 1;
//double seam_scale = 1;
//double compose_scale = 1;
//double seam_work_aspect = seam_scale / work_scale;
//bool is_work_scale_set = false;
//double work_megapix;
//float conf_thresh = 1.f;
//bool is_compose_scale_set = false;
//float blend_strength = 5;
//bool is_seam_scale_set = false;
//double seam_megapix = 0.1;
//using namespace cv;
//using namespace cv::detail;

//int get_combined_feature(featuredata_pano &result, Mat full_img, int img_idx){
//    Ptr<Feature2D> finder =  cv::xfeatures2d::SiftFeatureDetector::create();
////    Size full_img_sizes = full_img.size();
//
//    // resize the img
//    resize(full_img, result.resized_img, Size(), work_scale, work_scale, INTER_LINEAR_EXACT);
////    ImageFeatures features;
//    if (!is_seam_scale_set)
//    {
//        seam_scale = min(1.0, sqrt(seam_megapix * 1e6 / full_img.size().area()));
//        seam_work_aspect = seam_scale / work_scale;
//        is_seam_scale_set = true;
//    }
//    computeImageFeatures(finder, result.resized_img, result.features);
//    result.features.img_idx = img_idx;
////    features = result.features;
//
//    return 0;
//
//}
//
//int match_features(vector<featuredata_pano> feature_data_list, vector<MatchesInfo> &pairwise_matches){
//    int num_images=feature_data_list.size ();
//    //1。串联匹配
//    vector<vector<MatchesInfo> > f2_2;//f2_2[i] 表示 i 和 i+1 的匹配关系（0 开头，比图像数小 1）
//    for (int i = 1; i < num_images; ++i){
//        vector<ImageFeatures> f2;
//        vector<MatchesInfo> m2;
//
//        f2.push_back (feature_data_list[i-1].features);
//        f2.push_back (feature_data_list[i].features);
//        f2_matcher(f2,m2);
//        f2_2.push_back(m2);
//    }
//
//    //2。把串联匹配 ----按opencv stitching 拼接的匹配关系组在一起
//    MatchesInfo f;//大小： n x n (n个图)
//    for (int i = 0; i < num_images; ++i)
//    {
//        for (int j = 0; j < num_images; ++j)
//        {
//            //cout<<"i,j:"<<i<<","<<j<<endl;
//            if(i==j)//自身不用匹配
//            {
//                f.src_img_idx = -1;
//                f.dst_img_idx = -1;
//                f.num_inliers = 0;
//                f.confidence = 0;
//                pairwise_matches.push_back (f);
//            }else if(i+1==j)//相连（顺）
//            {
//                pairwise_matches.push_back (f2_2[i][1]);
//                //修改匹配关系
//                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
//                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
//            }else if(j+1==i)//相连（倒）
//            {
//                pairwise_matches.push_back (f2_2[j][2]);
//                //修改匹配关系
//                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
//                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
//            }else//其它略过
//            {
//                f.src_img_idx = -1;
//                f.dst_img_idx = -1;
//                f.num_inliers = 0;
//                f.confidence = 0;
//                pairwise_matches.push_back (f);
//            }
//            //cout<<"size:"<<pairwise_matches.size ()<<endl;
//
//        }
//    }
//
//}
//
void f2_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &f2_matches)
{

    //vector<MatchesInfo> f2_matches;    //特征匹配
    BestOf2NearestMatcher matcher(false, 0.3f, 6, 6);    //定义特征匹配器，2NN方法
    matcher(features, f2_matches);    //进行特征匹配


}

//int estimate_homo(vector<featuredata_pano> featuredata_pano_list, vector<ImageFeatures> features, vector<MatchesInfo> pairwise_matches, vector<Mat> full_imgs, int step, Mat &result_img){
//
//    vector<int> indices = leaveBiggestComponent(features, pairwise_matches, conf_thresh);
//
//    vector<Mat> img_subset;
//    vector<Mat> full_images_subset;
////    vector<Size> full_img_sizes_subset;
//    for (size_t i = 0; i < indices.size(); ++i)
//    {
//        cout<< "indices '"<< indices[i] <<"'\n";
//        img_subset.push_back(featuredata_pano_list[indices[i]].resized_img);
//        full_images_subset.push_back(full_imgs[indices[i]]);
////        full_img_sizes_subset.push_back(full_img_sizes[indices[i]]);
//    }
//
//    vector<Mat> images = img_subset;
//    full_imgs = full_images_subset;
////    full_img_sizes = full_img_sizes_subset;
//    int num_images = static_cast<int>(images.size());
//    if (num_images < 2)
//    {
//        std::cout << "Need more images\n";
//        return -1;
//    }
//    //!(5) 估计 homography
//    Ptr<Estimator> estimator = makePtr<HomographyBasedEstimator>();
//    vector<CameraParams> cameras;
//    if (!(*estimator)(features, pairwise_matches, cameras))
//    {
//        cout << "Homography estimation failed.\n";
//        return -1;
//    }
//
//    for (size_t i = 0; i < cameras.size(); ++i)
//    {
//        Mat R;
//        cameras[i].R.convertTo(R, CV_32F);
//        cameras[i].R = R;
//        std::cout << "\nInitial camera intrinsics #" << indices[i] + 1 << ":\nK:\n" << cameras[i].K() << "\nR:\n" << cameras[i].R << std::endl;
//    }
//    //(6) 创建约束调整器
//    Ptr<detail::BundleAdjusterBase> adjuster = makePtr<detail::BundleAdjusterRay>();
//    adjuster->setConfThresh(conf_thresh);
//    Mat_<uchar> refine_mask = Mat::zeros(3, 3, CV_8U);
//    refine_mask(0, 0) = 1;
//    refine_mask(0, 1) = 1;
//    refine_mask(0, 2) = 1;
//    refine_mask(1, 1) = 1;
//    refine_mask(1, 2) = 1;
//    adjuster->setRefinementMask(refine_mask);
//    if (!(*adjuster)(features, pairwise_matches, cameras))
//    {
//        cout << "Camera parameters adjusting failed.\n";
//        return -1;
//    }
//    // Find median focal length
//    vector<double> focals;
//    for (size_t i = 0; i < cameras.size(); ++i)
//    {
//        focals.push_back(cameras[i].focal);
//    }
//
//    sort(focals.begin(), focals.end());
//    float warped_image_scale;
//    if (focals.size() % 2 == 1)
//        warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
//    else
//        warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;
//
//    std::cout << "\nWarping images (auxiliary)... \n";
//
//    vector<Point> corners(num_images);
//    vector<UMat> masks_warped(num_images);
//    vector<UMat> images_warped(num_images);
//    vector<Size> sizes(num_images);
//    vector<UMat> masks(num_images);
//
//    // Preapre images masks
//    for (int i = 0; i < num_images; ++i)
//    {
//        masks[i].create(images[i].size(), CV_8U);
//        masks[i].setTo(Scalar::all(255));
//    }
//
//    // Warp images and their masks
////    Ptr<WarperCreator> warper_creator = makePtr<cv::CylindricalWarper>();
//    Ptr<WarperCreator> warper_creator = makePtr<cv::PlaneWarper>();
//    if (!warper_creator)
//    {
//        cout << "Can't create the warper \n";
//        return 1;
//    }
//
//    //! Create RotationWarper
//    Ptr<RotationWarper> warper = warper_creator->create(static_cast<float>(warped_image_scale * seam_work_aspect));
//
////! Calculate warped corners/sizes/mask
//    for (int i = 0; i < num_images; ++i)
//    {
//        Mat_<float> K;
//        cameras[i].K().convertTo(K, CV_32F);
//        float swa = (float)seam_work_aspect;
//        K(0, 0) *= swa; K(0, 2) *= swa;
//        K(1, 1) *= swa; K(1, 2) *= swa;
//        corners[i] = warper->warp(images[i], K, cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
//        sizes[i] = images_warped[i].size();
//        warper->warp(masks[i], K, cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
//    }
//
//    vector<UMat> images_warped_f(num_images);
//    for (int i = 0; i < num_images; ++i)
//        images_warped[i].convertTo(images_warped_f[i], CV_32F);
//
//    std::cout << "Compensating exposure... \n";
//
//    //! 计算曝光度，调整图像曝光，减少亮度差异
//    Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
//    if (dynamic_cast<BlocksCompensator*>(compensator.get()))
//    {
//        BlocksCompensator* bcompensator = dynamic_cast<BlocksCompensator*>(compensator.get());
//        bcompensator->setNrFeeds(1);
//        bcompensator->setNrGainsFilteringIterations(2);
//        bcompensator->setBlockSize(32, 32);
//    }
//
//    compensator->feed(corners, images_warped, masks_warped);
//
//    Ptr<SeamFinder> seam_finder = makePtr<detail::GraphCutSeamFinder>(GraphCutSeamFinderBase::COST_COLOR);
//    seam_finder->find(images_warped_f, corners, masks_warped);
//
//    // Release unused memory
//    images.clear();
//    images_warped.clear();
//    images_warped_f.clear();
//    masks.clear();
//
//    Mat img_warped, img_warped_s;
//    Mat dilated_mask, seam_mask, mask, mask_warped;
//    Ptr<Blender> blender;
//    double compose_work_aspect = 1;
//
//    Mat img;
//    for (int img_idx = 0; img_idx < num_images; ++img_idx)
//    {
//        // Read image and resize it if necessary
//        Mat full_img = full_imgs[img_idx];
//        if (!is_compose_scale_set)
//        {
//            is_compose_scale_set = true;
//            compose_work_aspect = compose_scale / work_scale;
//
//            // Update warped image scale
//            warped_image_scale *= static_cast<float>(compose_work_aspect);
//            warper = warper_creator->create(warped_image_scale);
//
//            // Update corners and sizes
//            for (int i = 0; i < num_images; ++i)
//            {
//                cameras[i].focal *= compose_work_aspect;
//                cameras[i].ppx *= compose_work_aspect;
//                cameras[i].ppy *= compose_work_aspect;
//
//                Size sz = full_img.size();
//                Size ori_sz = sz;
//                if (std::abs(compose_scale - 1) > 1e-1)
//                {
//                    sz.width = cvRound(ori_sz.width * compose_scale);
//                    sz.height = cvRound(ori_sz.height * compose_scale);
//                }
//
//                Mat K;
//                cameras[i].K().convertTo(K, CV_32F);
//                Rect roi = warper->warpRoi(sz, K, cameras[i].R);
//
//                corners[i] = roi.tl();
//                sizes[i] = roi.size();
//            }
//        }
//
//        if (abs(compose_scale - 1) > 1e-1)
//            resize(full_img, img, Size(), compose_scale, compose_scale, INTER_LINEAR_EXACT);
//        else
//            img = full_img;
//        full_img.release();
//        Size img_size = img.size();
//
//        Mat K, R;
//        cameras[img_idx].K().convertTo(K, CV_32F);
//        R = cameras[img_idx].R;
//
//        // Warp the current image : img => img_warped
//        warper->warp(img, K, cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);
//
//        // Warp the current image mask
//        mask.create(img_size, CV_8U);
//        mask.setTo(Scalar::all(255));
//        warper->warp(mask, K, cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);
//
//        compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);
//        img_warped.convertTo(img_warped_s, CV_16S);
//        img_warped.release();
//        img.release();
//        mask.release();
//
//        dilate(masks_warped[img_idx], dilated_mask, Mat());
//        resize(dilated_mask, seam_mask, mask_warped.size(), 0, 0, INTER_LINEAR_EXACT);
//        mask_warped = seam_mask & mask_warped;
//
//        if (!blender)
//        {
//            blender = Blender::createDefault(Blender::MULTI_BAND, false);
//            Size dst_sz = resultRoi(corners, sizes).size();
//            float blend_width = sqrt(static_cast<float>(dst_sz.area())) * blend_strength / 100.f;
//            if (blend_width < 1.f){
//                blender = Blender::createDefault(Blender::NO, false);
//            }
//            else
//            {
//                MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(blender.get());
//                mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));
//            }
//            blender->prepare(corners, sizes);
//        }
//
//        blender->feed(img_warped_s, mask_warped, corners[img_idx]);
//    }
///* ===========================================================================*/
//    // Blend image
//    std::cout << "\nBlending ...\n";
//    Mat result, result_mask;
//    blender->blend(result, result_mask);
//
//    string output_path = "/home/baihao/Stitch/try_new/result"+to_string(step) +".jpeg";
//    imwrite(output_path, result);
//    result_img = result;
//    result_mask.release();
//    result.release();
////    img_warped_s.release();
////    mask_warped.release();
////    free(corners);
//}

store_each generate_result(store_each all_param, int index){



    all_param.work_megapix = 0.6;
    all_param.seam_megapix = 0.1;
    all_param.compose_megapix = -1;
    all_param.conf_thresh = 1.f;
    all_param.match_conf = 0.3f;
    all_param.blend_strength = 5;
    all_param.work_scale = 1;
    all_param.seam_scale = 1;
    all_param.compose_scale = 1;
    all_param.seam_work_aspect = 1;
    all_param.is_work_scale_set = false;
    all_param.is_seam_scale_set = false;
    all_param.is_compose_scale_set = false;
//
//    boos
    try {


    //    all_param.full_imgs.push_back(imread(all_param.img_names[index]));

        all_param.full_img_sizes.push_back(all_param.full_imgs[index].size()) ;

        if (!all_param.is_work_scale_set)
        {
            all_param.work_scale = min(1.0, sqrt(all_param.work_megapix * 1e6 / all_param.full_img_sizes[index].area()));
            all_param.is_work_scale_set = true;
        }

        Mat resized_img;
        resize(all_param.full_imgs[index],resized_img , Size(), all_param.work_scale, all_param.work_scale);

        if (!all_param.is_seam_scale_set)
        {
            all_param.seam_scale = min(1.0, sqrt(all_param.seam_megapix * 1e6 / all_param.full_img_sizes[index].area()));
            all_param.seam_work_aspect = all_param.seam_scale / all_param.work_scale;
            all_param.is_seam_scale_set = true;
        }
        Ptr<FeaturesFinder> finder;
//        finder = FeaturesFinder("S")
        finder = new SurfFeaturesFinder();
//
//        finder = makePtr<SiftFeaturesFinder>();
//        Ptr<Feature2D> finder =  cv::xfeatures2d::SiftFeatureDetector::create();
//cv::detail::
        (*finder)(resized_img, all_param.temp_feature);
        finder->collectGarbage();
//        computeImageFeatures(all_param.finder, resized_img, all_param.temp_feature);
        all_param.temp_feature.img_idx = index;
        all_param.features.push_back(all_param.temp_feature);
        // 拼接缝比例尺seam_scale
        resize(all_param.full_imgs[index], resized_img, Size(), all_param.seam_scale, all_param.seam_scale);
        all_param.resized_imgs.push_back(resized_img);
        resized_img.release();

        if(index == 0){
            return all_param;
        }
        // match each pair
        vector<MatchesInfo> new_match;
        all_param.pairwise_matches = new_match;
        new_match.clear();

    //    Ptr<FeaturesMatcher>  matcher = makePtr<BestOf2NearestMatcher>(false, all_param.match_conf);
    //    (*matcher)(all_param.features, all_param.pairwise_matches);
    //    matcher->collectGarbage();

        i_matcher(all_param.features, all_param.pairwise_matches);
        //! (4) 剔除外点，保留最确信的大成分
        // Leave only images we are sure are from the same panorama
        vector<int> indices = leaveBiggestComponent(all_param.features, all_param.pairwise_matches, all_param.conf_thresh);

        vector<Mat> img_subset;
    //    vector<String> img_names_subset;
        vector<Size> full_img_sizes_subset;
        for (size_t i = 0; i < indices.size(); ++i)
        {
            cout<< "indices '"<< indices[i] <<"'\n";
    //        img_names_subset.push_back(all_param.img_names[indices[i]]);
            img_subset.push_back(all_param.resized_imgs[indices[i]]);
            full_img_sizes_subset.push_back(all_param.full_img_sizes[indices[i]]);
        }

    //    all_param.img_names = img_names_subset;
        all_param.resized_imgs = img_subset;
        all_param.full_img_sizes = full_img_sizes_subset;

        // 及时清内存
    //    img_names_subset.clear();
        img_subset.clear();
        full_img_sizes_subset.clear();

        // Check if we still have enough images
        int num_images = static_cast<int>(all_param.full_imgs.size());
        if (num_images < 2)
        {
            // 及时报错
            throw   "Need more images\n";
    //        Exception;
        }

        //!(5) 估计 homography

        if (!(*all_param.estimator)(all_param.features, all_param.pairwise_matches, all_param.cameras))
        {
            throw   "Homography estimation failed.\n";
    //        return -1;
        }

        for (size_t i = 0; i < all_param.cameras.size(); ++i)
        {
            Mat R;
            all_param.cameras[i].R.convertTo(R, CV_32F);
            all_param.cameras[i].R = R;
            std::cout << "\nInitial camera intrinsics #" << indices[i] + 1 << ":\nK:\n" << all_param.cameras[i].K() << "\nR:\n" << all_param.cameras[i].R << std::endl;
            R.release();
        }
        all_param.adjuster->setConfThresh(all_param.conf_thresh);
        all_param.refine_mask(0, 0) = 1;
        all_param.refine_mask(0, 1) = 1;
        all_param.refine_mask(0, 2) = 1;
        all_param.refine_mask(1, 1) = 1;
        all_param.refine_mask(1, 2) = 1;
        all_param.adjuster->setRefinementMask(all_param.refine_mask);

        if (!(*all_param.adjuster)(all_param.features, all_param.pairwise_matches, all_param.cameras))
        {
            throw  "Camera parameters adjusting failed.\n";
        }

        // Find median focal length
        vector<double> focals;
        for (size_t i = 0; i < all_param.cameras.size(); ++i)
        {
            focals.push_back(all_param.cameras[i].focal);
        }
        sort(focals.begin(), focals.end());
        all_param.focals = focals;



        if (focals.size() % 2 == 1)
            all_param.warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
        else
            all_param.warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

        std::cout << "\nWarping images (auxiliary)... \n";

        vector<Point> corners(num_images);
        vector<UMat> masks_warped(num_images);
        vector<UMat> images_warped(num_images);
        vector<Size> sizes(num_images);
        vector<UMat> masks(num_images);

        for (int i = 0; i < num_images; ++i)
        {
            masks[i].create(all_param.resized_imgs[i].size(), CV_8U);
            masks[i].setTo(Scalar::all(255));
        }


        if (!all_param.warper_creator)
        {
            throw  "Can't create the warper \n";
    //        return 1;
        }
        //! Create RotationWarper
        Ptr<RotationWarper> warper = all_param.warper_creator->create(static_cast<float>(all_param.warped_image_scale * all_param.seam_work_aspect));

        //! Calculate warped corners/sizes/mask
        for (int i = 0; i < num_images; ++i)
        {
            Mat_<float> K;
            all_param.cameras[i].K().convertTo(K, CV_32F);
            float swa = (float)all_param.seam_work_aspect;
            K(0, 0) *= swa; K(0, 2) *= swa;
            K(1, 1) *= swa; K(1, 2) *= swa;
            corners[i] = warper->warp(all_param.resized_imgs[i], K, all_param.cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
            sizes[i] = images_warped[i].size();
            warper->warp(masks[i], K, all_param.cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
        }

        vector<UMat> images_warped_f(num_images);
        for (int i = 0; i < num_images; ++i)
            images_warped[i].convertTo(images_warped_f[i], CV_32F);

        std::cout << "Compensating exposure... \n";
        //! 计算曝光度，调整图像曝光，减少亮度差异
//        if (dynamic_cast<BlocksGainCompensator*>(all_param.compensator.get()))
//        {
//            BlocksGainCompensator* bcompensator = dynamic_cast<BlocksGainCompensator*>(all_param.compensator.get());
//            bcompensator->setNrFeeds(1);
//            bcompensator->setNrGainsFilteringIterations(2);
//            bcompensator->setBlockSize(32, 32);
//        }
//        Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
        all_param.compensator->feed(corners, images_warped, masks_warped);

        // 找接缝
        all_param.seam_finder->find(images_warped_f, corners, masks_warped);
        // Release unused memory
    //    images.clear();
        images_warped.clear();
        images_warped_f.clear();
        masks.clear();

        Mat img;
        Mat img_warped, img_warped_s;
        Mat dilated_mask, seam_mask, mask, mask_warped;
        Ptr<Blender> blender;


        for (int img_idx = 0; img_idx < num_images; ++img_idx)
        {
            // Read image and resize it if necessary
            Mat full_img = all_param.full_imgs[img_idx];
    //        string output_path = "/home/baihao/Stitch/try_new/img"+to_string(img_idx) +".jpeg";
    //        imwrite(output_path, full_img);
            if (!all_param.is_compose_scale_set)
            {
                all_param.is_compose_scale_set = true;
                all_param.compose_work_aspect = all_param.compose_scale / all_param.work_scale;

                // Update warped image scale
                all_param.warped_image_scale *= static_cast<float>(all_param.compose_work_aspect);
                warper = all_param.warper_creator->create(all_param.warped_image_scale);

                // Update corners and sizes
                for (int i = 0; i < num_images; ++i)
                {
                    all_param.cameras[i].focal *= all_param.compose_work_aspect;
                    all_param.cameras[i].ppx *= all_param.compose_work_aspect;
                    all_param.cameras[i].ppy *= all_param.compose_work_aspect;

                    Size sz = all_param.full_img_sizes[i];
                    if (std::abs(all_param.compose_scale - 1) > 1e-1)
                    {
                        sz.width = cvRound(all_param.full_img_sizes[i].width * all_param.compose_scale);
                        sz.height = cvRound(all_param.full_img_sizes[i].height * all_param.compose_scale);
                    }

                    Mat K;
                    all_param.cameras[i].K().convertTo(K, CV_32F);
                    Rect roi = warper->warpRoi(sz, K, all_param.cameras[i].R);

                    corners[i] = roi.tl();
                    sizes[i] = roi.size();
                    K.release();
                }

            }

            if (abs(all_param.compose_scale - 1) > 1e-1)
                resize(full_img, img, Size(), all_param.compose_scale, all_param.compose_scale);
            else
                img = full_img;

            full_img.release();
            Size img_size = img.size();

            Mat K, R;
            all_param.cameras[img_idx].K().convertTo(K, CV_32F);
            R = all_param.cameras[img_idx].R;

            // Warp the current image : img => img_warped
            warper->warp(img, K, all_param.cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

            // Warp the current image mask
            mask.create(img_size, CV_8U);
            mask.setTo(Scalar::all(255));
            warper->warp(mask, K, all_param.cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

            all_param.compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);
            img_warped.convertTo(img_warped_s, CV_16SC3);
            img_warped.release();
            img.release();
            mask.release();


            dilate(masks_warped[img_idx], dilated_mask, Mat());
            resize(dilated_mask, seam_mask, mask_warped.size(), 0, 0);
            mask_warped = seam_mask & mask_warped;

            if (!blender)
            {
                // 朋友使这个贼快，留着括号上面那个blender->prepare(corners, sizes)，剩下的都注释咯
//                blender = Blender::createDefault(Blender::NO, false);
                blender = Blender::createDefault(Blender::MULTI_BAND, false);
                Size dst_sz = resultRoi(corners, sizes).size();
                float blend_width = sqrt(static_cast<float>(dst_sz.area())) * all_param.blend_strength / 100.f;
                if (blend_width < 1.f){
                    blender = Blender::createDefault(Blender::NO, false);
                }
                else
                {
                    MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(blender.get());
                    mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));
                }
                blender->prepare(corners, sizes);
            }
    //        string output_path = "/home/baihao/Stitch/try_new/resultaaaaa"+to_string(img_idx) +".jpeg";
    //        imwrite(output_path, img_warped_s);
    //        output_path = "/home/baihao/Stitch/try_new/resultbbbbb"+to_string(img_idx) +".jpeg";
    //        imwrite(output_path, mask_warped);
            blender->feed(img_warped_s, mask_warped, corners[img_idx]);
        }
        /* ===========================================================================*/
        // Blend image
        std::cout << "\nBlending ...\n";
        Mat result, result_mask;
        blender->blend(result, result_mask);
//        imwrite("/home/baihao/Stitch/try_new/resultabc.jpg", result);
    //    imwrite("/home/baihao/Stitch/try_new/result_mask.jpg", result_mask);
//        imwrite("/AI/panoimg/result/resultabc.jpg", result);
        all_param.result_stitched_img = result;
        all_param.result_stitched_img_mask = result;
        all_param.status = 0;

        // 清内存
        result.release();
        result_mask.release();
        img.release();
        blender.release();
        img_warped.release();
        img_warped_s.release();
        dilated_mask.release();
        seam_mask.release();
        mask.release();
        warper.release();
        mask_warped.release();
        corners.clear();
        masks_warped.clear();
        sizes.clear();
        focals.clear();
//        all_param.
    } catch (Exception e1) {
        all_param.status = 1;
    }
    return all_param;

}

void i_matcher(vector<ImageFeatures> &features, vector<MatchesInfo> &pairwise_matches)
{
    int num_images=features.size ();
    //1。串联匹配
    vector<vector<MatchesInfo> > f2_2;//f2_2[i] 表示 i 和 i+1 的匹配关系（0 开头，比图像数小 1）
    for (int i = 1; i < num_images; ++i)
    {
        vector<ImageFeatures> f2;
        vector<MatchesInfo> m2;
        f2.push_back (features[i-1]);
        f2.push_back (features[i]);
        f2_matcher(f2,m2);
        f2_2.push_back(m2);
        f2.clear();
        m2.clear();
    }


    //2。把串联匹配 ----按opencv stitching 拼接的匹配关系组在一起
    MatchesInfo f;//大小： n x n (n个图)
    for (int i = 0; i < num_images; ++i)
    {
        for (int j = 0; j < num_images; ++j)
        {
            //cout<<"i,j:"<<i<<","<<j<<endl;
            if(i==j)//自身不用匹配
            {
                f.src_img_idx = -1;
                f.dst_img_idx = -1;
                f.num_inliers = 0;
                f.confidence = 0;
                pairwise_matches.push_back (f);
            }else if(i+1==j)//相连（顺）
            {
                pairwise_matches.push_back (f2_2[i][1]);
                //修改匹配关系
                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
            }else if(j+1==i)//相连（倒）
            {
                pairwise_matches.push_back (f2_2[j][2]);
                //修改匹配关系
                pairwise_matches[pairwise_matches.size ()-1].src_img_idx =i;
                pairwise_matches[pairwise_matches.size ()-1].dst_img_idx =j;
            }else//其它略过
            {
                f.src_img_idx = -1;
                f.dst_img_idx = -1;
                f.num_inliers = 0;
                f.confidence = 0;
                pairwise_matches.push_back (f);
            }
            //cout<<"size:"<<pairwise_matches.size ()<<endl;

        }
    }


    // 开始清理内存
    f2_2.clear();
//    f
//    delete f;
}

int generatePanoResult(store_each *all_param, int index){

    store_each *temp;

    all_param->work_megapix = 0.6;
    all_param->seam_megapix = 0.1;
    all_param->compose_megapix = -1;
    all_param->conf_thresh = 1.f;
    all_param->match_conf = 0.3f;
    all_param->blend_strength = 5;
    all_param->work_scale = 1;
    all_param->seam_scale = 1;
    all_param->compose_scale = 1;
    all_param->seam_work_aspect = 1;
    all_param->is_work_scale_set = false;
    all_param->is_seam_scale_set = false;
    all_param->is_compose_scale_set = false;
//
//    boos
    try {


        //    all_param.full_imgs.push_back(imread(all_param.img_names[index]));

        all_param->full_img_sizes.push_back(all_param->full_imgs[index].size()) ;

        if (!all_param->is_work_scale_set)
        {
            all_param->work_scale = min(1.0, sqrt(all_param->work_megapix * 1e6 / all_param->full_img_sizes[index].area()));
            all_param->is_work_scale_set = true;
        }

        Mat resized_img;
        resize(all_param->full_imgs[index],resized_img , Size(), all_param->work_scale, all_param->work_scale);

        if (!all_param->is_seam_scale_set)
        {
            all_param->seam_scale = min(1.0, sqrt(all_param->seam_megapix * 1e6 / all_param->full_img_sizes[index].area()));
            all_param->seam_work_aspect = all_param->seam_scale / all_param->work_scale;
            all_param->is_seam_scale_set = true;
        }
        Ptr<FeaturesFinder> finder;
//        finder = FeaturesFinder("S")
        finder = new SurfFeaturesFinder();
//
//        finder = makePtr<SiftFeaturesFinder>();
//        Ptr<Feature2D> finder =  cv::xfeatures2d::SiftFeatureDetector::create();
//cv::detail::
        (*finder)(resized_img, all_param->temp_feature);
        finder->collectGarbage();
//        computeImageFeatures(all_param.finder, resized_img, all_param.temp_feature);
        all_param->temp_feature.img_idx = index;
        all_param->features.push_back(all_param->temp_feature);
        // 拼接缝比例尺seam_scale
        resize(all_param->full_imgs[index], resized_img, Size(), all_param->seam_scale, all_param->seam_scale);
        all_param->resized_imgs.push_back(resized_img);
        resized_img.release();

        if(index == 0){
            return -1;
        }
        // match each pair
        vector<MatchesInfo> new_match;
        all_param->pairwise_matches = new_match;
        new_match.clear();

        //    Ptr<FeaturesMatcher>  matcher = makePtr<BestOf2NearestMatcher>(false, all_param.match_conf);
        //    (*matcher)(all_param.features, all_param.pairwise_matches);
        //    matcher->collectGarbage();

        i_matcher(all_param->features, all_param->pairwise_matches);
        //! (4) 剔除外点，保留最确信的大成分
        // Leave only images we are sure are from the same panorama
        vector<int> indices = leaveBiggestComponent(all_param->features, all_param->pairwise_matches, all_param->conf_thresh);

        vector<Mat> img_subset;
        //    vector<String> img_names_subset;
        vector<Size> full_img_sizes_subset;
        for (size_t i = 0; i < indices.size(); ++i)
        {
            cout<< "indices '"<< indices[i] <<"'\n";
            //        img_names_subset.push_back(all_param.img_names[indices[i]]);
            img_subset.push_back(all_param->resized_imgs[indices[i]]);
            full_img_sizes_subset.push_back(all_param->full_img_sizes[indices[i]]);
        }

        //    all_param.img_names = img_names_subset;
        all_param->resized_imgs = img_subset;
        all_param->full_img_sizes = full_img_sizes_subset;

        // 及时清内存
        //    img_names_subset.clear();
        img_subset.clear();
        full_img_sizes_subset.clear();

        // Check if we still have enough images
        int num_images = static_cast<int>(all_param->full_imgs.size());
        if (num_images < 2)
        {
            // 及时报错
            throw   "Need more images\n";
            //        Exception;
        }

        //!(5) 估计 homography

        if (!(*all_param->estimator)(all_param->features, all_param->pairwise_matches, all_param->cameras))
        {
            throw   "Homography estimation failed.\n";
            //        return -1;
        }

        for (size_t i = 0; i < all_param->cameras.size(); ++i)
        {
            Mat R;
            all_param->cameras[i].R.convertTo(R, CV_32F);
            all_param->cameras[i].R = R;
            std::cout << "\nInitial camera intrinsics #" << indices[i] + 1 << ":\nK:\n" << all_param->cameras[i].K() << "\nR:\n" << all_param->cameras[i].R << std::endl;
            R.release();
        }
        all_param->adjuster->setConfThresh(all_param->conf_thresh);
        all_param->refine_mask(0, 0) = 1;
        all_param->refine_mask(0, 1) = 1;
        all_param->refine_mask(0, 2) = 1;
        all_param->refine_mask(1, 1) = 1;
        all_param->refine_mask(1, 2) = 1;
        all_param->adjuster->setRefinementMask(all_param->refine_mask);

        if (!(*all_param->adjuster)(all_param->features, all_param->pairwise_matches, all_param->cameras))
        {
            throw  "Camera parameters adjusting failed.\n";
        }

        // Find median focal length
        vector<double> focals;
        for (size_t i = 0; i < all_param->cameras.size(); ++i)
        {
            focals.push_back(all_param->cameras[i].focal);
        }
        sort(focals.begin(), focals.end());
        all_param->focals = focals;



        if (focals.size() % 2 == 1)
            all_param->warped_image_scale = static_cast<float>(focals[focals.size() / 2]);
        else
            all_param->warped_image_scale = static_cast<float>(focals[focals.size() / 2 - 1] + focals[focals.size() / 2]) * 0.5f;

        std::cout << "\nWarping images (auxiliary)... \n";

        vector<Point> corners(num_images);
        vector<UMat> masks_warped(num_images);
        vector<UMat> images_warped(num_images);
        vector<Size> sizes(num_images);
        vector<UMat> masks(num_images);

        for (int i = 0; i < num_images; ++i)
        {
            masks[i].create(all_param->resized_imgs[i].size(), CV_8U);
            masks[i].setTo(Scalar::all(255));
        }


        if (!all_param->warper_creator)
        {
            throw  "Can't create the warper \n";
            //        return 1;
        }
        //! Create RotationWarper
        Ptr<RotationWarper> warper = all_param->warper_creator->create(static_cast<float>(all_param->warped_image_scale * all_param->seam_work_aspect));

        //! Calculate warped corners/sizes/mask
        for (int i = 0; i < num_images; ++i)
        {
            Mat_<float> K;
            all_param->cameras[i].K().convertTo(K, CV_32F);
            float swa = (float)all_param->seam_work_aspect;
            K(0, 0) *= swa; K(0, 2) *= swa;
            K(1, 1) *= swa; K(1, 2) *= swa;
            corners[i] = warper->warp(all_param->resized_imgs[i], K, all_param->cameras[i].R, INTER_LINEAR, BORDER_REFLECT, images_warped[i]);
            sizes[i] = images_warped[i].size();
            warper->warp(masks[i], K, all_param->cameras[i].R, INTER_NEAREST, BORDER_CONSTANT, masks_warped[i]);
        }

        vector<UMat> images_warped_f(num_images);
        for (int i = 0; i < num_images; ++i)
            images_warped[i].convertTo(images_warped_f[i], CV_32F);

        std::cout << "Compensating exposure... \n";
        //! 计算曝光度，调整图像曝光，减少亮度差异
//        if (dynamic_cast<BlocksGainCompensator*>(all_param.compensator.get()))
//        {
//            BlocksGainCompensator* bcompensator = dynamic_cast<BlocksGainCompensator*>(all_param.compensator.get());
//            bcompensator->setNrFeeds(1);
//            bcompensator->setNrGainsFilteringIterations(2);
//            bcompensator->setBlockSize(32, 32);
//        }
//        Ptr<ExposureCompensator> compensator = ExposureCompensator::createDefault(ExposureCompensator::GAIN_BLOCKS);
        all_param->compensator->feed(corners, images_warped, masks_warped);

        // 找接缝
        all_param->seam_finder->find(images_warped_f, corners, masks_warped);
        // Release unused memory
        //    images.clear();
        images_warped.clear();
        images_warped_f.clear();
        masks.clear();

        Mat img;
        Mat img_warped, img_warped_s;
        Mat dilated_mask, seam_mask, mask, mask_warped;
        Ptr<Blender> blender;


        for (int img_idx = 0; img_idx < num_images; ++img_idx)
        {
            // Read image and resize it if necessary
            Mat full_img = all_param->full_imgs[img_idx];
            //        string output_path = "/home/baihao/Stitch/try_new/img"+to_string(img_idx) +".jpeg";
            //        imwrite(output_path, full_img);
            if (!all_param->is_compose_scale_set)
            {
                all_param->is_compose_scale_set = true;
                all_param->compose_work_aspect = all_param->compose_scale / all_param->work_scale;

                // Update warped image scale
                all_param->warped_image_scale *= static_cast<float>(all_param->compose_work_aspect);
                warper = all_param->warper_creator->create(all_param->warped_image_scale);

                // Update corners and sizes
                for (int i = 0; i < num_images; ++i)
                {
                    all_param->cameras[i].focal *= all_param->compose_work_aspect;
                    all_param->cameras[i].ppx *= all_param->compose_work_aspect;
                    all_param->cameras[i].ppy *= all_param->compose_work_aspect;

                    Size sz = all_param->full_img_sizes[i];
                    if (std::abs(all_param->compose_scale - 1) > 1e-1)
                    {
                        sz.width = cvRound(all_param->full_img_sizes[i].width * all_param->compose_scale);
                        sz.height = cvRound(all_param->full_img_sizes[i].height * all_param->compose_scale);
                    }

                    Mat K;
                    all_param->cameras[i].K().convertTo(K, CV_32F);
                    Rect roi = warper->warpRoi(sz, K, all_param->cameras[i].R);

                    corners[i] = roi.tl();
                    sizes[i] = roi.size();
                    K.release();
                }

            }

            if (abs(all_param->compose_scale - 1) > 1e-1)
                resize(full_img, img, Size(), all_param->compose_scale, all_param->compose_scale);
            else
                img = full_img;

            full_img.release();
            Size img_size = img.size();

            Mat K, R;
            all_param->cameras[img_idx].K().convertTo(K, CV_32F);
            R = all_param->cameras[img_idx].R;

            // Warp the current image : img => img_warped
            warper->warp(img, K, all_param->cameras[img_idx].R, INTER_LINEAR, BORDER_REFLECT, img_warped);

            // Warp the current image mask
            mask.create(img_size, CV_8U);
            mask.setTo(Scalar::all(255));
            warper->warp(mask, K, all_param->cameras[img_idx].R, INTER_NEAREST, BORDER_CONSTANT, mask_warped);

            all_param->compensator->apply(img_idx, corners[img_idx], img_warped, mask_warped);
            img_warped.convertTo(img_warped_s, CV_16SC3);
            img_warped.release();
            img.release();
            mask.release();


            dilate(masks_warped[img_idx], dilated_mask, Mat());
            resize(dilated_mask, seam_mask, mask_warped.size(), 0, 0);
            mask_warped = seam_mask & mask_warped;

            if (!blender)
            {
                // 朋友使这个贼快，留着括号上面那个blender->prepare(corners, sizes)，剩下的都注释咯
//                blender = Blender::createDefault(Blender::NO, false);
                blender = Blender::createDefault(Blender::MULTI_BAND, false);
                Size dst_sz = resultRoi(corners, sizes).size();
                float blend_width = sqrt(static_cast<float>(dst_sz.area())) * all_param->blend_strength / 100.f;
                if (blend_width < 1.f){
                    blender = Blender::createDefault(Blender::NO, false);
                }
                else
                {
                    MultiBandBlender* mb = dynamic_cast<MultiBandBlender*>(blender.get());
                    mb->setNumBands(static_cast<int>(ceil(log(blend_width) / log(2.)) - 1.));
                }
                blender->prepare(corners, sizes);
            }
            //        string output_path = "/home/baihao/Stitch/try_new/resultaaaaa"+to_string(img_idx) +".jpeg";
            //        imwrite(output_path, img_warped_s);
            //        output_path = "/home/baihao/Stitch/try_new/resultbbbbb"+to_string(img_idx) +".jpeg";
            //        imwrite(output_path, mask_warped);
            blender->feed(img_warped_s, mask_warped, corners[img_idx]);
        }
        /* ===========================================================================*/
        // Blend image
        std::cout << "\nBlending ...\n";
        Mat result, result_mask;
        blender->blend(result, result_mask);
//        imwrite("/home/baihao/Stitch/try_new/resultabc.jpg", result);
        //    imwrite("/home/baihao/Stitch/try_new/result_mask.jpg", result_mask);
//        imwrite("/AI/panoimg/result/resultabc.jpg", result);
        all_param->result_stitched_img = result;
        all_param->result_stitched_img_mask = result;
        all_param->status = 0;

        // 清内存
        result.release();
        result_mask.release();
        img.release();
        blender.release();
        img_warped.release();
        img_warped_s.release();
        dilated_mask.release();
        seam_mask.release();
        mask.release();
        warper.release();
        mask_warped.release();
        corners.clear();
        masks_warped.clear();
        sizes.clear();
        focals.clear();
//        all_param.
    } catch (Exception e1) {
        all_param->status = 1;
    }
    return 0;

}
store_each enmty_struct(store_each all_param){
    all_param.result_stitched_img.release();
    all_param.full_imgs.clear();
    all_param.resized_imgs.clear();
    all_param.full_img_sizes.clear();
    all_param.adjuster.release();
    all_param.result_stitched_img.release();
    all_param.cameras.clear();
    all_param.compensator.release();
    all_param.features.clear();
    all_param.refine_mask.release();
    all_param.focals.clear();
    all_param.estimator.release();
    all_param.features.clear();
    all_param.result_stitched_img_mask.release();
    all_param.seam_finder.release();
    all_param.warper_creator.release();

}

store_each roll_back(store_each all_param) {
    all_param.cameras.pop_back();
    all_param.focals.pop_back();
    all_param.pairwise_matches.pop_back();
    all_param.features.pop_back();
    all_param.resized_imgs.pop_back();
    all_param.full_imgs.pop_back();
    all_param.full_img_sizes.pop_back();
    return all_param;
}

store_each return_param(store_each all_param) {


}