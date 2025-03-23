#include <iostream>
#include "sfinae.hpp"

class foo_able {
public:
    void foo() {
        std::cout << "has foo" << std::endl;
    }
};

class foo_unable {

};

int main() {
    take(1);
    take(1.2);
    const char* Cstr = "Hello World!";
    take(Cstr);
    take(std::string("you /"));

    int a = 100;
    int* p = &a;
    take(p);


    put(123);
    put("123");

}
