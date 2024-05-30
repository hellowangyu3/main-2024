#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
/*******************************
 * 函数名:int main(int argc,char *argv[])
 * 功能：主程序
 * 参数：命令行参数
 *      int argc：参数的个数
 *      char *argv[]：参数的内容{字符数组指针}  //切记里面的内容为字符串
 * 返回值：int ，用于处理main程序的错误码
 * ******************************/
int main(int argc, char *argv[])
{
    /***** 打印参数内容 ****/
    printf("argc = %d\n", argc);    //参数个数
    for (int i = 0; i < argc; i++)  //参数内容
    {
        printf("argv[%d] = %s\n", i, argv[i]);
    }

    if (argc == 1)
    {
        printf("缺少文件参数\n");
        return -1;
    }

    int fd = -1;
    char buf[1024] = "";
    int len = 0;
    //遍历后面的可执行文件
    for (int i = 1; i < argc; i++)
    {
        fd = open(argv[i], O_RDONLY);
        if (fd == -1)
        {
            continue;
        }
        //读取文件数据并打印到屏幕
        do
        {
            memset(buf, 0, sizeof(buf));          //清空buf数组内容 ---- 防止内容覆盖
            len = read(fd, buf, sizeof(buf) - 1); //读取文件数据
            if (len != 0)
            {
                printf("%s", buf); //输出到屏幕
            }
        } while (len == sizeof(buf) - 1);
        close(fd);
    }

    return 0;
}