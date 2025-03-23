//
// Created by Sean on 3/22/25.
// ref: https://www.yuque.com/lianlianfengchen-cvvh2/sekvap/tmen67dlbcdzv5yb

#ifndef THREADPOOL_HPP
#define THREADPOOL_HPP

#include <atomic>
#include <condition_variable>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
private:
    std::atomic_int _thread_num;
    std::vector<std::thread> _threads;
    std::mutex _mu;
    std::queue<std::packaged_task<void()>> _tasks;
    std::condition_variable _cv_lock;
    std::atomic_bool _stop;
private:
    ThreadPool(unsigned int num = 5) : _stop(false) {
        if (num < 1) {
            _thread_num = 1;
        }else {
            _thread_num = num;
        }
        start();
    }
    /*
     * start() is trying to create threads while there is
     * enough cap for the pool and new task commited
     */
    void start() {
        for (int i = 0; i < _thread_num; ++i) {
            _threads.emplace_back([this] ()-> void {
                while (!this->_stop.load()) {
                    std::packaged_task<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(_mu);
                        _cv_lock.wait(lock, [this]() -> bool{
                            return this->_stop.load() || !this->_tasks.empty();
                        });
                        if (this->_tasks.empty()){
                            return;
                        }
                        task = std::move(this->_tasks.front());
                        this->_tasks.pop();
                    }
                    --this->_thread_num;
                    task();
                    ++this->_thread_num;
                }

            });
        }
    }

    /*
     * stop()
     */
    void stop() {
        _stop.store(true);
        _cv_lock.notify_all();

        for (auto& thread: _threads) {
            if (thread.joinable()) {
                std::cout << "finishing working threads : " << thread.get_id() << std::endl;
                thread.join();
            }
        }

    }

public:
    ThreadPool(ThreadPool const & other) = delete;
    ThreadPool& operator=(ThreadPool const & other) = delete;

    static ThreadPool& get_instance() {
        static ThreadPool ins;
        return ins;
    }

    ~ThreadPool() {
        stop();
    }


    template <typename F, typename ... Args>
    auto commit (F&& f, Args&&... args) -> std::future<decltype(f(args...))> {
        using RetType = decltype(f(args...));

        if (_stop.load()) {
            return std::future<RetType>{};
        }

        auto task = std::make_shared<std::packaged_task<RetType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<RetType> ret = task->get_future();
        {
            std::lock_guard<std::mutex> lock (_mu);
            _tasks.emplace([task] {
                (*task)();
            });
        }
        _cv_lock.notify_one();
        return ret;
    }

    int get_idle_count() {
        return this->_thread_num;
    }
};

#endif //THREADPOOL_HPP
