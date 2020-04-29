#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "panorama_check.h"

using namespace cv;
using namespace std;


vector<String> img_names = {"/home/baihao/jpg/1111111/1.jpg", "/home/baihao/jpg/1111111/2.jpg", "/home/baihao/jpg/1111111/3.jpg", "/home/baihao/jpg/1111111/4.jpg", "/home/baihao/jpg/1111111/5.jpg", "/home/baihao/jpg/1111111/6.jpg"};
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

        all_param = generate_result(all_param, i);
    }

    return 1;
}
