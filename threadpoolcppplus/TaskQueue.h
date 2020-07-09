#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H
#include"Condition.h"
#include"MutexLock.h"

#include<queue>
using std::queue;
//任务队列
namespace cf
{
class Task;
typedef Task*ElemType;
class TaskQueue
{
public:
    TaskQueue(size_t queSize);
    
    bool empty()const;
    bool full()const;
    void push(const ElemType&elem);
    ElemType pop();

    void wakeup()
    {
        _flag = false;
        _notEmpty.notifyall();
    }

private:
    size_t _queSize;   //队列大小
    queue<ElemType> _que;
    MutexLock _mutex;
    Condition _notFull;
    Condition _notEmpty;
    bool _flag;
};


}

#endif