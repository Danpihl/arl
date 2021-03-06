#ifndef END_INDEX_H_
#define END_INDEX_H_

#include <cassert>

namespace arl
{
struct EndIndex
{
    const int offset;

    EndIndex() : offset(0) {}
    EndIndex(const int offset_) : offset(offset_)
    {
        assert(offset_ <= 0 && "Offset must be either 0 or negative!");
    }
};

inline EndIndex operator-(const EndIndex& end_idx, const int offset)
{
    return EndIndex(end_idx.offset - offset);
}

#define End EndIndex()
}  // namespace arl

#endif
