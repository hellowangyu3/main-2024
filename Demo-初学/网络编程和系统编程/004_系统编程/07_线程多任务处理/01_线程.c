/******** 线程操作 *****
 * ?:设置线程状态
 * 1.创建线程:pthread_create
 * 2.线程结束:pthread_exit
 * 3.回收线程:pthread_join
 ********************/

/***************************************
 * 编译的时候需要链接线程库 "-l pthread"
 * 函数名:int pthread_create(pthread_t *thread,     //线程结构体地址
 *                          const pthread_attr_t *attr, //线程属性设置结构体地址：NULL{默认：结合态}
 *                          void *(*start_routine) (void *), //线程的执行回调函数:void *返回值,void *参数
 *                          void *arg);//给线程函数传参
 * 线程状态:结合态 Vs 分离态(类似孤儿进程)
 * 功能：创建线程
 * 返回值:
 *      成功：0
 *      失败:错误码
 *************************************/

/**************************************************************
 * 初始化线程属性：
 * int pthread_attr_init(pthread_attr_t *attr);
 * 修改线程分离态
 * 线程分离状态的函数：设置线程属性，分离or非分离
 * int pthread_attr_setdetachstate(pthread_attr_t *attr, int detachstate);
 * 获取程属性: 分离or非分离
 * int pthread_attr_getdetachstate(pthread_attr_t *attr, int *detachstate);
 * 参数：
	 attr：已初始化的线程属性
	 detachstate：设置线程状态
		PTHREAD_CREATE_DETACHED（分离线程）
		PTHREAD_CREATE_JOINABLE（非分离线程）
*******************************************************************/
#include <pthread.h> //线程操作头文件
#include <stdio.h>
#include <unistd.h>

void *pthread_func1(void *arg); //声明线程回调函数
void *pthread_func2(void *arg);
void *pthread_func3(void *arg);
int main()
{
    printf("自己的进程号:%d\n", getpid());
    pthread_t thread;    //线程结构体
    pthread_attr_t attr; //线程属性结构体
    /***** 初始化线程属性结构体 并设置 线程状态 *****/
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);

    /***** 开始创建线程 ****/
    // int dat1 = 10,dat2 = 20;
    // pthread_create(&thread,&attr,pthread_func1,&dat1);
    // pthread_create(&thread,&attr,pthread_func1,&dat2);
    pthread_create(&thread, &attr, pthread_func2, NULL);
    pthread_create(&thread, &attr, pthread_func3, NULL);
    /***** 进程结束，随之线程也会结束 ****/
    while (1)
    {
    }

    printf("进程结束\n");
    return 0;
}

/**** 线程的回调函数 *****/
void *pthread_func1(void *arg)
{
    int *str = (int *)arg;
    while ((*str)--)
    {
        printf("%d\n", *str);
        sleep(1);
        // if(*str == 5)
        // {
        //     int a = 10 / (*str - 5);
        // }
    }
    if (fork() == 0)
    {
        printf("父进程:%d\n", getppid());
    }
    pthread_exit("");
}

char buf[20] = "";
int buf_flag = 0;
#include <string.h>
void *pthread_func2(void *arg)
{

    while (1)
    {
        if (buf_flag == 0)  //判断锁
        {
            buf_flag = 1;   //上锁
            for (int i = 0; i < strlen("张三"); i++)
            {
                buf[i] = "张三"[i];
                sleep(1);
            }
            printf("buf = %s\n", buf);
            buf_flag = 0;   //解锁
            sleep(1);
        }
    }
    pthread_exit("");
}

void *pthread_func3(void *arg)
{
    while (1)
    {
        if (buf_flag == 0)  //判断锁
        {
            buf_flag = 1;   //上锁
            for (int i = 0; i < strlen("李四"); i++)
            {
                buf[i] = "李四"[i];
                sleep(1);
            }
            printf("buf = %s\n", buf);
            buf_flag = 0;   //解锁
            sleep(1);
        }
    }
    pthread_exit("");
}