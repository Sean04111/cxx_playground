//
// Created by Sean on 3/23/25.
//

#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <iostream>
#include <string>
#include <type_traits>

// common class
template <typename T, typename Enable = void>
class Logger {
public:
    static void log(const T& value) {
        std::cout << "General logger : "<< value << std::endl;
    }
};

// T as ptr
template <typename T>
class Logger<T, typename std::enable_if<std::is_pointer<T>::value,void>::type> {
public:
    static void log(const  T& value) {
        if (value) {
            std::cout << "Pointer logger : " << *value << std::endl;
        }else {
            std::cout << "Pointer logger : nullptr" << std::endl;
        }
    }
};

// T as std::string
template <>
class Logger<std::string> {
public:
    static void log(const std::string& value) {
        std::cout << "String logger : " << value << std::endl;
    }
};


template <typename T>
void log(const T& value) {
    Logger<T>::log(value);
}

template <typename T, typename... Args>
void log(const T& value,  const Args&... args) {
    Logger<T>::log(value);
    log(args...);
}


#endif //LOGGER_HPP
