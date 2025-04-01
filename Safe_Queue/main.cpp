#include <atomic>
#include <thread>
#include <iostream>


class spin_lock {
private:
    std::atomic_flag flag;
public:
    spin_lock(): flag(ATOMIC_FLAG_INIT) {};

    void lock() {
        while (flag.test_and_set(std::memory_order_acquire));
    }

    void unlock() {
        flag.clear(std::memory_order_release);
    }
};

int main() {
    std::atomic<spin_lock*> lock{};
    std::cout << lock.is_lock_free() << std::endl;
    return 0;
}

