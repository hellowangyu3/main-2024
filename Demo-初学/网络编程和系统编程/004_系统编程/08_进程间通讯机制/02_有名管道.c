/************************
 * 函数名:int mkfifo(const char *pathname, mode_t mode);
 * 功能：创建有名管道
 * 参数:
 *     pathname:有名管道的文件名路径
 *     mode：权限  
 * 返回值:
 *      成功:0
 *      失败:-1
 * *************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#if Creat
int main()
{
    if (mkfifo("管道文件", 0666) == -1)
    {
        perror("管道创建失败:");
        exit(0);
    }
    return 0;
}
#endif












#if Write
int main()
{
    char buf[128] = "";
    int fd = open("管道文件",O_WRONLY);
    while(1)
    {
        printf("请输入要写入管道的数据\n");
        fgets(buf,sizeof(buf)-1,stdin);
        write(fd,buf,strlen(buf));
    }

    return 0;
}
#endif



























#if Read
int main()
{
    char buf[128] = "";
    int fd = open("管道文件",O_RDONLY);
    while(1)
    {
        memset(buf,0,sizeof(buf));
        read(fd,buf,sizeof(buf)-1);
        printf("接收到的数据:%s\n",buf);
    }

    return 0;
}
#endif