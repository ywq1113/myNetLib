//EventLoop保证一个线程只有一个IO事件循环
//因此要判断是否是当前线程
//如果当前线程已经创建了其他EventLoop对象
//就会产生异常中止

#ifndef EVENTLOOP_H
#define EVENTLOOP_H

#include "mylib/base/CurrentThread.h"
#include <boost/thread/thread.hpp>
#include <boost//noncopyable.hpp>
#include <boost/utility.hpp>

class Channle;
class Poller;
class TimerQueue;

class EventLoop : boost::noncopyable
{
public:
    EventLoop();
    ~EventLoop();

    void loop();

    void assertInLoopThread()
    {
        if(!isInLoopThread())
        {
            abortNotInLoopThread();
        }
    }

    bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }

    //操作分发器Channel
    void wakeup();
    void updateChannel(Channel* channel);
    void removeChannel(Channel* channel);
    //bool hasChannel(Channel* channel);

private:
    void abortNotInLoopThread();

    bool looping_;
    const pid_t threadId_;
};
