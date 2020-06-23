#include "eventloop_thread.h"
#include <functional>

EventLoopThread::EventLoopThread() :
    loop_(NULL), 
    exiting_(false), 
    thread_(boost::bind(&EventLoopThread::threadFunc, this))
{
}

EventLoopThread::~EventLoopThread()
{
    exiting_ = true;
    if(loop_ != NULL)
    {
        //loop_.quit();
        thread_.join();
    }
}

event_loop* EventLoopThread::startLoop()
{
    mutex_.lock();
    while(loop_ == NULL)
    {
        cond_.wait();
    }
    mutex_.unlock();
    return loop_;
}

void EventLoopThread::threadFunc()
{
    event_loop loop;
    mutex_.lock();
    loop_ = &loop;
    cond_.signal();
    mutex_.unlock();

    //loop.loop();
    loop_ = NULL;
}