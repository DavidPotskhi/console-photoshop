#include <iostream>
#include "application.h"
#include "app_exceptions.h"
int main(int argc, char* argv[]) {
    try {
        Application apl;
        apl.Configure();
        apl.Run(argc, argv);
    } catch(const App_exceptions& exp) {
        std::cout << exp.what() << std::endl;
    } catch(const std::exception& exp) {
        std::cout << exp.what() << std::endl;
    } catch (...) {
        std::cout << "something went wrong... sorry";
    }
    return 0;
}
