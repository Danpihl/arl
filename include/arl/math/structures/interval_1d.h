#ifndef INTERVAL_1D_H_
#define INTERVAL_1D_H_

namespace arl
{
template <typename T> struct Interval1D
{
    T from;
    T to;

    Interval1D() = default;
    Interval1D(const T from_, const T to_) : from(from_), to(to_) {}
};
}  // namespace arl

#endif
