//
// Created by Sean on 3/15/25.
//


#include <utility>
#include <iostream>
#include "SimpleUniquePtr.hxx"


int main() {
    auto p = new SimpleUniquePtr<int>(5);
    auto p2 = std::move(*p);
    return 0;
}
