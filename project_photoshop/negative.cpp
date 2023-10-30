#include "negative.h"




bool Negative::Apply(Bitmap& bmp) {
    for (std::vector<Color>& pixel_row : bmp.pixel_array_) {
        for (Color& color : pixel_row) {
            color.r_ = 255 - color.r_;
            color.g_ = 255 - color.g_;
            color.b_ = 255 - color.b_;
        }
    }
    return true;
}