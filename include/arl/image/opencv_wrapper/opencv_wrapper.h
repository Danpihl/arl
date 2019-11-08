#ifndef OPENCV_WRAPPER_H
#define OPENCV_WRAPPER_H

#include "arl/image_core.h"
#include <arl/colors.h>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

namespace arl
{
std::string getCvMatType(const cv::Mat &m);

template <typename T>
void aplImageToOpencvImage(const arl::ImageC1<T> &apl_image, cv::Mat &cv_image)
{
    if (apl_image.rows() != static_cast<size_t>(cv_image.rows) ||
        apl_image.cols() != static_cast<size_t>(cv_image.cols))
    {
        cv_image = cv::Mat(apl_image.rows(), apl_image.cols(), CV_8UC1);
    }

    for (size_t r = 0; r < apl_image.rows(); r++)
    {
        for (size_t c = 0; c < apl_image.cols(); c++)
        {
            cv_image.at<T>(r, c) = apl_image(r, c);
        }
    }
}

template <typename T>
void opencvImageToAtwImage(const cv::Mat &cv_image, arl::ImageC1<T> &apl_image)
{
    ASSERT(cv_image.channels() == 1) << "Number of channels of cv image is larger than 1!";
    if (!apl_image.isAllocated() || apl_image.rows() != static_cast<size_t>(cv_image.rows) ||
        apl_image.cols() != static_cast<size_t>(cv_image.cols))
    {
        apl_image.reallocate(cv_image.rows, cv_image.cols);
    }

    for (int r = 0; r < cv_image.rows; r++)
    {
        for (int c = 0; c < cv_image.cols; c++)
        {
            apl_image(r, c) = cv_image.at<T>(r, c);
        }
    }
}

template <typename T>
void aplImageToRainBowCvImage(const T factor, const arl::ImageC1<T> &apl_image, cv::Mat &cv_image)
{
    if (apl_image.rows() != static_cast<size_t>(cv_image.rows) ||
        apl_image.cols() != static_cast<size_t>(cv_image.cols))
    {
        cv_image = cv::Mat(apl_image.rows(), apl_image.cols(), CV_8UC3);
    }

    int red, green, blue;

    for (int r = 0; r < cv_image.rows; r++)
    {
        for (int c = 0; c < cv_image.cols; c++)
        {
            if (apl_image(r, c) == 0)
            {
                red = 127;
                green = 127;
                blue = 127;
            }
            else
            {
                rainbow_color(apl_image(r, c) * factor, &red, &green, &blue);
            }

            cv_image.at<cv::Vec3b>(r, c) = cv::Vec3b(blue, green, red);
        }
    }
}

} // namespace arl

#endif
