//
// Created by Sean on 3/26/25.
//

#ifndef THREADSAFE_STACK_HPP
#define THREADSAFE_STACK_HPP

#include <memory>
#include <exception>
#include <mutex>
#include <stack>


struct empty_stack : std::exception {
    const char* what () const throw(){};
};

template <typename T>
class threadsafe_stack {
private:
    std::stack<T> _data;
    mutable  std::mutex _mu;
public:
    threadsafe_stack(){};
    threadsafe_stack(const threadsafe_stack& other) {
        std::lock_guard<std::mutex> lock(other._mu);
        _data = other._data;
    };
    threadsafe_stack& operator=(const threadsafe_stack&) = delete;
    void push(T new_value) {
        std::lock_guard<std::mutex> lock(_mu);
        _data.push(std::move(new_value));
    };
    std::shared_ptr<T> pop() {
        std::lock_guard<std::mutex> lock(_mu);
        if (_data.empty()) throw empty_stack();
        std::shared_ptr<T> const res(std::make_shared<T>(_data.top()));
        _data.pop();
        return res;
    };
    void pop(T& value) {
        std::lock_guard<std::mutex> lock(_mu);
        if (_data.empty()) throw empty_stack();
        value = _data.top();
        _data.pop();
    };
    bool empty() const {
        std::lock_guard<std::mutex> lock(_mu);
        return _data.empty();
    };

    size_t size() const {
        std::lock_guard<std::mutex> lock(_mu);
        return _data.size();
    }
};

#endif //THREADSAFE_STACK_HPP
