#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "panorama_check.h"

using namespace cv;
using namespace std;

//vector<String> img_names = {"/home/nolan/Images/1.jpg", "/home/nolan/Images/2.jpg", "/home/nolan/Images/3.jpg",
//                            "/home/nolan/Images/4.jpg", "/home/nolan/Images/5.jpg"};

//vector<String> img_names = {"/home/baihao/Stitch/try_new/1.jpeg", "/home/baihao/Stitch/try_new/2.jpeg", "/home/baihao/Stitch/try_new/3.jpeg"};
vector<String> img_names = {"/AI/panoimg/1111111/1.jpg", "/AI/panoimg/1111111/2.jpg"};
//vector<String> img_names = {"/home/nolan/Images/c1.jpg", "/home/nolan/Images/c2.jpg", "/home/nolan/Images/c3.jpg",
//                            "/home/nolan/Images/c4.jpg"};


int main()
{
    int num_images = static_cast<int>(img_names.size());



    Mat pre_frame = imread(img_names[0]);
    if (pre_frame.empty()){
        return -2;
    }

    vector<string> image_names_temp;
    store_each *all_param = new store_each();

    all_param->full_imgs.push_back(pre_frame);
    generate_result(*all_param, 0);

    all_param->full_imgs.push_back(pre_frame);
    generate_result(*all_param, 2);
    reset_it(*all_param);
    all_param->full_imgs.push_back(pre_frame);
    generate_result(*all_param, 0);
    for (int i = 1; i < num_images; ++i)
    {
//        store_each temop_all_param = *all_param;
        store_each temop_all_param(*all_param);

        Mat pre_frame = imread(img_names[i]);
        all_param->full_imgs.push_back(pre_frame);


//        boost::thread api_caller(::generate_result(all_param, i) );
//
//        if(api_caller.timed_join(boost::posix_time::milliseconds(500))){
        int a = generate_result(*all_param, i);
        if(a == 1){
            return 1;
        }
//        }else{
//
//        }
//
    }
//    cout<<"aaaaaaaaaaa";
//    all_param->result_stitched_img.convertTo(all_param->result_stitched_img,CV_8U);
//    cv::cvtColor(all_param->result_stitched_img, all_param->result_stitched_img, CV_BGRA2BGR);
    imwrite("/AI/panoimg/result/6.jpg", all_param->result_stitched_img);
    cout<<all_param->result_stitched_img.cols;

    roll_back(*all_param);
    cout<<all_param->full_imgs.size();
//    free_it(all_param);
//    delete all_param;
//    all_param->full_imgs.push_back(pre_frame);
//    generate_result(*all_param, 0);
    return 0;
}
