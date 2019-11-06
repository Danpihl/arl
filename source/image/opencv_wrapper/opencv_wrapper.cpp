#include "arl/image/opencv_wrapper/opencv_wrapper.h"

#include "arl/utilities/color_map.h"
#include "arl/utilities/logging.h"

namespace arl
{
void applyColorMapToGrayscaleImage(const cv::Mat& input_image,
                                   cv::Mat& output_image,
                                   const RGBColorMap<unsigned char>& color_map)
{
    ASSERT((input_image.rows > 0) && (input_image.cols > 0)) << "Input image is empty!";

    const auto input_type = getCvMatType(input_image);
    ASSERT(input_type.second == "C1") << "Incorrect number of channels!";
    ASSERT(input_type.first == "8U") << "Incorrect bit depth!";

    output_image.create(input_image.rows, input_image.cols, CV_8UC3);

    const int max_val = 255;

    for (int r = 0; r < input_image.rows; r++)
    {
        for (int c = 0; c < input_image.cols; c++)
        {
            const arl::RGBTriplet<unsigned char> col =
                color_map(input_image.at<unsigned char>(r, c), max_val);
            output_image.at<cv::Vec3b>(r, c) = cv::Vec3b(col.blue, col.green, col.red);
        }
    }
}

std::pair<std::string, std::string> getCvMatType(const cv::Mat& m)
{
    const int type = m.type();
    std::string bit_depth;

    unsigned char depth = type & CV_MAT_DEPTH_MASK;
    unsigned char num_channels = 1 + (type >> CV_CN_SHIFT);

    switch (depth)
    {
        case CV_8U:
            bit_depth = "8U";
            break;
        case CV_8S:
            bit_depth = "8S";
            break;
        case CV_16U:
            bit_depth = "16U";
            break;
        case CV_16S:
            bit_depth = "16S";
            break;
        case CV_32S:
            bit_depth = "32S";
            break;
        case CV_32F:
            bit_depth = "32F";
            break;
        case CV_64F:
            bit_depth = "64F";
            break;
        default:
            bit_depth = "User";
            break;
    }

    const std::string num_channels_str = "C" + std::to_string(num_channels);

    return {bit_depth, num_channels_str};
}

}  // namespace arl
