#include"TaskQueue.h"

namespace cf
{
TaskQueue::TaskQueue(size_t queSize)
:_queSize(queSize)
,_mutex()
,_notFull(_mutex)
,_notEmpty(_mutex)
,_flag(true)
{

}
    
bool TaskQueue::empty()const
{
    return _que.size() == 0;   
}
bool TaskQueue::full()const
{
    return _que.size() == _queSize;
}

void TaskQueue::push(const ElemType&elem)
{
    MutexLockGuard autolock(_mutex);
    while(full())
    {
        _notFull.wait();
    }
    _que.push(elem);
    _notEmpty.notify();   //通知消费者来取
}

ElemType TaskQueue::pop()
{
    MutexLockGuard autolock(_mutex);
    while (_flag&&empty())
    {
        /* code */
        _notEmpty.wait();
    }
    if(_flag){
        ElemType tmp = _que.front();
        _que.pop();
        _notFull.notify();   
        return tmp;
    }else{
        return nullptr;
    }
}


}