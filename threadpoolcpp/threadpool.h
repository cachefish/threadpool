/*  线程池: *      一种线程使用模式。线程过多会带来调度开销，
进而影响缓存局部性和整体性能。而线程池维护着多个线 程，
等待着监督管理者分配可并发执行的任务。这避免了在处理短
时间任务时创建与销毁线程的代价。线程池不仅能够 保证内核
的充分利用，还能防止过分调度。可用线程数量应该取决于可用
的并发处理器、处理器内核、内存、网络 sockets等的数量。 *  
线程池的应用场景： *      1.  需要大量的线程来完成任务，且完成
任务的时间比较短。 WEB服务器完成网页请求这样的任务，使用线 
程池技术是非常合适的。因为单个任务小，而任务数量巨大，你可
以想象一个热门网站的点击次数。 但对于长时间的任 务，比如一个
Telnet连接请求，线程池的优点就不明显了。因为Telnet会话时间比
线程的创建时间大多了。 *      2.  对性能要求苛刻的应用，比如要求
服务器迅速响应客户请求。 *      3.  接受突发性的大量请求，但不至
于使服务器因此产生大量线程的应用。突发性大量客户请求，在没有
线 程池情况下，将产生大量线程，虽然理论上大部分操作系统线程数
目最大值不是问题，短时间内产生大量线程可能使内 存到达极限，出
现错误. *  线程池的种类： *  线程池示例： *      1.  创建固定数量线程池
，循环从任务队列中获取任务对象， *      2.  获取到任务对象后，执行任务
对象中的任务接口 */

#pragma once

#include<iostream>
#include<queue>
#include<pthread.h>
#include<unistd.h>

#define MAX_THREAD 5
typedef bool(*handler_t)(int);

class ThreadTask{
    private:
        int _data;
        handler_t _handler;

    public:
        ThreadTask():_data(-1),_handler(NULL){}
        ThreadTask(int data,handler_t handler_t){
            _data = data;
            _handler = handler_t;
        }

        void setTask(int data,handler_t handler){
                _data = data;
                _handler = handler;          
        }

        void Run(){
            _handler(_data);
        }

};

class ThreadPool{
    private:
        int _thread_max;
        int _thread_cur;
        bool _tp_quit;
        std::queue<ThreadTask*> _task_queue;
        pthread_mutex_t _lock;
        pthread_cond_t _cond;

    private:
        void LockQueue(){
            pthread_mutex_lock(&_lock);
        }
        void UnLockQueue(){
            pthread_mutex_unlock(&_lock);
        }
        void WakeUpOne(){
            pthread_cond_signal(&_cond);
        }
        void WakeUpAll(){
            pthread_cond_broadcast(&_cond);
        }
        void ThreadQuit(){
            _thread_cur--;
            UnLockQueue();
            pthread_exit(NULL);
        }
        void ThreadWait(){
            if(_tp_quit){
                ThreadQuit();
            }
            pthread_cond_wait(&_cond,&_lock);
        }
        bool IsEmpty(){
            return _task_queue.empty();
        }
        static void *thr_start(void*arg){
            ThreadPool*tp = (ThreadPool*)arg;
            while(1){
                tp->LockQueue();
                while(tp->IsEmpty()){
                    tp->ThreadWait();
                }
                ThreadTask*tt;
                tp->PopTask(&tt);
                tp->UnLockQueue();
                tt->Run();
                delete tt;
            }
            return NULL;
        }

        public:
            ThreadPool(int max = MAX_THREAD):_thread_max(max),_thread_cur(max),_tp_quit(false){
                    pthread_mutex_init(&_lock,NULL);
                    pthread_cond_init(&_cond,NULL);
            }

            ~ThreadPool(){
                pthread_mutex_destroy(&_lock);
                pthread_cond_destroy(&_cond);
            }

                bool PoolInit(){
                    pthread_t tid;
                    for(int i =0;i<_thread_max;i++){
                        int ret = pthread_create(&tid,NULL,thr_start,this);
                        if(ret != 0){
                            std::cout<<"create pool thread error!\n";
                            return false;
                        }
                    }
                    return true;
                }

                bool PushTask(ThreadTask*tt){
                    LockQueue();
                    if(_tp_quit){
                        UnLockQueue();
                        return false;
                    }
                        _task_queue.push(tt);
                        WakeUpOne();
                        UnLockQueue();
                        return true;
                }
                bool PopTask(ThreadTask**tt){
                        *tt  = _task_queue.front();
                        _task_queue.pop();
                        return true;
                }
                bool PoolQuit(){
                    LockQueue();
                    _tp_quit = true;
                    UnLockQueue();
                    while(_thread_cur>0){
                        WakeUpAll();
                        usleep(1000);
                    }
                    return true;
                }
};







