/******************** 整型相互转换 ***********************
 *      将主机字节序转换成网络字节序
 * 函数名:uint32_t htonl(uint32_t hostlong);
 * 函数名:uint16_t htons(uint16_t hostshort);
 *      
 *      将网络字节序转换成主机字节序
 * 函数名:uint32_t ntohl(uint32_t netlong);
 * 函数名:uint16_t ntohs(uint16_t netshort);
 * ********************************************/
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    unsigned int temp_h = 0x12345678;

    printf("转换前:\n");
    printf("主机字节序:0x%x\n", temp_h);

    printf("转换后:\n");
    unsigned int temp_n = htonl(temp_h);
    printf("网络字节序:0x%x\n", temp_n);

    printf("转回后:\n");
    temp_h = ntohl(temp_n);
    printf("主机字节序:0x%x\n", temp_h);

    printf("字符串转网络:\n");
    //字符：点分形式
    char *str_ip = "192.168.0.6";
    in_addr_t ip_temp = inet_addr(str_ip);
    printf("网络字节序:0x%x\n", ip_temp);

    struct in_addr temp = *(struct in_addr*)&ip_temp;
    str_ip = inet_ntoa(temp);
    printf("主机字节序字符:%s\n", str_ip);
        return 0;
}
/****************  字符与整型转换   *************
 *      将字符转换成网络字节序整数
 * 函数名:in_addr_t inet_addr(const char *cp);
 * 
 *      将网络字节序整数转换字符
 * 函数名:char *inet_ntoa(struct in_addr in)
 * *******************************************/