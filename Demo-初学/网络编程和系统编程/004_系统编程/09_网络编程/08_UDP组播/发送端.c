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
    sockaddr.sin_addr.s_addr = inet_addr(argc[1]);
    sockaddr.sin_port = htons(atoi(argc[2]));
    sockaddr.sin_family = AF_INET;

    socklen_t sockaddr_len = sizeof(sockaddr);

    /*** 1.创建套接字 ****/
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);

    /*** 2.向组播地址发送数据 ****/
    while (1)
    {
        fgets(buf,sizeof(buf)-1,stdin);
        sendto(udp_socket,buf,strlen(buf),0,(struct sockaddr *)&sockaddr,sockaddr_len);
        if(strncmp("quit",buf,strlen("quit")) == 0)
        {
            break;  //跳出循环
        }
    }
    close(udp_socket); //关闭套接字
}
