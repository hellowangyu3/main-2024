/*********************************
 * 函数名:int pipe(int pipefd[2]);
 * 功能:无名管道，应用亲缘关系进程
 * 参数:
 *      int pipefd[2]:文件描述符数组
 *                  pipefd[0]:读端
 *                  pipefd[1]:写端
 * 返回值:
 *     成功:0
 *     失败:-1 
 * *****************************/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>
#include <sys/types.h>
int main()
{
    pid_t pipefd[2];

    pipe(pipefd);
    /**** 既然无名管道要有继承关系，所以必须在fork前进程申请无名管道 ***/
    pid_t pid = fork(); //创建子进程
    if(pid < 0)
    {
        exit(0);
    }
    else if(pid == 0)
    {
        /**** 子进程 *****/
        char buf[128] = "";
        close(pipefd[1]);   //关闭子进程的无名管道的写端
        //想用读端
        while(1)
        {
            memset(buf,0,sizeof(buf));
            read(pipefd[0],buf,sizeof(buf)-1);  //读取无名管道数据
            printf("子进程:buf = %s\n",buf);
            sleep(1);
            // if(strcmp(buf,"close") == 0)
            // {
            //     close(pipefd[0]);   //关闭子进程的无名管道的读端,当只有管道只有一个端存在，管道出现炸裂
            // }

            if(strcmp(buf,"quit") == 0)
            {
                break;
            }
        }
        printf("子进程接收到quit指令，退出状态\n");
        exit(0);
    }else{
        /**** 父进程 ****/
        char buf[128] = "";
        close(pipefd[0]);   //关闭父进程的无名管道的读端
        //想用写端
        while(1)
        {
            scanf("%s",buf);    //scanf 默认阻塞
            write(pipefd[1],buf,strlen(buf));   //向无名管道写入数据
            if(strcmp(buf,"close") == 0)
            {
                close(pipefd[1]);   //关闭子进程的无名管道的写端,当只有管道只有一个端存在，管道出现炸裂
            }
            if(strcmp(buf,"quit") == 0)
            {
                break;
            }
        }
        printf("父进程输入quit指令，让子进程结束\n");
    }

    pid_t r_pid = wait(NULL); //给子进程收尸
    printf("成功为%d收尸\n",r_pid);
    return 0;
}

