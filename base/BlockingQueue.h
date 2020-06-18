#ifndef BLOCKINTQUEUE_H
#define BLOCKINGQUEUE_H

#include <mutex>
#include <condition_variable>
#include <functional>
#include <deque>
#include <assert.h>
#include <boost/noncopyable.hpp>
#include<boost/utility.hpp>

namespace mylib
{
template<typename T>
class BlockingQueue : boost::noncopyable
{
public:
    BlockingQueue() { };

    void put(const T& x) { 
        std::unique_lock<std::mutex> ulk(mutex_);
        queue_.push_back(x);
        cond_.notify_all();
    }

    void put(T&& x) {
        std::unique_lock<std::mutex> ulk(mutex_);
        queue_.push_back(std::move(x));
        cond_.notify_all();
    }

    T take() {
        std::unique_lock<std::mutex> ulk(mutex_);
        while(queue_.empty()) {
            cond_.wait(ulk);
        }
        assert(!queue_.empty());
        T front(std::move(queue_.front()));
        queue_.pop_front();
        return front;
    }

    size_t size() {
        std::unique_lock<std::mutex> ulk(mutex_);
        return queue_.size();
    }

private:
    mutable std::mutex          mutex_;
    std::condition_variable     cond_;
    std::deque<T>               queue_;
};

} //namespace mylib

#endif
