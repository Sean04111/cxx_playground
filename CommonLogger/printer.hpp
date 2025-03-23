//
// Created by Sean on 3/23/25.
//

#ifndef PRINTER_HPP
#define PRINTER_HPP
#include <iostream>

template <typename T>
class Printer {
public:
    void print(const T& obj) {
        std::cout << "General printer says " << obj << std::endl;
    }
};


template <>
class Printer<std::string> {
public:
    void print(std::string obj) {
        std::cout << "String printer says " << obj << std::endl;
    }
};

template <typename T, typename U>
class MyClass {
public:
    T first;
    U second;
    MyClass(T a, U b): first(a), second(b) {};
    void print() {
        std::cout << first << " , " << second << "as common !" <<std::endl;
    }
};

template <typename T, typename U>
class MyClass<T, U*> {
public:
    T first;
    U* second;

    MyClass(T a, U* b): first(a), second(b) {};
    void print() {
        std::cout << first << " , " << *second << "as ptr type !"<< std::endl;
    }
};


template <typename T>
inline void print_value(const T& obj) {
    std::cout << obj << " as general value" << std::endl;
}

template <>
inline void print_value<std::string>(const std::string& obj){
    std::cout << obj << " as string value" << std::endl;
}

template <>
inline void print_value <int*>(int* const& obj) {
    std::cout << *obj << " as integer pointer value" << std::endl;
}

inline void print_all() {
    std::cout << std::endl;
}

template <typename T, typename...Args>
inline void print_all(const T& first, const Args&... args) {
    std::cout << first << " ";
    print_all(args...);
}

// substitution failure is not an error


#endif //PRINTER_HPP
