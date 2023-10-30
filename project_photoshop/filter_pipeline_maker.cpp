#include "filter_pipeline_maker.h"
#include "app_exceptions.h"
#include <stdexcept>





namespace FilterMakers {
    Base_filter* MakeCropFilter (const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-crop") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeCropFilter");
        }
        int new_width = 0;
        int new_height = 0;
        if (fd.params_.empty()) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Crop gets 2 positive integers as params, you provided zero");
        }
        try {
            new_width = std::stoi(fd.params_[0]);
            new_height = std::stoi(fd.params_[1]);
        } catch (const std::invalid_argument& argument) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Not correct params for filter Crop, should be two positive integers");
        } catch (const std::out_of_range& ofRange) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Too big integers, should be less");
        } catch (...) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Incorrect filter params for Crop");
        }
        return new Crop_filter(new_width, new_height);
    }

    Base_filter* MakeGrayscaleFilter (const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-gs") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeGrayscaleFilter");
        }
        return new Grayscale();
    }


    Base_filter* MakeNegativeFilter (const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-neg") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeNegativeFilter");
        }
        return new Negative();
    }

    Base_filter* MakeSharpeningFilter(const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-sharp") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeSharpeningFilter");
        }
        return new Sharpening();
    }

    Base_filter* MakeEdgeDetectorFilter(const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-edge") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeEdgeDetectorFilter");
        }
        int threshold = 0;
        try {
            threshold = std::stoi(fd.params_[0]);
        } catch (const std::invalid_argument& argument) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Not correct param for filter Edge Detector, should be one positive integer");
        } catch (const std::out_of_range& ofRange) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Too big integer, should be less");
        }
        return new EdgeDetection(threshold);
    }

    Base_filter* MakeBlurFilter(const FilterDescriptor& fd) {
        if (fd.filter_name_ != "-blur") {
            throw std::invalid_argument("invalid filter descriptor passed to MakeBlurFilter");
        }
        double sigma = 0;
        try {
            sigma = std::stod(fd.params_[0]);
        } catch (const std::invalid_argument& argument) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Not correct param for filter Blur, should be one positive float");
        } catch (const std::out_of_range& ofRange) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadFilterParam, "Too big float, should be less");
        }
        return new Blur(sigma);
    }


}












Base_filter* Filter_pipeline_maker::MakeFilter(const FilterDescriptor &fd) const {
    FilterMakePtr maker = GetFilterMaker(fd.filter_name_);
    if (!maker) {
        std::string message;
        message = "No such a filter called: " + fd.filter_name_;
        throw App_exceptions(App_exceptions::ErrorsCode::BadFilterName, message);
    }
    return maker(fd);
}

Filter_pipeline_maker::FilterMakePtr Filter_pipeline_maker::GetFilterMaker(std::string name) const {
    auto ix = filter_creator_.find(name);
    if (ix == filter_creator_.end()) {
        return nullptr;
    }
    return ix->second;
}

void Filter_pipeline_maker::MakePipelineOfFilters(std::vector<FilterDescriptor>& filters) {
    filters_pipeline_.reserve(filters.size());
    for (auto& filter : filters) {
        filters_pipeline_.emplace_back(MakeFilter(filter));
    }
}

void Filter_pipeline_maker::DeleteFiltersPipeline() {
    for (auto ptr : filters_pipeline_) {
        delete ptr;
    }
}
