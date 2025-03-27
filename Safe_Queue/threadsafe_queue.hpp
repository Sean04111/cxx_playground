//
// Created by Sean on 3/27/25.
//

#ifndef THREADSAFE_QUEUE_HPP
#define THREADSAFE_QUEUE_HPP

#include <queue>


template <typename T>
class threadsafe_queue {
private:
    std::mutex _mu;
    std::queue<T> _queue;
    std::condition_variable _pop_cond;
public:
    threadsafe_queue() {};

    threadsafe_queue(const threadsafe_queue& other) {
        std::lock_guard<std::mutex> lock(other._mu);
        _queue = other._queue;
    };

    void push(const T& value) {
        std::lock_guard<std::mutex> lock (_mu);
        _queue.push(value);
        _pop_cond.notify_one();
    }

    void wait_and_pop(T& value) {
        std::unique_lock<std::mutex> lock(_mu);
        _pop_cond.wait(lock, [&] () -> bool {
            return !_queue.empty();
        });
        value = _queue.front();
        _queue.pop();
    }

    std::shared_ptr<T> wait_and_pop() {
        std::unique_lock<std::mutex> lock(_mu);
        _pop_cond.wait(lock, [&] () -> bool {
            return !_queue.empty();
        });

        std::shared_ptr<T> res = std::make_shared<T>(_queue.front());
        _queue.pop();
        return res;
    }

    bool try_pop(T &value) {
        std::lock_guard<std::mutex> lock(_mu);
        if (_queue.empty()) {
            return false;
        }else {
            value = _queue.front();
            _queue.pop();
            return true;
        }
    }

    std::shared_ptr<T> try_pop() {
        std::lock_guard<std::mutex> lock(_mu);
        if (_queue.empty()) {
            return std::shared_ptr<T>();
        }else {
            std::shared_ptr<T> res = std::make_shared<T>(_queue.front());
            _queue.pop();
            return res;
        }
    }

    bool empty() const {
        std::lock_guard<std::mutex> lock(_mu);
        return _queue.empty();
    }
};

#endif //THREADSAFE_QUEUE_HPP
