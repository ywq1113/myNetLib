// 2020.5.8
//
//learn from muduo by Chuo Chen
//
// Author: Wenqi Yang

#ifndef MYLIB_CURRENTTHREAD_H
#define MYLIB_CURRENTTHREAD_H

#include "mylib/base/types.h"

namespace mylib 
{
namespace CurrentThread
{
  extern __thread int t_cachedTid;  
  extern __thread char t_tidString[32];
  extern __thread int t_tidStringLength;
  extern __thread const char* t_threadName;
  void cacheTid();

  inline int tid()
  {
      //long __bulitin_expect(long expr, long c)是gcc内建函数，
      //进行分支预测，期望expr == c，如果c为0，那么执行if分支可能性小
      //否则执行else分支可能性小
      //gcc在编译时，会将可能性大的代码紧跟前面的代码
      //使用该函数可以对程序进行优化，减少指令跳转带来性能上的下降
      //在华为云的服务器上，g++使用这个函数会报错，not declared
      //if(__bulitin_expect(t_cachedTid == 0, 0)) {
          //cacheTid();
      //}
      if(t_cachedTid == 0)
          cacheTid();
      return t_cachedTid;
  }

  inline const char* tidStr()
  {
      return t_tidString;
  }

  inline int tidStrLen()
  {
      return t_tidStringLength;
  }

  inline const char* name()
  {
      return t_threadName;
  }

  //bool isMainThread();

  string stackTrace(bool demangle);

} //CurrentThread
} //mylib

#endif
