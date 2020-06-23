#pragma once
#include <memory>
#include <vector>
#include "event_loop.h"
#include "eventloop_thread.h"
#include "log/log.h"

#include <boost/thread/thread.hpp>
#include <boost//noncopyable.hpp>
#include <boost/utility.hpp>

/*
 * 一个专门存放eventloop线程的线程池
 * 
 * 
 * 
 * 
 */ 

class eventloop_threadpool : public boost::noncopyable
{
public:
    eventloop_threadpool(event_loop* baseloop, int numOfThreads)
        : baseLoop_(baseloop), numOfThreads_(numOfThreads), started_(false), next_(0)
    {
        if(numOfThreads_ <= 0)
        {
            LOG_INFO("numOfThreads_ <= 0");
            abort();
        }
    }

    ~eventloop_threadpool()
    {
        LOG_INFO("event_loop_threadpool deconstruction");
    }

    void start();

    event_loop* getNextLoop();

private:
    event_loop *baseLoop_;
    bool started_;
    int numOfThreads_;
    int next_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
    std::vector<event_loop*> loops_;
};