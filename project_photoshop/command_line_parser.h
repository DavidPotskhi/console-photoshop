#ifndef PROJECT_PHOTOSHOP_COMMAND_LINE_PARSER_H
#define PROJECT_PHOTOSHOP_COMMAND_LINE_PARSER_H
#include <cstdint>
#include <vector>
#include <string>

class FilterDescriptor {
public:
    std::string filter_name_;
    std::vector<std::string> params_;
};



class Command_line_parser {
public:
    static const int MIN_ARG_NUM = 3;
    static const int INPUT_FILE_INDEX = 1;
    static const int OUTPUT_FILE_INDEX = 2;
    static const char FILTER_ID = '-';
    static const int FILTER_ID_IND = 0;
public:

    bool Parse(int argc, char* argv[]);

    std::string GetInput() const {
        return input_file_name_;
    }
    std::string GetOutput() const {
        return output_file_name_;
    }
protected:
    std::string input_file_name_;
    std::string output_file_name_;
public:
    std::vector<FilterDescriptor> filters_;
};


#endif //PROJECT_PHOTOSHOP_COMMAND_LINE_PARSER_H
