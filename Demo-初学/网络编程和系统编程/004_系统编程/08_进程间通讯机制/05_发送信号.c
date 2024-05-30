/***********************************
 * 函数名1:int kill(pid_t pid, int sig);
 *  功能：向自定进程发送信号
 * 函数名2:int raise(int sig);
 *  功能：向自己发送信号
 * 
 * 参数:
 *      pid:进程号
 *      sig:信号
 * 返回值：
 *      成功：0
 *      失败：-1
 * ********************************/

/*****************************************
 * 函数名：int pause(void);
 * 功能：让当前进程挂起,直到下一个任何信号(必须要注册捕获 或者 终止)到来
 * 参数：
 * 返回值：
 *      成功：0
 *      失败：-1
 * ****************************************/

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#if 1
void signal_SIGALRM(int sig)
{
    printf("自定义信号到来\n");
}
int main()
{
    signal(SIGUSR1,signal_SIGALRM);
    /**** 给自己发送信号 ****/
    int timer = 0;
    while(1)
    {
        timer++;
        sleep(1);
        printf("死循环\n");
        if(timer == 5)
        {
            // raise(SIGKILL); //杀死自己
            // raise(SIGSTOP); //给自己发送一个停止信号
            // kill(getpid(),SIGKILL);
            pause();
        }
    }
    return 0;
}
#endif

/**************************************************
 * 函数名：unsigned int alarm(unsigned int seconds);
 * 功能：给进程设置一个闹钟，时间到后默认结束进程,再次调
 *      用则刷新闹钟时间并返回剩余时间
 * 参数:
 *      seconds:秒数
 * 返回值:
 *      返回剩余秒数
 * ************************************************/
#if 0
void signal_SIGALRM(int sig)
{
    printf("狗已经饿死,无法正常工作\n");
    _exit(-1);
}

int main()  //软件喂狗的模拟
{
    
    int timer = 0;
    signal(SIGALRM,signal_SIGALRM);
    alarm(5);
    printf("成功买入一条家用田园犬\n");
    while (1)
    {
        timer++;
        if(timer % 3 == 0)
        {
            printf("成功喂狗\n");
            alarm(5);   //可以模拟成为喂狗
        }
        sleep(1);
        printf("死循环\n");

        /**** 任务突然间卡死 ***/
        if(timer == 10)
        {
            //出现意外，电机损坏，信号链接不上
            printf("出现意外，电机损坏，信号链接不上\n");
            sleep(5);
        }
    }
    return 0;
}
#endif
