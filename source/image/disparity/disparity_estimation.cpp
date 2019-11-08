#include "arl/image/disparity/disparity_estimation.h"

#include <string>

#include <arl/utilities/logging.h>

namespace arl
{
int sumOfSquaredDifference(const ImageC1<int> &image_left,
                           const ImageC1<int> &image_right,
                           const int half_win_size,
                           const int row_left,
                           const int col_left,
                           const int row_right,
                           const int col_right)
{
    int s = 0;
    for (int r = -half_win_size; r <= half_win_size; r++)
    {
        for (int c = -half_win_size; c <= half_win_size; c++)
        {
            const int diff =
                image_left(r + row_left, c + col_left) - image_right(r + row_right, c + col_right);
            s = s + diff * diff;
        }
    }
    return s;
}

void estimateDisparity(const ImageC1<int> &image_left,
                       const ImageC1<int> &image_right,
                       ImageC1<int> &estimated_disparity,
                       const int search_length = 30,
                       const int half_win_size = 3)
{
    ASSERT(image_left.isAllocated()) << "Left image not initialized!";
    ASSERT(image_right.isAllocated()) << "Right image not initialized!";
    ASSERT(estimated_disparity.isAllocated()) << "Output image not initialized!";

    const int rows = static_cast<int>(image_left.rows());
    const int cols = static_cast<int>(image_left.cols());

    int ssd_val, min_val = 10000;
    int min_idx;

    for (int r = half_win_size; r < rows - half_win_size; r++)
    {
        for (int c = half_win_size; c < cols - half_win_size - search_length; c++)
        {
            min_val = 10000;
            min_idx = 0;

            for (int i = 0; i < search_length; i++)
            {
                ssd_val =
                    sumOfSquaredDifference(image_left, image_right, half_win_size, r, c + i, r, c);
                if (ssd_val < min_val)
                {
                    min_val = ssd_val;
                    min_idx = i;
                }
            }
            estimated_disparity(r, c) = min_idx;
        }
    }
}

void estimateDisparityFast(const ImageC1<int> &image_left,
                           const ImageC1<int> &image_right,
                           ImageC1<int> &estimated_disparity,
                           const int search_length,
                           const int half_win_size,
                           const int search_stride,
                           const int window_stride)
{
    ASSERT(image_left.isAllocated()) << "Left image not initialized!";
    ASSERT(image_right.isAllocated()) << "Right image not initialized!";
    ASSERT(estimated_disparity.isAllocated()) << "Output image not initialized!";

    const int rows = static_cast<int>(image_left.rows());
    const int cols = static_cast<int>(image_left.cols());

    int *data_left = image_left.getDataPointer();
    int *data_right = image_right.getDataPointer();
    int *data_disp = estimated_disparity.getDataPointer();

    int min_idx, diff, ssd_val, min_val;

    for (int r = half_win_size + 1; r < rows - half_win_size - 1; r += search_stride)
    {
        for (int c = half_win_size + 1; c < cols - half_win_size - search_length - 1;
             c += search_stride)
        {
            min_val = 10000;
            min_idx = 0;

            for (int i = 0; i < search_length; i++)
            {
                ssd_val = 0;
                for (int r_i = -half_win_size; r_i <= half_win_size; r_i += window_stride)
                {
                    for (int c_i = -half_win_size; c_i <= half_win_size; c_i += window_stride)
                    {
                        diff = data_left[(r + r_i) * cols + c + c_i + i] -
                               data_right[(r + r_i) * cols + c + c_i];

                        ssd_val += diff * diff;
                    }
                }

                if (ssd_val < min_val)
                {
                    min_val = ssd_val;
                    min_idx = i;
                }
            }
            data_disp[r * cols + c] = min_idx;
        }
    }
}

} // namespace arl