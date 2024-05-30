#include <stdlib.h>
#include <stdio.h>
/****************************
 * 函数名:int system(const char *command);
 * 功能：先调用fork()创建进程，然后在调用execl()代码指令集替换
 *      父进程挂起，子进程先运行，然后子进程结束后，父进程被调度
 * 参数:
 *      command:可执行文件路径 + 指令
 * 返回值:
 *      成功:0
 *      失败:-1
 * ***************************/
       
int main()
{
    int ok = system("clear");
    printf("ok = %d\n",ok);
    return 0;
}
