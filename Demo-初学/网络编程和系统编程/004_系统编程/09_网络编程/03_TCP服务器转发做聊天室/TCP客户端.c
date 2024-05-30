#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("参数错误:./程序名 ip地址 端口号\n");
        exit(-1);
    }

    int cid = socket(AF_INET, SOCK_STREAM, 0);
    if (cid == -1)
    {
        perror("创建套接字失败:");
        exit(-1);
    }

    /******* 链接服务器 ****/
    unsigned short port = atoi(argv[2]); //小端字节序
    char *ip = argv[1];                  //点分形式
    struct sockaddr_in tcp_sockaddr;
    tcp_sockaddr.sin_family = AF_INET;            //协议
    tcp_sockaddr.sin_port = htons(port);          //需要将小端转为大端字节序
    tcp_sockaddr.sin_addr.s_addr = inet_addr(ip); //将点分转为大端字节序

    if(connect(cid,(struct sockaddr*)&tcp_sockaddr,sizeof(tcp_sockaddr)) == -1)
    {
        perror("链接服务器失败:");
        exit(-1);
    }

    void *pthread_func(void *arg);   //函数内部声明

    pthread_t pthread;
    pthread_create(&pthread,NULL,pthread_func,&cid);

    char buf[128];
    while(1)
    {
        fgets(buf,sizeof(buf)-1,stdin);
        write(cid,buf,strlen(buf));
    }
    return 0;
}

//线程函数处理读取服务器发过来的数据
void *pthread_func(void *arg)
{
    int cid = *(int *)arg;
    char buf[128];
    while(1)
    {
        memset(buf,0,sizeof(buf));
        read(cid,buf,sizeof(buf)-1);
        printf("%s",buf);
    }
}
