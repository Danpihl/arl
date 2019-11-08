#ifndef _UTILITIES_COLORS_H_
#define _UTILITIES_COLORS_H_

#define COLOR_IDX_MAX 1280

namespace arl
{
namespace colors_internal
{
const int color_idx_max = 1280;
extern int color_red[color_idx_max];
extern int color_green[color_idx_max];
extern int color_blue[color_idx_max];
} // namespace colors_internal

void rainbowColor(float d, int &r, int &g, int &b);
void rainbowColor(int idx, int &r, int &g, int &b);

} // namespace arl

#endif