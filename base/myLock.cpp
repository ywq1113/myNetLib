#include "myLock.h"

/*
 * try_lock尝试锁住互斥量，如果互斥量被其他线程占有，也不会阻塞当前线程 
 * 调用该函数会出现以下三种情况：
 * 1）如果当前互斥量没有被其他线程占有，则锁住互斥量，直到调用unlock
 * 2）如果当前互斥量被其他线程锁住，则当前调用线程返回 false，而并不会被阻塞掉
 * 3）如果当前互斥量被当前调用线程锁住，则会产生死锁(deadlock)
 */

void Mutex::Mutex() {
    pthread_mutex_init(&mutex_, NULL);
    holder_ = 0;
}

void Mutex::~Mutex() {
    assert(holder_ == 0);
    pthread_mutex_destroy(&mutex_);
}

void Mutex::lock() const 
{
    pthread_mutex_lock(&mutex_);
}

void Mutex::unlock() const
{
    holder_ = 0;
    pthread_mutex_unlock(&mutex_);
}

bool Mutex::try_lock()
{
    if(holder_ == 0){
        this->lock();
    }
    else if(holder_ == CurrentThread::tid()){
        error << "Dead Lock" << endl;
    }
    else {
        return false;
    }
    return true;
}