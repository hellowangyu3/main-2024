#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#define FileName "时间文件.txt"
int main()
{
    int fd = open(FileName,O_CREAT|O_RDWR|O_APPEND,0666);

    char buf[128];
    char *str = NULL;
    time_t timer;
    
    while(1)
    {
        sleep(1);

        time(&timer);   //获取时间
        str = asctime(localtime(&timer));
        write(fd,str,strlen(str));
    }

    

    return 0;
}