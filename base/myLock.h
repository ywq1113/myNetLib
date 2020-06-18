#ifndef MYLOCK_H
#define MYLOCK_H

#include <pthread.h>
#include "CurrentThread.h"

//接口类命名
class ILock 
{
public:
    virtual ~Lock() { }
    virtual void lock() const = 0;
    virtual void unlock() const = 0;
};

//Mutex Lock
class Mutex: public ILock
{
public:
    Mutex();
    ~Mutex();

    virtual void lock() const;
    virtual void unlock() const;
    bool try_lock() const;
private:
    mutable pthread_mutex_t mutex_;  //设计为永远处于可变的状态，const成员函数可以修改该成员变量
    pid_t holder_;  //持有该锁的线程id
};


