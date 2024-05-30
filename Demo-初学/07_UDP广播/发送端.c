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

    /*** 0.创建套接字 ****/
    int udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    /*** 1.设置他为广播发送 ****/
    /********************************
     * 函数名:int setsockopt(int sockfd, int level, int optname,const void *optval, socklen_t optlen);
     * 功能:设置套接字信息
     * 参数:
     *  	sockfd：套接字描述符
     *  	level：选项所属协议层
     *  	optname：所属协议名称
     *  	optval：设置选项值的缓存区
     *  	optlen：选项值的缓存区大小
     * 返回值:
     *  	成功：0
     *  	失败：-1，并设置errno
     * *****************************/
    int BUF = 1;
    setsockopt(udp_socket,SOL_SOCKET,SO_BROADCAST,&BUF,sizeof(BUF));

    /*** 2.向广播地址发送数据 ****/
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
