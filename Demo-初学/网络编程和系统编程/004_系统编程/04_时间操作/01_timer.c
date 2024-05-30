#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
/**********************
 * 函数名:time_t time(time_t *tloc);
 * 功能:返回开始1970-01-01 00:00:00 +0000 (UTC).到现在的秒数
 * 参数:
 *     time_t *tloc：拥有存储间隔的秒数
 *            说明:如果传入 NULL 则不想保存
 *                 如果传入 非NULL 则想保存
 * 
 *      //long int  ====== time_t
 * 返回值:
 *      间隔的秒数
 * ********************/

/****************************************
 * 函数名：struct tm *gmtime(const time_t *timep);
 * 功能：将时间转换成国际时间
 * 参数：
 *      const time_t *timep：秒数时间
 * 返回值：返回结构体
 *      struct tm*：时间结构体指针
 * **************************************/

/****************************************
 * 函数名：struct tm *localtime(const time_t *timep);
 * 功能：将时间转换本地际时间
 * 参数：
 *      const time_t *timep：秒数时间
 * 返回值：返回结构体
 *      struct tm*：时间结构体指针
 * **************************************/

/****************************************
 * 函数名：char *asctime(const struct tm *tm);
 * 功能：将时间结构体转换成 字符串
 * 参数：
 *      const struct tm *tm：时间结构体地址
 * 返回值：返回结构体
 *      char *：时间字符串
 * **************************************/
#define FileNmae "timer.txt"
int main()
{
    int fd = open(FileNmae, O_RDWR | O_CREAT | O_APPEND, 0666);
    struct tm *tm = NULL;
    char *timer;

    time_t tloc = 0;
    time_t temp_tloc = 0;
    int i = 0;
    while (1)
    {
        temp_tloc = time(&tloc);    //获取时间秒数

        tm = localtime(&temp_tloc); //将时间秒数 转成 本地时间 结构体
        // printf("temp_tloc = %ld\n",temp_tloc);
        // printf("tloc = %ld\n",tloc);
        // printf("年:%d\n",tm->tm_year + 1900);
        // printf("月:%d\n",tm->tm_mon + 1);
        // printf("日:%d\n",tm->tm_mday);

        printf("%04d-%02d-%02d\t", tm->tm_year + 1900, tm->tm_mon + 1, tm->tm_mday);
        printf("%02d:%02d:%02d\n", tm->tm_hour, tm->tm_min, tm->tm_sec);

        /***** 将时间结构体转换成字符串 *****/
        timer = asctime(tm);    //结构体 转换成 字符串
        printf("现在时刻:%s\n", timer);

        sleep(1);   //延时1s
        i++;
        if(i % 10 == 0)
        {
            write(fd,timer,strlen(timer));
        }
    }
  
    return 0;
}