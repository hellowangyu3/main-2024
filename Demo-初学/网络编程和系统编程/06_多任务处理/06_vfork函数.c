#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid = vfork();    //创建子进程，并让子进程先运行，直到子进程运行exec或者结束才运行父进程
    if(pid < 0){
        return -1;
    }else if(pid == 0){
        /**** 子进程 *****/
        printf("getpid() = %d : getppid() = %d\n",getpid(),getppid());
        execl("./10测试","123465",NULL);
    }else{
        /**** 父进程 ****/
        printf("getpid() = %d : getppid() = %d\n",getpid(),getppid());
        pid_t ppppppid = wait(NULL);
        printf("收尸成功:%d\n",ppppppid);
    }

    return 0;
}