#include"MutexLock.h"


namespace cf
{
MutexLock::MutexLock():_islocking(false)
{
    pthread_mutex_init(&_mutex,nullptr);
}

MutexLock::~MutexLock()
{
    pthread_mutex_destroy(&_mutex);
}

void MutexLock::lock()
{
    pthread_mutex_lock(&_mutex);
    _islocking=true;
}

void MutexLock::unlock()
{
    pthread_mutex_unlock(&_mutex);
    _islocking = false;
}

}