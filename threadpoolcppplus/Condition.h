#ifndef _CONDITION_H
#define _CONDITION_H

#include"Noncopyable.h"
#include<pthread.h>
namespace cf
{
class MutexLock;

class Condition:Noncopyable
{
public:
    Condition(MutexLock&mutex);
    ~Condition();

    void wait();
    void notify();
    void notifyall();

private:
    pthread_cond_t _cond;
    MutexLock &_mutex;
};

}

#endif 