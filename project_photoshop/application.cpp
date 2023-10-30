#include "application.h"


void Application::Configure() {
    fpm_.AddFilterCreator("-blur", FilterMakers::MakeBlurFilter);
    fpm_.AddFilterCreator("-edge", FilterMakers::MakeEdgeDetectorFilter);
    fpm_.AddFilterCreator("-crop", FilterMakers::MakeCropFilter);
    fpm_.AddFilterCreator("-gs", FilterMakers::MakeGrayscaleFilter);
    fpm_.AddFilterCreator("-neg", FilterMakers::MakeNegativeFilter);
    fpm_.AddFilterCreator("-sharp", FilterMakers::MakeSharpeningFilter);
}

void Application::Run(int argc, char* argv[]) {
    MakeParse(argc, argv);
    MakeFiltersPipeline();
    MakeBmpLoad();
    ApplyFilters();
    MakeBmpExport();
}

void Application::MakeParse(int argc, char* argv[]) {
    cmp_.Parse(argc, argv);
}

void Application::MakeFiltersPipeline() {
    fpm_.MakePipelineOfFilters(cmp_.filters_);
}

void Application::MakeBmpLoad() {
    bmp_.Load(cmp_.GetInput());
}

void Application::ApplyFilters() {
    for (auto filter : fpm_.GetPipelineOfFilters()) {
        filter->Apply(bmp_);
    }
    fpm_.DeleteFiltersPipeline();
}

void Application::MakeBmpExport() {
    bmp_.Export(cmp_.GetOutput());
}
