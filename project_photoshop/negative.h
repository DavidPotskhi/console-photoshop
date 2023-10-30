#ifndef PROJECT_PHOTOSHOP_NEGATIVE_H
#define PROJECT_PHOTOSHOP_NEGATIVE_H
#include "base_filter.h"
#include "bitmap.h"

class Negative : public Base_filter {
public:
    bool Apply(Bitmap& bmp) override;
    virtual ~Negative() = default;
};


#endif //PROJECT_PHOTOSHOP_NEGATIVE_H
