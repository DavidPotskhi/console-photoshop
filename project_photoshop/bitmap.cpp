#include "bitmap.h"
#include "app_exceptions.h"

Color::Color() : r_(0), g_(0), b_(0) {

}

Color::Color(double r, double g, double b) : r_(r), g_(g), b_(b) {

}

Color Color::operator*(int x) {
    Color res = *this;
    res.r_ *= x;
    res.b_ *= x;
    res.g_ *= x;
    return res;
}

Color Color::operator+(const Color& other) {
    Color res;
    res.r_ = r_ + other.r_;
    res.g_ = g_ + other.g_;
    res.b_ = b_ + other.b_;
    return res;
}

Color& Color::operator=(const Color &other) {
    r_ = other.r_;
    g_ = other.g_;
    b_ = other.b_;
    return *this;
}

Color Color::ColorMax(const Color& color, const double x) {
    Color res;
    res.r_ = std::max(x, color.r_);
    res.b_ = std::max(x, color.b_);
    res.g_ = std::max(x, color.g_);
    return res;
}

Color Color::ColorMin(const double x, const Color &color) {
    Color res;
    res.r_ = std::min(x, color.r_);
    res.b_ = std::min(x, color.b_);
    res.g_ = std::min(x, color.g_);
    return res;
}

Color Color::operator*(double x) {
    Color res = *this;
    res.g_ *= x;
    res.b_ *= x;
    res.r_ *= x;
    return res;
}

Color &Color::operator+=(const Color& other) {
    r_ += other.r_;
    g_ += other.g_;
    b_ += other.b_;
    return *this;
}

Color& Color::operator*=(double x) {
    r_ *= x;
    b_ *= x;
    g_ *= x;
    return *this;
}


void Bitmap::Load(const std::string path) {
    std::ifstream f(path, std::ios::in | std::ios::binary);
    if (!f.is_open()) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadInputFile, "something went wrong during reading a file, ensure that you input correct file");
    }
    f.read(reinterpret_cast<char *>(&bmpHeader_), fileHeaderSize);
    if (f.fail() == 1 || f.bad() == 1) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadInputFile, "something went wrong during reading a file, ensure that you input correct file");
    }
    if (!CheckBMPHeader(bmpHeader_)) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadInputFile, "wrong file format, read carefully instructions about input file format");
    }
    f.read(reinterpret_cast<char *>(&dibHeader_), informationHeaderSize);
    if (f.fail() == 1 || f.bad() == 1) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadInputFile, "something went wrong during reading a file, ensure that you input correct file");
    }
    pixel_array_.resize(dibHeader_.height, std::vector<Color>(dibHeader_.width));
    const size_t paddingAmount = ((4 - (dibHeader_.width * 3) % 4) % 4);
    for (size_t y = 0; y < dibHeader_.height; ++y) {
        for (size_t x = 0; x < dibHeader_.width; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char *>(color), 3);
            pixel_array_[y][x].r_ = color[2];
            pixel_array_[y][x].g_ = color[1];
            pixel_array_[y][x].b_ = color[0];
        }
        f.ignore(paddingAmount);
    }
    this->InversePixelArray();
    f.close();
}

bool Bitmap::CheckBMPHeader(const Bitmap::BMPHeader &header) {
    return (header.signature == 0x4d42);
}

void Bitmap::Export(const std::string path) {
    std::ofstream f(path, std::ios::out | std::ios::binary);
    if (!f.is_open()) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadOutputFile, "something went wrong during exporting a file");
    }
    f.write(reinterpret_cast<char *>(&bmpHeader_), fileHeaderSize);
    if (f.fail() == 1 || f.bad() == 1) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadOutputFile, "something went wrong during exporting a file");;
    }
    f.write(reinterpret_cast<char *>(&dibHeader_), informationHeaderSize);
    if (f.fail() == 1 || f.bad() == 1) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadOutputFile, "something went wrong during exporting a file");
    }
    this->InversePixelArray();
    unsigned char bmpPad[3] = {0,0,0};
    const size_t paddingAmount = ((4 - (dibHeader_.width * 3) % 4) % 4);
    for (size_t y = 0; y < dibHeader_.height; ++y) {
        for (size_t x = 0; x < dibHeader_.width; ++x) {
            unsigned char color[3] = {static_cast<unsigned char>(pixel_array_[y][x].b_),
                                      static_cast<unsigned char>(pixel_array_[y][x].g_),
                                      static_cast<unsigned char>(pixel_array_[y][x].r_)};
            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
        if (f.fail() == 1 || f.bad() == 1) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadOutputFile, "something went wrong during exporting a file");
        }
    }
    f.close();
}

void Bitmap::InversePixelArray() {
    for (size_t i = 0; i < (pixel_array_.size() / 2 + pixel_array_.size() % 2); ++i) {
        for (size_t d = 0; d < pixel_array_[0].size(); ++d) {
            std::swap(pixel_array_[i][d], pixel_array_[pixel_array_.size() - 1 - i][d]);
        }
    }
}
