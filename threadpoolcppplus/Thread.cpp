#include "Thread.h"

namespace cf
{


Thread::~Thread()
{
    if(_isRunning){
        pthread_detach(_pthid);
        _isRunning = false;
    }
}

void Thread::start()
{
    pthread_create(&_pthid,nullptr,threadFunc,this);
    _isRunning = true;
}  
void Thread::join()
{
    if(_isRunning) {
        pthread_join(_pthid,nullptr);
        _isRunning = false;
    }
}
void *Thread::threadFunc(void *arg)
{
    Thread*pthread = static_cast<Thread*> (arg);
    if(pthread){
        pthread->run();
    }
    return nullptr;
}

}