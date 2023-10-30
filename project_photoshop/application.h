#ifndef PROJECT_PHOTOSHOP_APPLICATION_H
#define PROJECT_PHOTOSHOP_APPLICATION_H
#include "command_line_parser.h"
#include "filter_pipeline_maker.h"
#include "bitmap.h"
#include <stdexcept>
class Application {
public:
    Application() : cmp_(), fpm_(), bmp_(){}
    void Configure();
    void Run(int argc, char* argv[]);

private:
    void MakeParse(int argc, char* argv[]);
    void MakeFiltersPipeline();
    void MakeBmpLoad();
    void ApplyFilters();
    void MakeBmpExport();
protected:
    Command_line_parser cmp_;
    Filter_pipeline_maker fpm_;
    Bitmap bmp_;
};


#endif //PROJECT_PHOTOSHOP_APPLICATION_H
