#include "fcntl_lock.h"

#define FileName "商品.txt"
/********* 生产者 *******/
//锁的作用：保护文件的安全性
int main()
{
    int fd = open(FileName, O_RDWR | O_CREAT | O_APPEND, 0777); //打开文件

    int ok = reg_lockw(fd); //阻塞式上锁
    if (ok == -1)
    {
        printf("上锁失败");
        return -1;
    }
    char buf[] = "ABCDEFGHIJK";
    int len = strlen(buf);

    for (int i = 0; i < len; i++)
    {
        write(fd, &buf[i], 1);
        printf("生产了:%c\n", buf[i]);
        sleep(1);
    }

    //生产完了就解锁
    ok = reg_unlockw(fd); //阻塞式解锁
    if (ok == -1)
    {
        printf("解锁失败");
        return -1;
    }
}