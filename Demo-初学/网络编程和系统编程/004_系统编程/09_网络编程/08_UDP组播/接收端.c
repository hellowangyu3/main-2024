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

    /*** 1.创建套接字 ****/
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0); 
    /*** 2.加入到多播组 ****/
    // struct ip_mreqn
    // {
    //     struct in_addr imr_multiaddr;  //主播地址
    //     struct in_addr imr_address;    //自己的地址
    //     int imr_ifindex;               //索引
    // };
    struct ip_mreqn mreqn;            //多播组结构体
    memset(&mreqn, 0, sizeof(mreqn)); //清空结构体
    mreqn.imr_multiaddr.s_addr = inet_addr(argc[1]);
    //默认自己的INADDR_ANY ((in_addr_t) 0x00000000) 默认自己任意的可用ip地址
    mreqn.imr_address.s_addr = htons(INADDR_ANY); 
    //ip的协议层:IPPROTO_IP             //链路层之上的一层，如果没有加入多播则其他主机会在链路层直接丢掉数据包
    //ip的协议选项:IP_ADD_MEMBERSHIP    //加入多播
    if(setsockopt(udp_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreqn, sizeof(mreqn)) == -1)
    {
        perror("加入多播组失败:");
        exit(-1);
    }

    /*** 1.直接绑定多播ip地址 ****/ //绑定多播地址 224.0.0.1 10000
    if (bind(udp_socket, (struct sockaddr *)&sockaddr, sockaddr_len) == -1)
    {
        perror("绑定失败:");
        exit(-1);
    }
    /*** 2.接收多播的数据 ****/
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

void Print(struct sockaddr_in *sockaddr, char *buf)
{
    char *ip = inet_ntoa(sockaddr->sin_addr);
    int port = ntohs(sockaddr->sin_port);

    printf("ip:%s端口号:%d发送:%s\n", ip, port, buf);
}