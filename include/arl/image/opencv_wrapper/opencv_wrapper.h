#ifndef OPENCV_WRAPPER_H
#define OPENCV_WRAPPER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <utility>

#include "arl/image/image.h"
#include "arl/utilities/color_map.h"

namespace arl
{
std::pair<std::string, std::string> getCvMatType(const cv::Mat& m);
void applyColorMapToGrayscaleImage(const cv::Mat& input_image,
                                   cv::Mat& output_image,
                                   const RGBColorMap<unsigned char>& color_map);

template <typename T>
void aplImageToOpencvImage(const arl::ImageC1<T>& apl_image, cv::Mat& cv_image)
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
void opencvImageToArlImage(const cv::Mat& cv_image, arl::ImageC1<T>& arl_image)
{
    ASSERT(cv_image.channels() == 1) << "Number of channels of cv image is larger than 1!";
    if (!arl_image.isAllocated() || arl_image.rows() != static_cast<size_t>(cv_image.rows) ||
        arl_image.cols() != static_cast<size_t>(cv_image.cols))
    {
        arl_image.reallocate(cv_image.rows, cv_image.cols);
    }

    for (int r = 0; r < cv_image.rows; r++)
    {
        for (int c = 0; c < cv_image.cols; c++)
        {
            arl_image(r, c) = cv_image.at<T>(r, c);
        }
    }
}

}  // namespace arl

#endif
