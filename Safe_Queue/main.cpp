//
// Created by Sean on 3/27/25.
//

#include "threadsafe_queue.hpp"
#include <iostream>

int main() {
    threadsafe_queue<int> q{};
    q.push(1);
    auto p =  q.wait_and_pop();
    std::cout << *p << std::endl;

    return 0;
}
