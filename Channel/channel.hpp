//
// Created by Sean on 3/23/25.
//

#pragma once
#ifndef CHANNEL_HPP
#define CHANNEL_HPP
/*
 * CSP design style in CXX
 */
#include <mutex>
#include <string>
#include <condition_variable>
#include <queue>

/* channel exception */
class Channel_Exception : public std::exception {
private:
    std::string _message;
public:
    explicit Channel_Exception(const std::string& message) : _message(message) {}

    const char *what() const noexcept override {
        return _message.c_str();
    };
};

/* exception types */
using Exception_Types  = std::string;
Exception_Types SEND_CLOSED_CHAN = "Send to a closed channel";
Exception_Types CLOSE_CLOSED_CHAN = "Close a closed channel";

/* Channel declaration */
#define DEFAULT_CHANNEL_CAP  10;

template <typename T>
class Channel {
private:
    std::atomic_size_t _cap;
    std::mutex _mu;
    std::queue<T> _queue;


    std::condition_variable _recv_cond;
    std::condition_variable _send_cond;

    std::atomic_bool _closed;

    void _hand_off(Channel&& other) {
        this-> _cap = other._cap;
        this->_mu = std::move(other._mu);
        this->_queue = std::move(other._queue);

        this->_recv_cond = std::move(other._recv_cond);
        this->_send_cond = std::move(other._send_cond);

        this-> _closed.store(other._closed.load());

        other._queue = nullptr;
    }

public:
    Channel(const Channel& other) = delete;
    Channel& operator= (const Channel& other) = delete;

    Channel() {
        _closed.store(false);
        _cap.store(10);
    };

    Channel(std::size_t cap) {
        _closed.store(false);
        if (cap > 0) {
            _cap.store(cap);
        }
    };

    Channel(Channel&& other) noexcept {
        _hand_off(other);
    };

    Channel& operator=(Channel&& other) noexcept {
        if (*this != other) {
           _hand_off(other);
        }
        return *this;
    };

    void send(const T& msg) {
        /* check if closed */
        if (_closed.load()) {
            throw Channel_Exception(SEND_CLOSED_CHAN);
        }
        {
            std::unique_lock<std::mutex> lock (_mu);
            /* awake when:
             *  1. message & queue not full
             *  2. closed
             */
            _send_cond.wait(lock, [this]()-> bool {
                return (_cap.load() == 0 && _queue.empty() )||( _queue.size() < _cap.load() )|| _closed.load();
            });

            if (_closed.load()) {
                throw Channel_Exception(SEND_CLOSED_CHAN);
            }

            /* L or R value ? */
            _queue.push(msg);
            _recv_cond.notify_one();
        }
    };

    void receive(T& msg) {
        /* check if closed */
        if (_closed.load()) {
            throw nullptr;
        }
        {
            std::unique_lock<std::mutex> lock (_mu);
            _recv_cond.wait(lock, [this]() -> bool {
               return !_queue.empty() || _closed.load();
            });

            if (_closed.load()) {
                throw nullptr;
            }

            msg = _queue.front();
            _queue.pop();
            _send_cond.notify_one();
        }
    };
    void close() {

    };
    ~Channel() {

    };
};

#endif //CHANNEL_HPP
