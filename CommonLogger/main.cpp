//
// Created by Sean on 3/23/25.
//

#include "printer.hpp"
#include <string>
#include "logger.hpp"


int main() {
    int a = 1;
    int *p = &a;
    Logger<int*>::log(p);

    log(std::string("test"),1,a,p);
    return 0;
}


