#ifndef PROJECT_PHOTOSHOP_GRAYSCALE_H
#define PROJECT_PHOTOSHOP_GRAYSCALE_H
#include "bitmap.h"
#include "base_filter.h"

class Grayscale : public Base_filter {
public:
    bool Apply(Bitmap& bmp) override;
    virtual ~Grayscale() = default;
};


#endif //PROJECT_PHOTOSHOP_GRAYSCALE_H
