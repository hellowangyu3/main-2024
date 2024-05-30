/*******************************
 * 函数名:int remove(const char *pathname);
 * 功能：删除文件或者目录
 * 参数:
 *      pathname:文件名
 * 返回值：
 *      成功：0
 *      失败：-1
 * *******************************/
#include <stdio.h>
int main(int argv,char *argc[])
{
    if(argv == 1)
    {
        return -1;
    }

    for(int i = 1; i < argv;i++)
    {
        remove(argc[i]);
    }

    return 0;
}