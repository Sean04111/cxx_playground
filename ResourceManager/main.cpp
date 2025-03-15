//
// Created by Sean on 3/15/25.
//

#include <iostream>

#include "ResourceManager.hpp"

int main() {
    {
        auto rm =  ResourceManager(10);
        std::cout << rm.getValue() << std::endl;
        rm.setValue(20);
        std::cout << rm.getValue() << std::endl;

        ResourceManager rm2;
        rm2 = std::move(rm);

        std::cout << rm2.getValue() << std::endl;
    }

    return 0;
}