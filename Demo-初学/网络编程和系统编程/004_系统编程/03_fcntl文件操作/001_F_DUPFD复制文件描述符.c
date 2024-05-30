#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

/**************************************
 * 函数名:int fcntl(int fd, int cmd, ...arg);
 * 功能:已经打开的文件描述符操作
 * 参数:
 *      int fd:已经打开的文件描述符
 *      int cmd：命令
 *          F_DUPFD：复制文件描述符
 *      arg：可变参数,根据cmd命令来传参
 *          F_DUPFD:arg为最大文件描述符
 * 返回值：
 *      根据cmd命令的返回值
 *      F_DUPFD：返回一个新的文件描述符
 * **************************************/

/******************************************
 * 函数名：int dup2(int oldfd, int newfd);
 * 功能：复制文件描述符
 * 参数：
 *      oldfd：老的文件描述符
 *      newfd：新的文件描述符
 * 返回值：
 *      成功：新的描述符
 *      失败：-1
 * ******************************************/

//默认打开三个文件描述符stdin(0),stdout(1),stdeer(2)
int main()
{
#if 1
    int fd_new = fcntl(1,F_DUPFD,0);
    if(fd_new == -1)
    {
        printf("失败: %d\n",fd_new);
        return -1;
    }
    printf("新的文件描述符:%d\n",fd_new);
    write(fd_new,"吃了没\n",11);
#endif

#if 1
    int fd_new = 6;
    dup2(1, fd_new);
    printf("新的文件描述符:%d\n", fd_new);
    write(fd_new, "吃了没\n", 11);
    write(1, "吃了没\n", 11);
#endif
    return 0;
}