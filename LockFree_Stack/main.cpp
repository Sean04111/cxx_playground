//
// Created by Sean on 4/1/25.
//

#include <iostream>
#include <thread>
#include "lock_free_stack_with_delete_list.hpp"

int main() {
    lock_free_stack_with_delete_list<int> s{};

    std::thread t1 ([&]() -> void {
        s.push(1);
        std::shared_ptr<int> value = s.pop();
        std::cout << *value << std::endl;
    });
    t1.join();
    return 0;
}