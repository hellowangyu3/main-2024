/********** 守护进程 ******************
 * 思想：在会话组组长健在的时候进程脱离脱离会话组
 * 1.fork()   创建子进程，先结束父进程(子进程:孤儿进程->被认暴发户当爹)
 * 2.setsid() 创建会话(脱离上一个会话组,自己建立了会话组长{子进程就是新会话组组长})
 * 3.chdir()  改变工作路径
 * 4.umask()  修改权限掩码
 * 5.close()/dup2()  关闭集成过来的父进程的文件描述符
 * ***********************************/

#include <stdio.h>
int Daemon(char *path,char *argv[]);
int main()
{
    char *argv[] = {"1234",NULL};
    Daemon("20向文件写入时间.out",argv);
    return 0;
}

#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

#define ChekValue(Value1,Opretion,Value2,Return) \
    if ((Value1)Opretion(Value2)){\
        printf("%s,%d\n",__func__,__LINE__);\
        return Return;\
    }
        
int Daemon(char *path,char *argv[])
{
    // 1.fork()   创建子进程，先结束父进程(子进程:孤儿进程->被认暴发户当爹)
    ChekValue(fork(), !=, 0, -1);
    sleep(2);
    // 2.setsid() 创建会话(脱离上一个会话组,自己建立了会话组长{子进程就是新会话组组长})
    ChekValue(setsid(), ==, -1, -2);
    // 3.chdir()  改变工作路径
    ChekValue(chdir("/tmp"), ==, -1, -3);
    // 4.umask()  修改权限掩码
    umask(0);
    // 5.close()/dup2()  关闭集成过来的父进程的文件描述符
    //fd = open("error.log")
    //dup2(fd,1);
    for(int i = 0; i < getdtablesize();i++)
    {
        close(i);
    }

    if(execv(path,argv) == -1)
    {
        printf("运行进程失败\n");
    }
}
