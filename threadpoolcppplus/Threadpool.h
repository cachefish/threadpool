#ifndef _THREADPOOL_H__
#define _THREADPOOL_H__

#include "TaskQueue.h"
#include <vector>
#include <memory>
using std::vector;
using std::unique_ptr;


namespace cf
{

class Thread;
class WorkerThread;
class Threadpool
{
	friend WorkerThread;
public:
	Threadpool(size_t, size_t);
	~Threadpool();

	void start();
	void stop();
	void addTask(Task *);

private:
	Task * getTask();
	void threadFunc();

private:
	size_t _threadNumber;
	size_t _queSize;
	vector<unique_ptr<Thread> > _threads;
	TaskQueue _taskque;
	bool _isExit;
};

}//end of namespace cf


#endif
