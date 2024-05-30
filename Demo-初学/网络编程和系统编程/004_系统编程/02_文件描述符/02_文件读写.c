/*********  系统调用 -> 文件操作 ******************
 * 1.引入关于文件操作的头文件
 *  1.1 引入关于 open 函数的头文件
 *  
 * 2.打开文件 
 *  函数名：int open(const char *pathname, int flags, mode_t mode);
 *  参数：
 *      pathname：打开的文件路径名 
 *      flags：标志位
 *          O_RDONLY:只读
 *          O_WRONLY:只写
 *          O_RDWR:可读可写
 *          O_APPEND：追加写
 *          O_CREAT：创建文件 ----- 必须使用 mode 填写文件权限
 *      mode：文件权限(O_CREAT有关)
 *  返回值：文件描述符
 *      成功：非负整数 >= 0 的数
 *      失败：-1
 * 
 * 3.读写操作（read读，write写，seek偏移）
 *  
 * ********************************************/
#include <stdlib.h>
/*************************************
 * 函数名：void exit(int status);
 * 功能：结束 "进程" ，并且返回一个值给系统，而且还会清空缓存区
 * 头文件：#include <stdlib.h>
 * 参数：
 *      status：低八位有效的返回值
 * 返回值：无
 * *************************************/
#include <unistd.h>
/*************************************
 * 函数名：ssize_t read(int fd, void *buf, size_t count);
 * 功能：向文件描述符所指向的文件进行读取
 * 头文件：#include <unistd.h>
 * 参数：
 *      fd：文件描述符
 *      buf：读取数据存放的内存首地址
 *      count：要读取文件多大字节数数据放入到buf中
 * 返回值：ssize_t 无符号长整型
 *     读取到的字节数
 * *************************************/
#include <unistd.h>
/*************************************
 * 函数名：ssize_t write(int fd, const void *buf, size_t count);
 * 功能：向文件描述符所指向的文件进行写操作
 * 头文件：#include <unistd.h>
 * 参数：
 *      fd：文件描述符
 *      buf：向文件写入的数据首地址
 *      count：要写入多大数据到文件里面
 * 返回值：ssize_t 无符号长整型
 *     成功写入的字节数
 * *************************************/

#include <unistd.h>
/*************************************
 * 函数名：int close(int fd);
 * 功能：关闭open打开的文件描述符
 * 头文件：#include <unistd.h>
 * 参数：
 *      fd：文件描述符
 * 返回值：int
 *     成功：0
 *     失败：-1
 * *************************************/


//1.1 引入关于 open 函数的头文件
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
//引入标准输入输出
#include <stdio.h>  //void perror(const char *s);
#include <string.h> //void *memset(void *s, int c, size_t n); 内存空间数据重置
int main()
{
    //2.打开文件
    int fd = open("test.txt",1026); //fd 接收打开的文件描述符
    if(fd == -1)
    {
        perror("文件描述符打开失败:");
        exit(-1);
    }

    //3.读写操作
    char buf[1024] = "";
    memset(buf,0,sizeof(buf));

#if 0   //读操作
    int len = read(fd,buf,10);   //读取两个字节
    printf("len = %d字节\t 内容是:%s\n",len,buf);
#else   //写操作
    int len = write(fd,"万家丽吃饭",strlen("万家丽吃饭"));
    printf("len = %d字节\n",len);
#endif

    //4.关闭文件
    close(fd);
    return 0;
}