//
// Created by Sean on 3/15/25.
//

#include <iostream>
#include <type_traits>
#include "ResourceManager.hpp"

template <typename T>
class has_foo {
private:
    using yes = char[1];
    using no  = char[2];

    template <typename U, void (U::*foo)()>
    struct SFINAE{};

    template <typename U>
    static yes& test(SFINAE<U, &U::foo>*);

    template <typename U>
    static no& test(...);

public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T>
std::enable_if<has_foo<T>::value,void>::type call_foo(T& obj) {
    obj.foo();
    std::cout << "foo() called" << std::endl;
}

class WithFoo {
    public:
    void foo() {
        std::cout << "WithFoo::foo()" << std::endl;
    }
};

class WithoutFoo {};



int main() {
    WithFoo foo;
    call_foo<WithFoo>(foo);
    return 0;
}