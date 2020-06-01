#include"threadpool.h"


bool handler(int data){
    srand(time(NULL));
    int n = rand()%5;
    printf("Thread: %p Run Test:%d--sleep %d esc\n",(void*)pthread_self(),data,n);
}
int main()
{
    int i;
    ThreadPool pool;
    pool.PoolInit();
    for(i=0;i<10;i++)
    {
        ThreadTask*tt= new ThreadTask(i,handler);
        pool.PushTask(tt);
    }
    pool.PoolQuit();
    return 0;
}