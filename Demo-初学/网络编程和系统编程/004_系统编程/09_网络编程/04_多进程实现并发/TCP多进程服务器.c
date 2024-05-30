
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <wait.h>
#include <sys/types.h>
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


    int cid = -1;
    int _pid = 0;
    char buf[128] = "";
    int len = 0;
    /****** 5.循环等待响应 ******/
    while(1)
    {
        cid = accept(tcp_socket,NULL,0);    //默认阻塞
        if(cid > 0)
        {
            /******* 开始一个多进程处理 *********/
            if(fork() == 0)
            {
                while(1)
                {
                    memset(buf,0,sizeof(buf));
                    len = read(cid,buf,sizeof(buf)-1);
                    if(len <= 0)
                    {
                        break;
                    }
                    printf("%s\n",buf);

                    if(strncmp("quit",buf,strlen("quit")) == 0)
                    {
                        break;
                    }
                }
                close(cid);
                printf("子进程退出%d\n",getpid());
                exit(0);    //结束子进程，PCB空间数据没有被释放，需要父进程去回收
            }
        }

        /****** 在这里回收么？ ******/
        while((_pid = waitpid(-1,NULL,WNOHANG)) > 0)//非阻塞
        {
            printf("成功为子进程收尸：%d\n",_pid);
        }
    }
    return 0;
}