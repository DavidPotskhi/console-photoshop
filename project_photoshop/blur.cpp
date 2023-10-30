#include "blur.h"
#include <cmath>
#include <numeric>

bool Blur::Apply(Bitmap& bmp) {
    int64_t height = bmp.pixel_array_.size();
    int64_t width = bmp.pixel_array_[0].size();
    std::vector<std::vector<Color>> p_array_copy(height, std::vector<Color>(width));
    int convol_size = 3 * sigma_ + 1;
    AddFrame(p_array_copy, height, width, convol_size);
    std::vector<double> convol(convol_size);
    CalcGaussConvol(convol, convol_size);
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            p_array_copy[y][x] += bmp.pixel_array_[y][x] * convol[0];
            for (int64_t i = 1; i < convol_size; ++i) {
                p_array_copy[y][x] += bmp.pixel_array_[y][abs(x - i)] * convol[i] + bmp.pixel_array_[y][x + i] * convol[i];
            }
        }
    }
    for (int64_t y = 0; y < height; ++y) {
        for (int64_t x = 0; x < width; ++x) {
            bmp.pixel_array_[y][x] = p_array_copy[y][x] * convol[0];
            for (int64_t i = 1; i < convol_size; ++i) {
                bmp.pixel_array_[y][x] += p_array_copy[abs(y - i)][x] * convol[i] + p_array_copy[y + i][x] * convol[i];
            }
            bmp.pixel_array_[y][x] *= std::sqrt(1 / (2 * std::accumulate(convol.begin(), convol.end(), 0.0) - convol[0]));
        }
    }
    return true;
}

void Blur::AddFrame(std::vector<std::vector<Color>>& pixel_array, int64_t height, int64_t width, size_t convol_size) {
    for (size_t i = 0; i < convol_size; ++i) {
        pixel_array.emplace_back(pixel_array[height - 2 - i]);
    }
    for (auto& row : pixel_array) {
        for (size_t i = 0; i < convol_size; ++i) {
            row.emplace_back(row[width - 2 - i]);
        }
    }
}

void Blur::CalcGaussConvol(std::vector<double>& convol, int convol_size) {
    for (int64_t i = 0; i < convol_size; ++i) {
        convol[i] = (1 / std::sqrt(2 * std::numbers::pi * sigma_ * sigma_)) * pow(std::numbers::e, ((-1) * i * i) / (2 * sigma_ * sigma_));
    }
}