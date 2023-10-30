#include "edge_detection.h"

void EdgeDetection::AddFrame(std::vector<std::vector<Color>>& pixel_array, int64_t height, int64_t width) {
    pixel_array.emplace_back(pixel_array[height - 2]);
    for (auto& row : pixel_array) {
        row.emplace_back(row[width - 2]);
    }
}


bool EdgeDetection::Apply(Bitmap &bmp) {
    for (std::vector<Color>& pixel_row : bmp.pixel_array_) {
        for (Color& color : pixel_row) {
            color.r_ = color.b_ = color.g_ = color.r_ * 0.299 + color.g_ * 0.587 + color.b_ * 0.114;
        }
    }
    int64_t height = static_cast<int64_t>(bmp.pixel_array_.size());
    int64_t width = static_cast<int64_t>(bmp.pixel_array_[0].size());
    std::vector<std::vector<Color>> p_array_copy = bmp.pixel_array_;
    AddFrame(p_array_copy, height, width);
    for (long y = 0; y < height; ++y) {
        for (long x = 0; x < width; ++x) {
            bmp.pixel_array_[y][x] =
                    Color::ColorMin(255, Color::ColorMax( // Create name for 255
                            p_array_copy[y + 1][x] * (-1) +
                            p_array_copy[y][abs(x - 1)] * (-1)   + p_array_copy[y][x] * 4  + p_array_copy[y][x + 1] * (-1)   +
                            p_array_copy[abs(y - 1)][x] * (-1)
                            , 0));
        }
    }
    for (long y = 0; y < height; ++y) {
        for (long x = 0; x < width; ++x) {
            if (bmp.pixel_array_[y][x].g_ > threshold_) {
                bmp.pixel_array_[y][x].g_ = 255;
                bmp.pixel_array_[y][x].r_ = 255;
                bmp.pixel_array_[y][x].b_ = 255;
            } else {
                bmp.pixel_array_[y][x].g_ = 0;
                bmp.pixel_array_[y][x].r_ = 0;
                bmp.pixel_array_[y][x].b_ = 0;
            }
        }
    }
    return true;
}