#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("参数异常\n");
        return -1;
    }

    //1.打开文件 test.txt(被拷贝文件) 张三.txt(新建文件)
    int fd_read = open(argv[1], O_RDONLY);
    if (fd_read == -1)
    {
        perror("被拷贝文件不存在:");
        return -2;
    }

    int fd_new = open(argv[2], O_WRONLY | O_CREAT, 0777);

    /****** 循环读取被拷贝文件数据写入到新建文件内 ****/
    char buf[128] = "";
    int len = 0;
    do
    {
        memset(buf, 0, sizeof(buf));               //防止内容覆盖
        len = read(fd_read, buf, sizeof(buf) - 1); //读取被拷贝文件
        write(fd_new, buf, len);                   //写入新建文件
    } while (len != 0);

    /***** 关闭打开的文件 ******/
    close(fd_read);
    close(fd_new);

    return 0;
}