//
// Created by Sean on 3/15/25.
// auto pointer
#pragma once
#ifndef SIMPLESHAREDPTR_H
#define SIMPLESHAREDPTR_H

struct ControlBlock {
    int ref_count;
    ControlBlock():ref_count(1){};
};

template <typename T>
class SimpleSharedPtr {
private:
    T *ptr;
    ControlBlock *cb;

    void release();
public:
    SimpleSharedPtr();
    explicit SimpleSharedPtr(T *ptr);
    explicit SimpleSharedPtr(T&& value);
    ~SimpleSharedPtr();

    // copy constructor
    SimpleSharedPtr(const SimpleSharedPtr& other);
    // copy operator
    SimpleSharedPtr& operator=(SimpleSharedPtr& other);
    // move constructor
    SimpleSharedPtr(SimpleSharedPtr&& other) noexcept ;
    // move operator
    SimpleSharedPtr& operator=(SimpleSharedPtr&& other) noexcept;

    T& operator*();
    T* operator->();

    // return ref_count
    int use_count() const;
    // get the raw pointer
    T* get() const;
    // reset the pointer to new obj or nullptr
    void reset(T *ptr = nullptr);
};

template<typename T>
SimpleSharedPtr<T>::SimpleSharedPtr() : ptr(nullptr), cb(nullptr){}

template<typename T>
SimpleSharedPtr<T>::SimpleSharedPtr(T *ptr) : ptr(ptr) {
    if (ptr) {
        cb = new ControlBlock();
    }else {
        cb = nullptr;
    }
}

template<typename T>
SimpleSharedPtr<T>::SimpleSharedPtr(T &&value) {
    ptr = new T(value);
    cb = new ControlBlock();
}


template<typename T>
SimpleSharedPtr<T>::~SimpleSharedPtr() {
    release();
}

template<typename T>
void SimpleSharedPtr<T>::release() {
    if (cb) {
        cb->ref_count --;
        if (cb->ref_count == 0) {
            delete ptr;
            delete cb;
        }
    }
    ptr = nullptr;
    cb = nullptr;
}

template<typename T>
SimpleSharedPtr<T>::SimpleSharedPtr(const SimpleSharedPtr &other) : ptr(other.ptr) , cb(other.cb){
    if (cb) {
        cb->ref_count ++;
    }
}

template<typename T>
SimpleSharedPtr<T>& SimpleSharedPtr<T>::operator=(SimpleSharedPtr &other){
    if (this != &other) {
        release();
        ptr = other.ptr;
        cb = other.cb;
        if (cb) {
            cb->ref_count ++;
        }
    }
    return *this;
}

template <typename T>
SimpleSharedPtr<T>::SimpleSharedPtr(SimpleSharedPtr&& other) noexcept : ptr(other.ptr), cb(other.cb) {
    other.ptr = nullptr;
    other.cb = nullptr;
}

template<typename T>
SimpleSharedPtr<T> &SimpleSharedPtr<T>::operator=(SimpleSharedPtr &&other) noexcept {
    if (this != &other) {
        release();
        ptr = other.ptr;
        cb = other.cb;

        other.ptr = nullptr;
        other.cb = nullptr;
    }


    return *this;
}

template<typename T>
T &SimpleSharedPtr<T>::operator*() {
    return *ptr;
}

template<typename T>
T *SimpleSharedPtr<T>::operator->() {
    return ptr;
}

template<typename T>
int SimpleSharedPtr<T>::use_count() const {
    return cb->ref_count;
}

template<typename T>
T *SimpleSharedPtr<T>::get() const {
    return ptr;
}

template<typename T>
void SimpleSharedPtr<T>::reset(T *ptr) {
    this->ptr = ptr;
}




#endif //SIMPLESHAREDPTR_H
