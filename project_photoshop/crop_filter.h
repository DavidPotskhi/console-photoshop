#ifndef PROJECT_PHOTOSHOP_CROP_FILTER_H
#define PROJECT_PHOTOSHOP_CROP_FILTER_H

#include "bitmap.h"
#include "base_filter.h"

class Crop_filter : public Base_filter {
public:

    Crop_filter(int new_width_, int new_height_) : new_width(new_width_), new_height(new_height_) {

    }
    bool Apply(Bitmap& bmp) override;
    virtual ~Crop_filter() = default;
protected:
    int new_width;
    int new_height;

};

#endif //PROJECT_PHOTOSHOP_CROP_FILTER_H
