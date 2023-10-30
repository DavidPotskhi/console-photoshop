#ifndef PROJECT_PHOTOSHOP_EDGE_DETECTION_H
#define PROJECT_PHOTOSHOP_EDGE_DETECTION_H
#include "base_filter.h"
#include "bitmap.h"

class EdgeDetection : public Base_filter {
public:
    EdgeDetection(int threshold) : threshold_(threshold) {}
    bool Apply(Bitmap& bmp) override;
    static void AddFrame(std::vector<std::vector<Color>>&, int64_t, int64_t);
    virtual ~EdgeDetection() = default;
protected:
    int threshold_;
};


#endif //PROJECT_PHOTOSHOP_EDGE_DETECTION_H
