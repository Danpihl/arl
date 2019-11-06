#include <unistd.h>

#include <cmath>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <string>
#include <vector>

#include "arl/image/opencv_wrapper/opencv_wrapper.h"
#include "arl/utilities/color_map.h"
#include "arl/utilities/logging.h"

int main()
{
    cv::Mat img = cv::imread("/home/danielpi/work/arl/apps/clean_application/img.png");

    const arl::RGBColorMap<unsigned char> cm = arl::color_maps::jet;

    cv::Mat img_gray;
    cv::cvtColor(img, img_gray, CV_BGR2GRAY);

    cv::Mat img_rainbow, img_magma, img_viridis, img_jet;

    arl::applyColorMapToGrayscaleImage(img_gray, img_rainbow, arl::color_maps::rainbow);
    arl::applyColorMapToGrayscaleImage(img_gray, img_magma, arl::color_maps::magma);
    arl::applyColorMapToGrayscaleImage(img_gray, img_viridis, arl::color_maps::viridis);
    arl::applyColorMapToGrayscaleImage(img_gray, img_jet, arl::color_maps::jet);

    cv::namedWindow("Window0");
    cv::namedWindow("Window1");
    cv::namedWindow("Window2");
    cv::namedWindow("Window3");

    cv::imshow("Window0", img_rainbow);
    cv::imshow("Window1", img_magma);
    cv::imshow("Window2", img_viridis);
    cv::imshow("Window3", img_jet);

    cv::waitKey(-1);

    return 0;
}
