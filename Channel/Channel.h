#ifndef MYLIB_CHANNEL_H
#define MYLIB_CHANNEL_H

#include <functional>
#include <memory>

class EventLoop;

class Channel : boost::noncopyable
{
public:
    typedef boost::function<void()> cb_func;  //使用boost::function<>实现函数回调功能，代替函数指针

    Channel(EventLoop* loop, int fd);

    void handleEvent();
    
    void setReadCallback(const EventCallback& readCallback)
    { readCallback_ = readCallback; }
    
    void setWriteCallback(const EventCallback& writeCallback)
    { writeCallback_ = writeCallback; }

    void setErrorCallback(const EventCallback& errorCallback)
    { errorCallback_ = errorCallback; }

    int fd() const { return fd_; }
    int events() const { return events_; }
    
    void set_revents(int revt) { revents_ = revt; }
    bool isNoneEvent() const { return events_ == kNoneEvent; }

    //for IO multiplexing
    int index() { return index_; }
    void set_index(int idx) { index_ = idx; }

    EventLoop* ownerLoop() { return loop_; }

private:
    void update();

    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;

    EventLoop*  loop_;
    const int   fd_;
    int         events_;  //events_是关心的IO事件
    int         revents_; //revents_是当前活动的事件
    int         index_;
};   
