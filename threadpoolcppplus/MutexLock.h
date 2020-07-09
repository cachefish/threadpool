#ifndef _MUTEXLOCK_H
#define _MUTEXLOCK_H
#include"Noncopyable.h"
#include<pthread.h>

namespace cf
{
class MutexLock:Noncopyable
{
public:
    MutexLock();
    ~MutexLock();
    void lock();
    void unlock();

    pthread_mutex_t*getMutexLockPtr(){return &_mutex;}

private:
    pthread_mutex_t _mutex;
    bool _islocking;
};

class MutexLockGuard
{
public:
    MutexLockGuard(MutexLock&mutex)
    :_mutex(mutex)
    {
        _mutex.lock();
    }
    ~MutexLockGuard()
    {
        _mutex.unlock();
    }
private:
    MutexLock&_mutex;
};

}

#endif