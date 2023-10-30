#include "crop_filter.h"
#include "app_exceptions.h"

bool Crop_filter::Apply(Bitmap &bmp) {
    if (new_width >= bmp.dibHeader_.width && new_height >= bmp.dibHeader_.height) {
        return true;
    }
    if (new_width >= bmp.dibHeader_.width || new_height >= bmp.dibHeader_.height) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam,
                             "out of image size, check correctness of crop params");
    }
    bmp.pixel_array_.resize(new_height);
    for (auto &row: bmp.pixel_array_) {
        row.resize(new_width);
    }
    bmp.bmpHeader_.bmp_size -= ((bmp.dibHeader_.height - new_height) * bmp.dibHeader_.width +
                                new_height * (bmp.dibHeader_.width - new_width));
    bmp.dibHeader_.img_size -= ((bmp.dibHeader_.height - new_height) * bmp.dibHeader_.width +
                                new_height * (bmp.dibHeader_.width - new_width));
    bmp.dibHeader_.width = new_width;
    bmp.dibHeader_.height = new_height;
    return true;
}
