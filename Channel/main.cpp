//
// Created by Sean on 3/23/25.
//

#include <iostream>

#include "channel.hpp"
#include <thread>

void func(const int& a) {

}

int main() {
    auto chaan = new Channel<int>(5);

    std::thread t1 ([&] () -> void {
        try {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            for (int i = 1; i<= 100; ++i) {
                int msg = i;
                chaan -> send(msg);
            }
        }catch (Channel_Exception exception) {
            std::cout << exception.what() << std::endl;
        }

    });

    std::thread t2 ([&] () -> void {
        int msg;
        chaan->receive(msg);
        std::cout << msg << std::endl;
    });

    std::thread t_close([&] () -> void {
        std::this_thread::sleep_for(std::chrono::seconds(4));
        try {
            chaan->close();
        }catch (Channel_Exception exception) {
            std::cout << exception.what() << std::endl;
        }
    });


    t2.join();
    t_close.join();
    func(1);
    const int abc = 100;
    const int& b = 100;
    return 0;
}
