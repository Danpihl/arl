#ifndef LOOKUP_GRID_H_
#define LOOKUP_GRID_H_

#include <vector>

#include "arl/utilities/logging.h"

namespace arl
{

template <typename T> class BaseCell
{
private:
public:
    T x0;
    T y0;
    T x1;
    T y1;

    BaseCell() = default;
    BaseCell(const T x0_, const T y0_, const T x1_, const T y1_) : x0(x0_), y0(y0_), x1(x1_), y1(y1_) {}

};

class Cell0 : public BaseCell<double>
{
private:
    std::vector<int> vec;
public:

    Cell0() = default;
    Cell0(const double x0_, const double y0_, const double x1_, const double y1_) : BaseCell(x0_, y0_, x1_, y1_) {}

};

template <typename T, class CellType> class LookupGrid
{
private:
    CellType *cells_;

    size_t num_cells_x_;
    size_t num_cells_y_;
    size_t num_cells_;

    T x0_;
    T y0_;

    T inc_x_;
    T inc_y_;

    void setupCells(const std::vector<T>& borders_x, const std::vector<T>& borders_y);

public:

    T getNumCellsX() const
    {
        return num_cells_x_;
    }

    T getNumCellsY() const
    {
        return num_cells_y_;
    }

    CellType operator()(const T x, const T y) const;

    LookupGrid() {}
    LookupGrid(const T x0, const T x1, const T y0, const T y1, const T inc_x, const T inc_y);

    ~LookupGrid()
    {
        delete[] cells_;
    }
};

template <typename T, class CellType> LookupGrid<T, CellType>::LookupGrid(const T x0,
                                                                          const T x1,
                                                                          const T y0,
                                                                          const T y1,
                                                                          const T inc_x,
                                                                          const T inc_y) : x0_(x0), y0_(y0), inc_x_(inc_x), inc_y_(inc_y)
{
    assert(x1 > x0);
    assert(y1 > y0);
    const T interval_length_x = x1 - x0;
    const T interval_length_y = y1 - y0;

    constexpr bool is_correct_class = std::is_base_of<BaseCell<T>, CellType>::value;
    static_assert(is_correct_class, "Cell class should be derived from class \"BaseCell\"!");

    num_cells_x_ = std::ceil(interval_length_x/inc_x);
    num_cells_y_ = std::ceil(interval_length_y/inc_y);

    const size_t num_borders_x = num_cells_x_ + 1;
    const size_t num_borders_y = num_cells_y_ + 1;

    std::vector<T> borders_x(num_borders_x);
    std::vector<T> borders_y(num_borders_y);

    num_cells_ = num_cells_x_*num_cells_y_;
    cells_ = new CellType[num_cells_];

    T x = x0;
    size_t i_x = 0;
    while (x < x1)
    {
        borders_x[i_x] = x;
        x = x + inc_x;
        i_x++;

    }
    borders_x[i_x] = x;

    T y = y0;
    size_t i_y = 0;
    while (y < y1)
    {
        borders_y[i_y] = y;
        y = y + inc_y;
        i_y++;

    }
    borders_y[i_y] = y;

    setupCells(borders_x, borders_y);

}

template <typename T, class CellType>
void LookupGrid<T, CellType>::setupCells(const std::vector<T>& borders_x, const std::vector<T>& borders_y)
{
    for(size_t x = 0; x < num_cells_x_; x++)
    {
        for(size_t y = 0; y < num_cells_y_; y++)
        {
            const size_t cell_idx = y*num_cells_x_ + x;
            cells_[cell_idx].x0 = borders_x[x];
            cells_[cell_idx].x1 = borders_x[x + 1];

            cells_[cell_idx].y0 = borders_y[y];
            cells_[cell_idx].y1 = borders_y[y + 1];
        }
    }
}

template <typename T, class CellType> CellType LookupGrid<T, CellType>::operator()(const T x, const T y) const
{
    const size_t fx = std::floor((x - x0_)/inc_x_);
    const size_t fy = std::floor((y - y0_)/inc_y_);

    const size_t idx_x = std::min(fx, num_cells_x_ - 1);
    const size_t idx_y = std::min(fy, num_cells_y_ - 1);

    return cells_[idx_y*num_cells_x_ + idx_x];
}

}

#endif
