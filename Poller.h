#ifndef MYLIB_POLLER_H
#define MYLIB_POLLER_H

#include <vector>

#include "EventLoop.h"

namespace mylib
{
class Channel;

class Poller : boost::noncopyable
{
public:
    typedef std::vector<Channel*> ChannelList;

    Poller(EventLoop* loop);
    virtual ~Poller();

    //Timestamp poll(int timeoutMs, ChannelList* activeChannels);

    void updateChannels(Channels* channel);

protected:
    typedef std::map<int, Channel*> ChannelMap;
    ChannelMap channels_;

private:
    EventLoop* ownerloop_;

};
