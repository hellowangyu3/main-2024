/********************************
#include <unistd.h>
#include <signal.h>
void (*signal(int sig, void (*func)(int arg)))(int);
功能:设置信号响应方式(注册信号)
参数:signal(int sig, void (*func)(int arg))
    sig:要设置的信号类型
	func:信号响应后处理的函数(三种方式)
        1.指定信号处理方式:自己定义的函数地址
        2.SIG_DFL代表缺省方式
        3.SIG_IGN代表忽略信号
    arg:传入的信号类型
返回值:函数指针
    成功:返回原先信号处理函数
    失败:返回SIG_ERR
*************************************/

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void signal_func(int sig);  //信号处理函数
int main()
{
    signal(SIGINT,signal_func); //注册信号:按 CTRL + C 触发 SIGINT信号,使用signal_func函数处理该信号
    signal(SIGQUIT,signal_func); //注册信号:按 CTRL + \ 触发 SIGQUIT信号,使用signal_func函数处理该信号

    while(1)
    {
        printf("死循环\n");
        sleep(1);
    }

    return 0;
}

//typedef void (*sighandler_t)(int);
void signal_func(int sig)
{
    switch (sig)
    {
    case SIGINT:    //CTRL + C触发SIGINT信号
        printf("CTRL + C 触发 SIGINT信号,我就不让你结束进程\n");
        break;
    
    case SIGQUIT:
        printf("注册信号:按 CTRL + \\ 触发 SIGQUIT信号,就不让你结束进程\n");
        // system("shutdown"); //调用shell
        break;
    }
    
}