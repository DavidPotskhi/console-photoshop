#ifndef PROJECT_PHOTOSHOP_FILTER_PIPELINE_MAKER_H
#define PROJECT_PHOTOSHOP_FILTER_PIPELINE_MAKER_H
#include "command_line_parser.h"
#include "base_filter.h"
#include "crop_filter.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "edge_detection.h"
#include "blur.h"
#include <string>
#include <unordered_map>

namespace FilterMakers {
    Base_filter* MakeBlurFilter(const FilterDescriptor& fd);
    Base_filter* MakeCropFilter(const FilterDescriptor& fd);
    Base_filter* MakeGrayscaleFilter(const FilterDescriptor& fd);
    Base_filter* MakeNegativeFilter(const FilterDescriptor& fd);
    Base_filter* MakeSharpeningFilter(const FilterDescriptor& fd);
    Base_filter* MakeEdgeDetectorFilter(const FilterDescriptor& fd);
    // add more filters
}

class Filter_pipeline_maker {


public:
    typedef Base_filter*(*FilterMakePtr)(const FilterDescriptor&);
    typedef std::unordered_map<std::string, FilterMakePtr> FilterCreators;

public:
    void AddFilterCreator(std::string filter_name, FilterMakePtr filter_maker) {
        filter_creator_.insert({filter_name, filter_maker});
    }

    void MakePipelineOfFilters(std::vector<FilterDescriptor>&);
    std::vector<Base_filter*> GetPipelineOfFilters() {
        return filters_pipeline_;
    }

    Base_filter* MakeFilter(const FilterDescriptor& fd) const;

    FilterMakePtr GetFilterMaker(std::string name) const;
    void DeleteFiltersPipeline();
protected:
    FilterCreators filter_creator_/*{{"-crop", FilterMakers::MakeCropFilter}, {"-gs", FilterMakers::MakeGrayscaleFilter},
                                   {"-neg", FilterMakers::MakeNegativeFilter}, {"-sharp", FilterMakers::MakeSharpeningFilter},
                                   {"-edge", FilterMakers::MakeEdgeDetectorFilter}, {"-blur", FilterMakers::MakeBlurFilter}}*/;

     std::vector<Base_filter*> filters_pipeline_;

};




#endif //PROJECT_PHOTOSHOP_FILTER_PIPELINE_MAKER_H
