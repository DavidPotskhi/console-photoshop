#ifndef PROJECT_PHOTOSHOP_BASE_FILTER_H
#define PROJECT_PHOTOSHOP_BASE_FILTER_H
#include "bitmap.h"
#include <string>
#include <cmath>
#include <numeric>

class Base_filter {
public:
    virtual bool Apply(Bitmap&) = 0;
    virtual ~Base_filter() = default;
};

#endif //PROJECT_PHOTOSHOP_BASE_FILTER_H
