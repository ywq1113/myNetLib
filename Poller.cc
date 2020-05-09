#include "mylib/Poller.h"
#include "mylib/Channle.h"

using namespace mylib;

Poller::Poller(EventLoop* loop) 
  :ownerLoop_(loop) { }

Poller::~Poller() = default;

bool Poller::hasChannel(Channel* channel) const
{
    //EventLoop中的成员函数，判断是否在IO线程执行
    assertInLoopThread();
    ChannelMap::const_iterator it = channels_.find(channel->fd());
    return it != channels_.end() && it->second == channel;
}
