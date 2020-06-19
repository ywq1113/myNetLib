#include "Channel.h"

#include <unistd.h>
#include <cstdlib>
#include <iostream>

#include <queue>

//#include "Epoll.h"
#include "../eventloop/event_loop.h"
#include "../timer/utils.h"

Channel::Channel(event_loop* loop) 
    : loop_(loop), fd_(0), events_(0), lastEvents_(0) { } 

Channel::Channel(event_loop* loop, int fd)
    : loop_(loop), fd_(fd), events_(0), lastEvents_(0) { }

Channel::~Channel() {
  // loop_->poller_->epoll_del(fd, events_);
  // close(fd_);
}

int Channel::getFd() { return fd_; }

int Channel::setFd(int fd) { fd_ = fd; }

void Channel::handleRead()
{
    if(readHandler_)
        readHandler_();
}

void Channel::handleWrite()
{
    if(writeHandler_)
        writeHandler_();
}

void Channel::handleConn()
{
    if(connHandler_)
        connHandler_();
}

