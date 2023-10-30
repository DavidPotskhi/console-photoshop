#include "command_line_parser.h"
#include "app_exceptions.h"

bool Command_line_parser::Parse(int argc, char* argv[]) {
    if (argc < MIN_ARG_NUM) {
        throw App_exceptions(App_exceptions::ErrorsCode::BadCommandLineParams, "Too few arguments in command line, should be at least 3");
    }
    input_file_name_ = argv[INPUT_FILE_INDEX];
    output_file_name_ = argv[OUTPUT_FILE_INDEX];
    size_t cnt_of_filters = 0;
    for (int i = MIN_ARG_NUM; i < argc; ++i) {
        if (argv[i][FILTER_ID_IND] == FILTER_ID) {
            std::string s = argv[i];
            filters_.push_back({s});
            ++cnt_of_filters;
            continue;
        } else if (cnt_of_filters == 0) {
            throw App_exceptions(App_exceptions::ErrorsCode::BadCommandLineParams, "No filters were detected in your command line, pay attention that all filter names begin with -");
        }
        filters_[cnt_of_filters - 1].params_.emplace_back(argv[i]);
    }
    return true;
}
