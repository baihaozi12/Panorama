#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "panorama_check.h"

using namespace cv;
using namespace std;


//vector<String> img_names = {"/home/nolan/Images/1.jpg", "/home/nolan/Images/2.jpg", "/home/nolan/Images/3.jpg",
//                            "/home/nolan/Images/4.jpg", "/home/nolan/Images/5.jpg"};

vector<String> img_names = {"/home/baihao/Stitch/try_new/1.jpeg", "/home/baihao/Stitch/try_new/2.jpeg", "/home/baihao/Stitch/try_new/3.jpeg"};

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
    store_each all_param;

    all_param.full_imgs.push_back(pre_frame);
    all_param = generate_result(all_param, 0);
    for (int i = 1; i < num_images; ++i)
    {
        Mat pre_frame = imread(img_names[i]);
        all_param.full_imgs.push_back(pre_frame);

//        boost::thread api_caller(::generate_result(all_param, i) );
//
//        if(api_caller.timed_join(boost::posix_time::milliseconds(500))){
        all_param = generate_result(all_param, i);
//        }else{
//
//        }
//
    }

    return 1;
}
