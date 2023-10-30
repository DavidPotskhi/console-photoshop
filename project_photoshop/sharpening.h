//
// Created by talle on 3/20/2022.
//

#ifndef PROJECT_PHOTOSHOP_SHARPENING_H
#define PROJECT_PHOTOSHOP_SHARPENING_H
#include "bitmap.h"
#include "base_filter.h"
class Sharpening : public Base_filter {
public:
    bool Apply(Bitmap& bmp) override;
    static void AddFrame(std::vector<std::vector<Color>>&, int64_t, int64_t);
};


#endif //PROJECT_PHOTOSHOP_SHARPENING_H
