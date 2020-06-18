#include "EventLoop.h"

#include "mylib/base/Mutex.h"
#include "mylib/base/Logging.h"

#include <algorithm>

#include <signal.h>
#include <sys/eventfd.h>
#include <unistd.h>

using namespace mylib;


__thread EventLoop* t_loopInThisThread = 0;

//const int kPollTimeMs = 10000;

int createEventfd()
{
    int evtfd = ::eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
    if(evtfd < 0)
    {
        LOG_SYSERR << "Failed in eventfd";
        abort();
    }

    return evtfd;
}

EventLoop* EventLoop::getEventLoopOfCurrentThread()
{
    return t_loopInThisThread;
}

EventLoop::EventLoop():
    looping_(false),
    //quit(false),
    threadId_(CurrentThread::tid())
{
    LOG_DEBUG << "EventLoop created " << this << " int thread " << threadId_;
    if(t_loopInThisThread != 0)
    {
        LOG_FATAL << "Another EventLoop " << t_loopInThisThread
                  << "has exited in this thread " << threadId_;
    }
    else
    {
        t_loopInThisThread = this;
    }
}


EventLoop::~EventLoop()
{
    LOG_DEBUG << "EventLoop " << this << " of thread " << threadId_
                << " destructs in thread " << CurrentThread::tid();

    assert(!looping_);
    t_loopInThisThread = NULL;
}


