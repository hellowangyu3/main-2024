#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include "node.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
typedef struct CID
{
    int cid;                         //客户端的sokect套接字
    struct sockaddr_in tcp_sockaddr; //客户端的ip和端口号
    socklen_t len;                   //信息结构体长度
} CID_t;

//
Node_t *head_cid; //定义了一个链表

int main(int argc, char *argv[])
{
    /***** 1.验证用户传入参数是否是ip 和 端口号数量 ***/
    if (argc != 3)
    {
        printf("参数不对:请输入 ./程序名 ip地址 端口号\n");
        exit(-1);
    }

    /***** 2.创建套接字 ****/
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket == -1)
    {
        perror("套接字创建失败:");
        exit(-1);
    }

    /****** 3.绑定ip和端口号 ****/
    unsigned short port = atoi(argv[2]); //小端字节序
    char *ip = argv[1];                  //点分形式
    struct sockaddr_in tcp_sockaddr;
    tcp_sockaddr.sin_family = AF_INET;            //协议
    tcp_sockaddr.sin_port = htons(port);          //需要将小端转为大端字节序
    tcp_sockaddr.sin_addr.s_addr = inet_addr(ip); //将点分转为大端字节序

    if (bind(tcp_socket, (struct sockaddr *)&tcp_sockaddr, sizeof(tcp_sockaddr)) == -1)
    {
        perror("绑定ip和端口失败:");
        exit(-1);
    }

    /****** 4.监听 **************/
    if (listen(tcp_socket, 5) == -1)
    {
        perror("监听失败:");
        exit(-1);
    }

    /****** 5.等待客户端链接 *****/
    head_cid = Node_Init(); //初始化链表

    CID_t CID;
    pthread_t pthread;

    void *pthread_func(void *arg); //函数体内声明函数
    while (1)
    {
        CID.cid = accept(tcp_socket, (struct sockaddr *)&CID.tcp_sockaddr, &CID.len);
        if (CID.cid == -1)
        {
            perror("接收客户端响应失败:");
            continue;
        }

        Node_PushBack(&head_cid, &CID, sizeof(CID));        //将客户端插入到链表进行管理
        pthread_create(&pthread, NULL, pthread_func, &CID); //创建线程处理客户端数据
    }

    return 0;
}

void Send_to(void *arg1, void *arg2, char *data, int len);
int cmp_func(void *arg1, void *arg2);
void *pthread_func(void *arg)
{
    CID_t CID = *(CID_t *)arg;
    char *ip = inet_ntoa(CID.tcp_sockaddr.sin_addr);
    char buf[128];
    char buf_data[1024];
    int len = 0;
    while (1)
    {
        memset(buf, 0, sizeof(buf)); //清空buf
        len = read(CID.cid, buf, sizeof(buf) - 1);

        if (len <= 0)
        {
            printf("主动断开\n");
            break;
        }
        else
        {
            //接收成功
            Node_t *head = head_cid->next; //获取第一个元素首地址

            //“%s->%s\n”
            sprintf(buf_data, "ip:%s发送￥:%s\n", ip, buf);

            while (head->data != NULL)
            {
                Send_to(head->data, &CID, buf_data, strlen(buf_data));
                head = head->next;
            }
        }
    }

    Node_t *head = head_cid->next; //获取第一个元素首地址
    //“%s->%s\n”
    sprintf(buf_data, "ip:%s发送￥:有内鬼,停止了交易，大家散了\n", ip);
    while (head->data != NULL)
    {
        Send_to(head->data, &CID, buf_data, strlen(buf_data));
        head = head->next;
    }
    Node_Erase(Node_find(head_cid, &CID, cmp_func)); //将他移除

    pthread_exit("");
}

void Send_to(void *arg1, void *arg2, char *data, int len)
{
    CID_t CID = *(CID_t *)arg1;
    CID_t CID_temp = *(CID_t *)arg2;
    if (CID.cid != CID_temp.cid)
    {
        write(CID.cid, data, len);
    }
}

int cmp_func(void *arg1, void *arg2)
{
    CID_t CID = *(CID_t *)arg1;
    CID_t CID_temp = *(CID_t *)arg2;
    if (CID.cid == CID_temp.cid)
    {
        return 0;
    }
    return -1;
}
