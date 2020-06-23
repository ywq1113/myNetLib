#pragma once
#include "event_loop.h"
#include "locker.h"

//boost库
#include <boost/thread/thread.hpp>
#include <boost//noncopyable.hpp>
#include <boost/utility.hpp>

/*
 * 处理eventloop的线程
 * 
 */

class EventLoopThread
{
public:
    EventLoopThread();
    ~EventLoopThread();

    event_loop* startLoop();

private:
    void threadFunc();
    event_loop* loop_;
    bool exiting_;
    boost::thread thread_;
    locker mutex_;
    locker cond_;
};