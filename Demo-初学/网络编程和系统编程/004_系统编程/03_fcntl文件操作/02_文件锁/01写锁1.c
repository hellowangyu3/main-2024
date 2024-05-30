#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
/**************************************
 * 函数名:int fcntl(int fd, int cmd, ...arg);
 * 功能:已经打开的文件描述符操作
 * 参数:
 *      int fd:已经打开的文件描述符
 *      int cmd：命令
 *          F_DUPFD：复制文件描述符
 *          F_SETLK:设置锁
 *          F_GETLK:获取锁
 *      arg：可变参数,根据cmd命令来传参
 *          F_DUPFD:arg为最大文件描述符
 *  *       F_SETLK:struct flock结构体
 *          F_GETLK:struct flock结构体
 * 返回值：
 *      根据cmd命令的返回值
 *      F_DUPFD：返回一个新的文件描述符
 * **************************************/
#define FileName "测试文件.txt"
/****************************************************
*struct flock   //锁的内容
*{
*    short int l_type;   // 锁类型: F_RDLCK读, F_WRLCK写, or F_UNLCK无.	
*    short int l_whence; // 偏移位置:(like `lseek').  
*    __off_t l_start;    // 开始位置.  
*    __off_t l_len;      // 上锁长度：0默认到末尾，非0指定大小  
*    __pid_t l_pid;      // 锁的进程ID.  
*};
*******************************************************/
typedef struct flock flock_t; //取别名

void lock_init(struct flock *lock, short type, short whence, off_t start, off_t len);
int readw_lock(int fd);
int writew_lock(int fd);
int writew_lock(int fd);
int unlock(int fd);

int main()
{
    int fd = open(FileName, O_RDWR);
    if (fd == -1)
    {
        return -1;
    }

    char buf[20] = "吃了没?\n";
    while (1)
    {
        /******* 2.上锁 *****/
        writew_lock(fd);
        /****** 3.写入数据 ****/
        write(fd,buf,strlen(buf));
        /****** 4.关闭锁 *****/
        unlock(fd);
        sleep(2);
    }

    close(fd);
    return 0;
}

/*****************************************
 * 锁的初始化
 * 
 * 
 * ***************************************/
void lock_init(struct flock *lock, short type, short whence, off_t start, off_t len)
{
    if (lock == NULL)
        return;
    lock->l_type = type;
    lock->l_whence = whence;
    lock->l_start = start;
    lock->l_len = len;
}
int readw_lock(int fd)
{
    if (fd < 0)
    {
        return -1;
    }
    struct flock lock;
    lock_init(&lock, F_RDLCK, SEEK_SET, 0, 0);
    if (fcntl(fd, F_SETLKW, &lock) != 0)
    {
        return -1;
    }
    return 0;
}
int writew_lock(int fd)
{
    if (fd < 0)
    {
        return -1;
    }
    struct flock lock;
    lock_init(&lock, F_WRLCK, SEEK_SET, 0, 0);
    if (fcntl(fd, F_SETLKW, &lock) != 0)
    {
        return -1;
    }
    return 0;
}
int unlock(int fd)
{
    if (fd < 0)
    {
        return -1;
    }
    struct flock lock;
    lock_init(&lock, F_UNLCK, SEEK_SET, 0, 0);
    if (fcntl(fd, F_SETLKW, &lock) != 0)
    {
        return -1;
    }
    return 0;
}

pid_t lock_test(int fd, short type, short whence, off_t start, off_t len)
{
    struct flock lock;
    lock_init(&lock, type, whence, start, len);
    if (fcntl(fd, F_GETLK, &lock) == -1)
    {
        return -1;
    }
    if (lock.l_type == F_UNLCK)
        return 0;
    return lock.l_pid;
}