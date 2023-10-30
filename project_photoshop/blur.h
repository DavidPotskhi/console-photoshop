#ifndef PROJECT_PHOTOSHOP_BLUR_H
#define PROJECT_PHOTOSHOP_BLUR_H
#include "bitmap.h"
#include "base_filter.h"

class Blur : public Base_filter {
public:
    Blur(double sigma) : sigma_(sigma){}
    bool Apply(Bitmap& bmp) override;
    static void AddFrame(std::vector<std::vector<Color>>&, int64_t, int64_t, size_t);
    void CalcGaussConvol(std::vector<double>&, int );
    virtual ~Blur() = default;
protected:
    double sigma_;
};


#endif //PROJECT_PHOTOSHOP_BLUR_H
