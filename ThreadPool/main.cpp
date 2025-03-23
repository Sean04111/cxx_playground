//
// Created by Sean on 3/22/25.
//

#include "threadpool.hpp"



auto add(int a, int b) -> int {
    return a + b;
}


class A {
public:
};

int main() {

    ThreadPool& pool = ThreadPool::get_instance();

    auto ret =  pool.commit(add,1,2);
    auto ans = pool.commit([](int i)->int {
        return i * i;
    },10);

    std::future<std::string> result = std::async(std::launch::deferred, [](std::string former)->std::string {
        return former+"_subfix";
    },"prefix");

    std::cout <<"result is "<< result.get() << std::endl;

    std::cout << "ret is " << ret.get() << std::endl;
    std::cout << "ans is " << ans.get() << std::endl;

    std::cout << *"123" << std::endl;

    auto a = new A();
    pool.commit(a,1,2,3);


    return 0;
}
