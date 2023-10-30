#ifndef PROJECT_PHOTOSHOP_BITMAP_H
#define PROJECT_PHOTOSHOP_BITMAP_H
#include <vector>
#include <cstdlib>
#include <cstdint>
#include <fstream>
#include <iostream>

struct Color {
    double r_;
    double g_;
    double b_;

    Color();


    Color(double r, double g, double b);

    Color operator*(int x);
    Color operator+(const Color& other);
    Color& operator=(const Color& other);
    static Color ColorMax(const Color& color ,const double x);
    static Color ColorMin(const double x, const Color& color);
    Color operator*(double x);
    Color& operator+=(const Color&);
    Color& operator*=(double x);
};


class Bitmap {
public:
    const size_t fileHeaderSize = 14;
    const size_t informationHeaderSize = 40;

public:
    struct BMPHeader {
        uint16_t signature;
        uint32_t bmp_size;
        uint16_t dummy_1;
        uint16_t dummy_2;
        uint32_t offset;
    } __attribute__((packed));


    struct DIBHeader {
        uint32_t header_size;
        int32_t width;
        int32_t height;
        uint16_t color_plane_num;
        uint16_t bpp;
        uint32_t compr_method;
        uint32_t img_size;
        int32_t hor_res;
        int32_t vert_res;
        uint32_t color_num;
        uint32_t imp_color_num;
    } __attribute__((packed));

public:
    void Load(const std::string path);
    void Export(const std::string path);
    static bool CheckBMPHeader (const BMPHeader& header);
    void InversePixelArray();
public:
    BMPHeader bmpHeader_;
    DIBHeader dibHeader_;
    std::vector<std::vector<Color>> pixel_array_;
};


#endif //PROJECT_PHOTOSHOP_BITMAP_H
