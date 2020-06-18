// Copyright 2010, Shuo Chen.  All rights reserved.
// http://code.google.com/p/muduo/
//
// Use of this source code is governed by a BSD-style license
// that can be found in the License file.

// Author: Shuo Chen (chenshuo at chenshuo dot com)
//
// This is an internal header file, you should not include this.

#ifndef MUDUO_NET_TIMER_H
#define MUDUO_NET_TIMER_H

#include "muduo/base/Atomic.h"
#include "muduo/base/Timestamp.h"
#include "muduo/net/Callbacks.h"

// Timerstamp.h head file obtain ：
// 1) Invalid and valid timestamp
// 2) default copy/assignment/dtor
// 3) comparable operator '==' '!=' '<' '>' '<=' '>='
// 4) Output string type: toString(), toFormattedString(bool), 
// 5) Get time of now: now(), fromUnixTime(),
// 6) sum of time: addTime(Timestamp, double)

// 非阻塞服务端编程中，对于定时的任务，不能调用sleep()来使之挂起。
// 主事件循环被挂起，无法处理IO事件，这会让程序失去响应。
// 正确做法是把它变成一个特定的消息，到时候触发相应的处理函数。

namespace muduo
{
namespace net
{

///
/// Internal class for timer event.
///
class Timer : noncopyable
{
 public:
  Timer(TimerCallback cb, Timestamp when, double interval)
    : callback_(std::move(cb)),  //std::move()把对象cb转移到新变量callback_下，源对象调用析构函数释放资源
      expiration_(when),
      interval_(interval),
      repeat_(interval > 0.0),
      sequence_(s_numCreated_.incrementAndGet())
  { }

  void run() const
  {
    callback_();
  }

  //通过public成员函数访问private数据成员
  Timestamp expiration() const  { return expiration_; } 
  bool repeat() const { return repeat_; }
  int64_t sequence() const { return sequence_; }

  void restart(Timestamp now);

  static int64_t numCreated() { return s_numCreated_.get(); }

 private:
  const TimerCallback callback_;  //回调函数
  Timestamp expiration_;  //过期时间
  const double interval_;  //时间间隔
  const bool repeat_;  //判断是否重复
  const int64_t sequence_;  //记录当前定时器的编号

  static AtomicInt64 s_numCreated_;  //记录定时器个数
};

}  // namespace net
}  // namespace muduo

#endif  // MUDUO_NET_TIMER_H
