#include <stdio.h>
#include <unistd.h>
/******************************
 * 函数名:int access(const char *pathname, int mode);
 * 功能：判断文件权限
 * 参数:
 *      const char *pathname:文件名
 *      int mode:权限
 *          F_OK：是否存在
 *          R_OK：是否可读
 *          W_OK：是否可写
 *          X_OK：是否可执行
 * 返回值:
 *  成立：0
 *  不成立：-1
 * *****************************/
#define FileName "张三.txt"
int main()
{
    /****** 1.文件是否存在 ****/
    int OK_flag = access(FileName, F_OK);
    if (OK_flag == 0)
    {
        printf("%s 文件存在\n", FileName);
    }
    else
    {
        printf("%s 文件不存在\n", FileName);
        return -1;
    }

    OK_flag = access(FileName, R_OK);
    if (OK_flag == 0)
    {
        printf("%s 文件可读\n", FileName);
    }
    else
    {
        printf("%s 文件不可读\n", FileName);
    }

    OK_flag = access(FileName, W_OK);
    if (OK_flag == 0)
    {
        printf("%s 文件可写\n", FileName);
    }
    else
    {
        printf("%s 文件不可写\n", FileName);
    }

    OK_flag = access(FileName, X_OK);
    if (OK_flag == 0)
    {
        printf("%s 文件可执行\n", FileName);
    }
    else
    {
        printf("%s 文件不可执行\n", FileName);
    }

    return 0;
}