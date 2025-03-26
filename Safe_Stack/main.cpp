//
// Created by Sean on 3/26/25.
//
#include <iostream>
#include <ostream>

#include "threadsafe_stack.hpp"

int main() {
    threadsafe_stack<int> s2{};
    s2.push(1);

    int* p = new int;
    s2.pop(*p);
    std::cout << *p << std::endl;

    return 0;
}