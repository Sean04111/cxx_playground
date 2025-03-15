//
// Created by Sean on 3/15/25.
// infos:
// this is a safe pointer but not able shared it with others
// 1. only move ops are allowed
// 2. does it need ref count ? no
// 3. how to make it unique ?

#pragma once
#ifndef SIMPLEUNIQUEPTR_H
#define SIMPLEUNIQUEPTR_H

template <typename T> class SimpleUniquePtr {
private:
  T *ptr;

public:
  SimpleUniquePtr() : ptr(nullptr) {};
  explicit SimpleUniquePtr(T *p) : ptr(p) {};
  explicit SimpleUniquePtr(T &&value) : ptr(new T(value)) {};
  ~SimpleUniquePtr() {};

  SimpleUniquePtr(SimpleUniquePtr &&other) noexcept : ptr(other.ptr) {
    other.ptr = nullptr;
  };

  SimpleUniquePtr &operator=(SimpleUniquePtr &&other) noexcept {
    if (this != &other) {
      delete ptr;
      this->ptr = other.ptr;
      other.ptr = nullptr;
    }
    return *this;
  };
  // just forbid copy constructor
  SimpleUniquePtr(SimpleUniquePtr& other) = delete;
  SimpleUniquePtr &operator=(SimpleUniquePtr &other) = delete;

  T& operator*() {
    return *ptr;
  };

  T*operator->() {
    return ptr;
  };
};

#endif // SIMPLEUNIQUEPTR_H
