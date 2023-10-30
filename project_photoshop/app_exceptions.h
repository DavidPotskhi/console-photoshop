#ifndef PROJECT_PHOTOSHOP_APP_EXCEPTIONS_H
#define PROJECT_PHOTOSHOP_APP_EXCEPTIONS_H
#include "application.h"

class App_exceptions : public std::runtime_error {
public:
    enum class ErrorsCode {
        BadCommandLineParams,
        BadFilterName,
        BadFilterParam,
        BadInputFile,
        BadOutputFile
    };
    explicit App_exceptions(ErrorsCode code, const char *message) : runtime_error(message),
                                                                                         code_(code){}

    explicit App_exceptions(ErrorsCode code, const std::string  message) : runtime_error(message), code_(code) {}
protected:
    ErrorsCode code_;
};


#endif //PROJECT_PHOTOSHOP_APP_EXCEPTIONS_H
