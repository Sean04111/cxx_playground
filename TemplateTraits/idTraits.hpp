//
// Created by Sean on 3/16/25.
//

/*
 * a code template for cxx template traits situation
 * take hasId() as example
 */
#pragma once
#ifndef IDTRAITS_HPP
#define IDTRAITS_HPP
#include <iostream>
#include <ostream>
#include <string>
#include <type_traits>

/* only allow types with function hasId() fit in the template */


/* using type extraction */
template <typename T>
class idTraits {
private:
    using has_id = int[1];
    using has_not_id = int[2];

    template <typename U, std::string (U::*)()>
    struct fit_checker{};

    template <typename U>
    static has_id& fit(fit_checker<U,&U::hasId>*);

    template <typename U>
    static has_not_id& fit(...);

public:
    static constexpr bool ok = sizeof(fit<T>(nullptr)) == sizeof(has_id);
};


// template function with traits
template <typename T>
typename std::enable_if<idTraits<T>::ok, void>::type call_has_id(T& obj) {
    std::cout << "id is "<< obj.hasId() << std::endl;
}

//template class with traits
template <typename T>
class Data_with_id {
    T* data;
public:
    template <typename U = T ,typename std::enable_if<idTraits<U>::ok,int>::type = 0>
    Data_with_id(){};

    std::string get_id() {
        return data->hasId();
    };
};

class Class_With_Id  {
private:
    std::string id;
public:
    std::string hasId() {
        return id;
    }
};

class Class_Without_Id {};




#endif //IDTRAITS_HPP
