//
// Created by Sean on 3/23/25.
//

#ifndef SFINAE_HPP
#define SFINAE_HPP

#include <iostream>
#include <type_traits>

// before cxx20
template <typename T>
typename std::enable_if<std::is_integral<T>::value,void>::type take(T value) {
    std::cout << "Integral value " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value,void>::type take(T value) {
    std::cout << "Floating point value " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<const char*,T>::value ||
                        std::is_same<char* , T>::value,
                        void>::type take(T value) {
    std::cout << "C style string value " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_same<std::string, T>::value,void>::type take(T value) {
    std::cout << "std::string value " << value << std::endl;
}

template <typename T>
typename std::enable_if<std::is_pointer<T>::value &&
                        !std::is_same<char*,T>::value &&
                            !std::is_same<const char*,T>::value,
                        void>::type take(T value) {
    std::cout << "Pointer value " << *value << std::endl;
}

// after cxx20
template <typename T>
concept Integral = std::is_integral_v<T>;


template <typename T>
concept FloatingPoint = std::is_floating_point_v<T>;

template <typename T>
concept CString = std::is_same_v<T, const char*> || std::is_same_v<T, char*>;

template <typename T>
concept StdString = std::is_same_v<T,std::string>;

template <typename T>
concept Pointer = std::is_pointer_v<T> && !std::is_same_v<T, const char*> && !std::is_same_v<T, char*>;

void put(Integral auto value) {
    std::cout << "Integral value " << value << std::endl;
}

template <typename T>
requires (!Integral<T> &&!Pointer<T>)
void put(T value) {
    std::cout << "T value " << value << std::endl;
}



// type contraction
template <typename T>
class has_foo {
private:
    typedef char yes[1];
    typedef char no[2];

    template <typename U, void(U::*)()>
    struct SFINAE {};

    template <typename U>
    static yes& test(SFINAE<U, &U::foo>*);

    template <typename U>
    static no& test(...);
public:
    static constexpr bool value = sizeof(test<T>(0)) == sizeof(yes);
};

template <typename T>
typename std::enable_if<has_foo<T>::value, void>::type invoke_foo(T& value) {
    std::cout << "Foo value invocation" << std::endl;
    value->foo();
}





#endif //SFINAE_HPP
