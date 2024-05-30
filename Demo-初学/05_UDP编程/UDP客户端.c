#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
void *func(void *arg)
{
    int udp_socket = *(int *)arg;
    char buf[128] = "";
    int len = 0;
    while(1){
        len = recvfrom(udp_socket,buf,sizeof(buf)-1,0,NULL,NULL);
        printf("接收到数据:%s\n",buf);
    }
}

int main(int argc, char *argv[])
{
    /***** 1.验证用户传入参数是否是ip 和 端口号数量 ***/
    if (argc != 3)
    {
        printf("参数不对:请输入 ./程序名 ip地址 端口号\n");
        exit(-1);
    }

    /****** 2.创建UDP流式套接字 ***/
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    /****** 3.绑定ip和端口号 ****/
    unsigned short port = atoi(argv[2]); //小端字节序
    char *ip = argv[1];                  //点分形式
    struct sockaddr_in tcp_sockaddr;
    tcp_sockaddr.sin_family = AF_INET;            //协议
    tcp_sockaddr.sin_port = htons(port);          //需要将小端转为大端字节序
    tcp_sockaddr.sin_addr.s_addr = inet_addr(ip); //将点分转为大端字节序

    char buf[128] = "";
    int len = 0;
    socklen_t sockaddr_len = 0;
    
    pthread_t pthread;
    pthread_create(&pthread,NULL,func,&udp_socket);  //创建线程处理

    while (1){
        fgets(buf,sizeof(buf)-1,stdin);
        sendto(udp_socket,buf,strlen(buf),0,(struct sockaddr *)&tcp_sockaddr,
        sizeof(tcp_sockaddr));
    }
    return 0;
}