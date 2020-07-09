#ifndef __TASK_H__
#define __TASK_H__
//作为基类
namespace cf
{

class Task
{
public:
	virtual void process() = 0;
};

}//end of namespace cf

#endif
