//
// Created by Sean on 3/26/25.
//
#include <iostream>
#include <ostream>
#include <shared_mutex>
#include <thread>

#include "threadsafe_stack.hpp"

class C {
public:
    int x;
    std::once_flag x_init_flag;
    void init_x() {
        x = 100;
    }
    C(){
        show_x();
    };
    C(const C& __x) {
        x = __x.x;
    }

    void show_x() {
        std::call_once(x_init_flag, &C::init_x, this);
        std::cout << "x = " << x << std::endl;
    }
};

C& get_instance() {
    static C instance;
    return instance;
}

int main() {
    std::mutex m;
    std::condition_variable cond;





    return 0;
}