#include "eventloop_threadpool.h"

//开辟numOfThreads_个eventloop线程，并在线程处启动事件循环
void eventloop_threadpool::start()
{
    //baseLoop_->assertInLoopThread();
    started_ = true;
    for(int i = 0; i < numOfThreads_; ++i)
    {
        std::shared_ptr<EventLoopThread> tmp(new EventLoopThread());
        threads_.push_back(tmp);
        loop_.push_back(tmp->startLoop());
    }
}

event_loop* eventloop_threadpool::getNextLoop()
{
    //baseLoop_->assertInLoopThread();
    assert(started_);
    event_loop *loop = baseLoop_;
    if(!loops_.empty())
    {
        loop = loops_[next_];
        next_ = (1 + next_) % numOfThreads_;
    }
    return loop;
}