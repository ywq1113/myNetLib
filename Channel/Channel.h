#pragma once
#include <sys/epoll.h>
#include <sys/epoll.h>
#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "../eventloop/event_loop.h"
#include "http/http_conn.h"
//#include "Timer.h"

typedef std::function<void()> cb_func;

class event_loop;
class http_conn;

//Channel属于Reactor中的事件，属于一个eventloop，负责fd的IO事件，保存对应的回调函数
//当IO事件发生时，调用该类中的回调函数
class Channel
{
private:
    event_loop* loop_;
    int fd_;
    
    uint32_t events_;
    uint32_t revents_;
    uint32_t lastEvents_;

    //可以找到上层持有该channel的对象
    std::weak_ptr<http_conn> holder_;

    /*
        int parse_URI();
        int parse_Headers();
        int analysisRequest();
    */

    //保存对应的回调函数
    cb_func readHandler_;
    cb_func writeHandler_;
    cb_func errorHandler_;
    cb_func connHandler_;

public:
    Channel(event_loop* loop);
    Channel(event_loop *loop, int fd);
    ~Channel();

    int getFd();

    void setFd(int fd);

    void setHolder(std::shared_ptr<http_conn> holder) { holder_ = holder; }

    void setReadHandler(cb_func&& readHandler) { readHandler_ = readHandler; }

    void setWriteHandler(cb_func&& writeHandler) { writeHandler_ = writeHandler; }

    void setErrorHandler(cb_func&& errorHandler) { errorHandler_ = errorHandler; }

    void setConnHandler(cb_func&& connHandler) { connHandler_ = connHandler; }

    void handleEvents()
    {
        events_ = 0;
        if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
            events_ = 0;
            return;
        }
        if (revents_ & EPOLLERR) {
            if (errorHandler_) errorHandler_();
            events_ = 0;
            return;
        }
        if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
            handleRead();
        }
        if (revents_ & EPOLLOUT) {
            handleWrite();
        }
        handleConn();
    }

    void handleRead();
    void handleWrite();
    void handleError(int fd, int err_num, std::string short_msg);
    void handleConn();

    void setRevents(uint32_t ev) { revents_ = ev; }

    void setEvents(uint32_t ev) { events_ = ev; }

    bool EqualAndUpdateLastEvents()
    {
        if(events_ != lastEvents_)
        {
            lastEvents_ = events_;
            return false;
        }
        return true;
    }

    uint32_t &getEvents() { return events_; }

    uint32_t getLastEvents() { return lastEvents_; }
}

typedef std::shared_ptr<Channel> SP_Channel;