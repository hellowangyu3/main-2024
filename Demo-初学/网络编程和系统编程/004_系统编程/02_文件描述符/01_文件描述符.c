#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <string.h>
/**************************
 * stdin(0),    //行缓存
 * stdout(1),   //行缓存    \n 结束
 * stderr(2),   //无缓存区
 * 
 * printf() 函数默认参数 stdout
 * scanf() 函数默认参数 stdin
 * *********************/
int main()
{
    //fprintf(stdout, "打印的数据\n");
#if 1
    //系统调用的操作是：无缓存的
    write(1,"吃了没，吃了啥，去万家丽吃饭么？",strlen("吃了没，吃了啥，去万家丽吃饭么？"));
    write(1,"吃了没，吃了啥，去万家丽吃饭么？",strlen("吃了没，吃了啥，去万家丽吃饭么？"));
    write(1,"吃了没，吃了啥，去万家丽吃饭么？",strlen("吃了没，吃了啥，去万家丽吃饭么？"));
    while(1);
#endif

#if 1
    printf("吃了没，吃了啥，去万家丽吃饭么？");
    printf("吃了没，吃了啥，去万家丽吃饭么？");
    printf("吃了没，吃了啥，去万家丽吃饭么？");
    printf("吃了没，吃了啥，去万家丽吃饭么？");
    printf("吃了没，吃了啥，去万家丽吃饭么？");
    printf("\n");
    while(1);
#endif

#if 1
    fclose(stdin);    //关闭文件
    fclose(stderr);    //关闭文件
    FILE *fp1 = fopen("test.txt","r");   //打开文件  ---  FILE 里面拥有文件描述符
    if(fp1 != NULL)
    {
        //int fileno(FILE *stream);
        int fd1 = fileno(fp1);    //转换
        printf("文件描述符号:%d\n",fd1);
    }
    // fclose(fp1);    //关闭文件

    FILE *fp2 = fopen("xxxx.txt","r");   //打开文件  ---  FILE 里面拥有文件描述符
    if(fp2 != NULL)
    {
        int fd2 = fileno(fp2);    //转换
        printf("文件描述符号:%d\n",fd2);
    }
    while(1);
#endif 
    
    return 0;
}