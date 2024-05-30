#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <wait.h>
#include <sys/wait.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <arpa/inet.h>
#include <unistd.h>

void Print(struct sockaddr_in *sockaddr, char *buf); //打印接收数据
int main(int argv, char *argc[])
{
    /****  ./程序 IP地址 端口号   ****/
    if (argv != 3)
    {
        printf("参数错误:./程序 IP地址 端口号\n");
        exit(-1);
    }

    char buf[128] = "";
    int len = 0;

    struct sockaddr_in sockaddr;
    sockaddr.sin_addr.s_addr = inet_addr(argc[1]); //192.168.0.255
    sockaddr.sin_port = htons(atoi(argc[2]));      //10000
    sockaddr.sin_family = AF_INET;

    socklen_t sockaddr_len = sizeof(sockaddr);

    /*** 0.创建套接字 ****/
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    /**** 1.创建进程发送端 *****/
    if (fork() == 0) //子进程
    {
        int BUF = 1;
        setsockopt(udp_socket, SOL_SOCKET, SO_BROADCAST, &BUF, sizeof(BUF));

        /*** 2.向广播地址发送数据 ****/
        while (1)
        {
            fgets(buf, sizeof(buf) - 1, stdin);
            //向192.168.0.255 10000 发送数据
            sendto(udp_socket, buf, strlen(buf), 0, (struct sockaddr *)&sockaddr, sockaddr_len);
            if (strncmp("quit", buf, strlen("quit")) == 0)
            {
                break; //跳出循环
            }
        }
        close(udp_socket); //关闭套接字

        exit(0);
    }
    else //父进程
    {
        /*** 1.直接绑定广播ip地址 ****/ //绑定广播地址 192.168.0.255 10000
        if (bind(udp_socket, (struct sockaddr *)&sockaddr, sockaddr_len) == -1)
        {
            perror("绑定失败:");
            exit(-1);
        }
        /*** 2.接收广播的数据 ****/
        while (1)
        {
            memset(buf, 0, sizeof(buf));
            len = recvfrom(udp_socket, buf, sizeof(buf) - 1, 0, (struct sockaddr *)&sockaddr, &sockaddr_len);
            if (len <= 0)
            {
                printf("接收失败\n");
                break;
            }

            Print(&sockaddr, buf);
        }
        close(udp_socket); //关闭套接字
    }
}

void Print(struct sockaddr_in *sockaddr, char *buf)
{
    char *ip = inet_ntoa(sockaddr->sin_addr);
    int port = ntohs(sockaddr->sin_port);

    printf("ip:%s端口号:%d发送:%s\n", ip, port, buf);
}