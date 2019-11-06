#include <cmath>
#include <iostream>
#include <string>
#include <vector>

#include "arl/image/image.h"

int main()
{

    arl::ImageC1<size_t> i0(100, 100);

    i0(0, 3) = 3;
    return 0;
}
