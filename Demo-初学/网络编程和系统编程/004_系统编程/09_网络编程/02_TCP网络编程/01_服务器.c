/*************  套接字  *******************************************************
 * 函数名:int socket(int domain, int type, int protocol);
 * 功能:创建套接字
 * 参数:
 *      int domain:
 *          AF_INET(ipv4)
 *          AF_INET6(ipv6)
 *          AF_UNIX(原始)
 *      int type:
 *          SOCK_STREAM(TCP)
 *          SOCK_DGRAM(UDP)
 *          SOCK_RAW(原始套接字)
 *      int protocol:
 *          默认填写0
 * 返回值:
 *      成功：返回套接字文件描述符
 *      失败:-1
 * ***************************************************************************/

/************* 绑定 ip和端口号  ************************************************
 * 函数名:int bind(int sockfd, const struct sockaddr *addr,socklen_t addrlen);
 * 功能:功能绑定ip和端口号（需要用到网络字节序）
 * 参数:
 *      int sockfd：套接字特殊描述符
 *      struct sockaddr *addr:包含了ip和端口号的结构体
 *      socklen_t addrlen：结构体长度
 *                 struct sockaddr_in {
 *                   sa_family_t    sin_family; //address family: AF_INET 
 *                   in_port_t      sin_port;   //port 端口号 
 *                   struct in_addr sin_addr;   //internet address  IP地址
 *                  };

 * 返回值:
 *      成功：0
 *      失败：-1
 * **************************************************************************/

/************** 监听 *****************************
 * 函数名:int listen(int sockfd, int backlog);
 * 功能:将套接字设置为被动模式，用于接收用户请求
 * 参数:
 *      sockfd：套接字
 *      backlog：最大线路，最大队列(Max = 5)
 * 返回值:
 *      成功:0
 *      失败:-1
 * *********************************************/

/************** 等待连接 *****************************
 * 函数名:int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
 * 功能:等待用户连接，默认阻塞等待
 * 参数:
 *      sockfd：套接字
 *      struct sockaddr *addr：用户端的信息(ip和端口号) ，如果不想接受用户客户端主机信息可以不用接收直接NULL
 *      socklen_t *addrlen：结构体大小  ， 不接收客户端主机信息则可以0
 * 返回值:
 *      成功:客户端所用的套接字
 *      失败:-1
 * *********************************************/

#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
typedef struct TCP_socket
{
    int fd_cid;                    //客户端的socket套接字文件描述符
    struct sockaddr_in socketaddr; //客户端主机信息(ip和端口号)
} TCP_socket_t;

void *pthread_func(void *arg);
int main()
{
    //1.创建套接字
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    //2.绑定ip和端口号
    struct sockaddr_in socketaddr;
    socketaddr.sin_addr.s_addr = inet_addr("192.168.0.196"); //ip地址:必须绑定自己的ip地址否则绑定失败
    socketaddr.sin_port = htons(10000);                      //端口号 10000 - 40000
    socketaddr.sin_family = AF_INET;                         //协议：ipv4


    //连续绑定，他会失败，上一个程序的端口号还没有解绑(1-10秒时间)
    if (bind(tcp_socket, (struct sockaddr *)&socketaddr, sizeof(socketaddr)) == -1)
    {
        perror("绑定失败:");
        exit(-1);
    }
    printf("绑定成功\n");

    //3.监听套接字
    if (listen(tcp_socket, 5) == -1)
    {
        perror("监听失败:");
        exit(-2);
    }

    //4.等待用户的链接
    while (1)
    {
        int cid = -1;
        struct sockaddr_in cid_sockaddr;
        socklen_t socklen = sizeof(cid_sockaddr);
        //5.等待用户端连接
        cid = accept(tcp_socket, (struct sockaddr *)&cid_sockaddr, &socklen);
        if (cid == -1)
        {
            printf("接收客户端失败\n");
            continue;
        }

        //6.通过线程去接收
        pthread_t pthread;
        TCP_socket_t TCP_socket = {cid, cid_sockaddr};
        pthread_create(&pthread, NULL, pthread_func, &TCP_socket); //开创一个线程
    }

    //7.关闭套接字
    close(tcp_socket);

    return 0;
}

void *pthread_func(void *arg)
{
    TCP_socket_t TCP_socket = *(TCP_socket_t *)arg;
    printf("客户端的套接字文件描述符 = %d\n", TCP_socket.fd_cid);
    printf("客户端的ip地址:%s\t端口号:%d\n", inet_ntoa(TCP_socket.socketaddr.sin_addr), ntohs(TCP_socket.socketaddr.sin_port));

    char buf[1024] = "";
    int len = 0;
    while (1)
    {
        memset(buf, 0, sizeof(buf));
        len = read(TCP_socket.fd_cid, buf, sizeof(buf) - 1); //没有数据默认阻塞
        if(len <= 0)
        {
            break;
        }
        printf("接收%s的%d的数据为:%s\n",
               inet_ntoa(TCP_socket.socketaddr.sin_addr),  //ip地址
               len, //实际接收到数据长度
               buf);//接收到的数据
    }

    printf("%s退出聊天室\n",inet_ntoa(TCP_socket.socketaddr.sin_addr));
    pthread_exit("");   //退出线程
}
