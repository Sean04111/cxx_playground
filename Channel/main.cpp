//
// Created by Sean on 3/23/25.
//

#include <iostream>

#include "channel.hpp"
#include <thread>

int main() {
    auto chaan = new Channel<int>(5);

    std::thread t1 ([&] () -> void {
        std::cout << "thread 1 start ..." << std::endl;
        try {
            int msg = 10;
            std::this_thread::sleep_for(std::chrono::seconds(3));
            chaan->send(msg);
        }catch (Channel_Exception exception) {
            std::cout << exception.what() << std::endl;
        }

        std::cout << "thread 1 end ..." << std::endl;
    });

    std::thread t2 ([&] () -> void {
        std::cout << "thread 2 start ..." << std::endl;
        int msg;
        chaan->receive(msg);
        std::cout << msg << std::endl;
    });

    t1.join();
    t2.join();
    return 0;
}
