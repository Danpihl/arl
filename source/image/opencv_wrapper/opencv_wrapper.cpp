#include "arl/image/opencv_wrapper/opencv_wrapper.h"

std::string getCvMatType(const cv::Mat &m)
{
    int type = m.type();
    std::string r;

    unsigned char depth = type & CV_MAT_DEPTH_MASK;
    unsigned char num_channels = 1 + (type >> CV_CN_SHIFT);

    switch (depth)
    {
    case CV_8U:
        r = "8U";
        break;
    case CV_8S:
        r = "8S";
        break;
    case CV_16U:
        r = "16U";
        break;
    case CV_16S:
        r = "16S";
        break;
    case CV_32S:
        r = "32S";
        break;
    case CV_32F:
        r = "32F";
        break;
    case CV_64F:
        r = "64F";
        break;
    default:
        r = "User";
        break;
    }

    r += "C";
    r += (num_channels + '0');

    return r;
}
