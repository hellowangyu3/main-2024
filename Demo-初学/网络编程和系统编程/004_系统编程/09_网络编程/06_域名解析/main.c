/******* 域名解析 **************************
 * 函数名:struct hostent *gethostbyname(const char *name);
 * 功能:域名解析得到域名主机信息
 * 参数:
 *    const char *name:域名或者ip
 * 返回值:struct hostent *
 *      成功：返回数据结构体
 *      失败：NULL
 * ***************************************/

/********释放解析后的数据空间******************
 * 函数名:void endhostent(void);
 * 功能:释放gethostbyname函数申请的空间
 * 参数：无
 * 返回值：无
 * ****************************************/
/********释放解析后的数据空间******************
 * struct hostent   //只支持IPv4
 * {
 *     char *h_name;       // 主机正式名称 
 *     char **h_aliases;   // 别名列表 
 *     int h_addrtype;     // 主机地址类型 
 *     int h_length;       // 地址的长度 
 *     char **h_addr_list; // 地址列表   -> 但是他存储的是 unsigned int 的网络大端字节序
 * }
 * #define h_addr h_addr_list[0] // 为了向后兼容 ;;.
 * ****************************************/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argv, char *argc[])
{
    if (argv != 2)
    {
        printf("参数错误: ./程序名 域名或者ip地址\n");
        exit(0);
    }

    struct hostent *hs = gethostbyname(argc[1]); //进行解析
    if (hs == NULL)
    {
        perror("解析失败:");
        exit(-1);
    }
    /******* 打印主机相关数据 *****/
    printf("主机正式名称:%s\n", hs->h_name);

    for (int i = 0; hs->h_aliases[i] != NULL; i++)
    {
        printf("别名列表[%d] = %s\n", i, hs->h_aliases[i]);
    }

    char *ip = NULL;
    for (int i = 0; hs->h_addr_list[i] != NULL; i++)
    {
        ip = inet_ntoa(*(struct in_addr *)hs->h_addr_list[i]);  //需要将网络大端字节序转为点分形式自己才能看得懂
        printf("地址列表[%d] = %s\n", i, ip);
    }
    endhostent();   //释放掉信息结构体空间
}
//面向对象的是想:有申请就需要有释放,学习面向对象的时候，就会学习构造函数(实例化变量{对象})和析构函数(销毁他的时候默认调用)