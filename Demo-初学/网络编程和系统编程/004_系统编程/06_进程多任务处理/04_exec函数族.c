/************* exec函数族 ******************
 * 功能：进程中的代码指令集"替换"
 * 函数名1：int execl(const char *path, const char *arg, ... (char  *) NULL);
 * 函数名2：int execlp(const char *path, const char *arg, ... (char  *) NULL);
 * 函数名3：int execv(const char *path, char *const argv[]);
 * 参数：
 *      path：可执行程序指令集路径
 *      arg:命令参数
 *      ....:可变参数，必须要以NULL结尾
 *      argv[]:arg 和 ...的集合
 * 返回值:
 *      成功返回: 0
 *      失败返回:-1
 * ***************************************/
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
int main()  //父进程
{
    pid_t pid = fork();
    /***** 父进程:pid = 17029 ****/
    /***** 子进程:pid = 0 ****/
    if (pid < 0)
    {
        return -1;
    }
    else if (pid == 0)
    {
        /**** 子进程 *****/
        #if 0
        //int ok = execl("./10测试","111","222","333",NULL);    //代码指令集"替换"
        #else
        char *argv[] = {"111","222","333","444",NULL};
        int ok = execv("./10测试",argv);
        #endif
        
        if(ok == -1)
        {
            printf("失败\n");
        }else{
            printf("成功\n");
        }
    }
    else
    {
        printf("死等子进程结束\n");
        wait(NULL);
        printf("子进程结束\n");
    }

    return 0;
}
