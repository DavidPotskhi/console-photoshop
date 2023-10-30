#include "grayscale.h"

bool Grayscale::Apply(Bitmap &bmp) {
    for (std::vector<Color>& pixel_row : bmp.pixel_array_) {
        for (Color& color : pixel_row) {
            color.r_ = color.b_ = color.g_ = color.r_ * 0.299 + color.g_ * 0.587 + color.b_ * 0.114;
        }
    }
    return true;
}