#ifndef DISPARITY_ESTIMATION_H_
#define DISPARITY_ESTIMATION_H_

#include "include/arl/image_core.h"

namespace arl
{
void estimateDisparity(const ImageC1<int> &image_left,
                       const ImageC1<int> &image_right,
                       ImageC1<int> &estimated_disparity,
                       const int search_length,
                       const int half_win_size);

void estimateDisparityFast(const ImageC1<int> &image_left,
                           const ImageC1<int> &image_right,
                           ImageC1<int> &estimated_disparity,
                           const int search_length,
                           const int half_win_size,
                           const int search_stride,
                           const int window_stride);

} // namespace arl

#endif
