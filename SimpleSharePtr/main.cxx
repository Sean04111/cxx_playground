//
// Created by Sean on 3/15/25.
//
#include "SimpleSharedPtr.h"
#include <iostream>

int main(){
    auto share_ptr = new SimpleSharedPtr<int>(100);
    auto share_ptr2 = *share_ptr;
    std::cout << share_ptr->use_count() << std::endl;

    SimpleSharedPtr<int> share_ptr3 = std::move(*share_ptr);

    std::cout << share_ptr3.use_count() << std::endl;

    return 0;
}