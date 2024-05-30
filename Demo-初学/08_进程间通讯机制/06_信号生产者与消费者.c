/********************************
 * 案例：父进程生产者 - 子进程消费者(亲缘进程，可以轻易得到pid进程号)
 * 
 * 问题:非亲缘关系，则很难获得pid号，因为信号就是发送给指定进程号的进程的
 *      答：进程间通讯的机制去传递pid号       
 * *******************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <wait.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define FileName "产品厂房.txt"
void signal_func(int sig)
{
    printf("接收到消费信号\n");
}
int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        exit(-1);
    }
    else if (pid == 0)
    {
        /***** 子进程 *****/
        //先让自己暂停
        signal(SIGUSR1,signal_func);
        pause();    //让自己停止

        int fd = open(FileName, O_RDWR);
        if (fd < 0)
        {
            perror("文件打开失败\n");
            ;
            exit(-1);
        }
        char buf[128] = "";
        read(fd, buf, sizeof(buf) - 1);
        printf("消费了:%s\n", buf);
        exit(0);
    }
    else
    {
        /***** 父进程 *****/
        int fd = open6(FileName, O_RDWR | O_CREAT | O_APPEND, 0666);
        if (fd < 0)
        {
            perror("文件打开失败\n");
            ;
            exit(-1);
        }
        char buf[128] = "ABCDEF";
        for(int i = 0; i < strlen(buf);i++)
        {
            write(fd,&buf[i],1);
            sleep(1);
        }

        kill(pid,SIGUSR1);
        exit(0);
    }

    return 0;
}