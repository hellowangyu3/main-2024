#include <stdio.h>
#include <unistd.h>
int main(int argv,char *argc[])
{
    for(int i = 0; i < argv;i++)
    {
        printf("argc[%d] = %s\n",i,argc[i]);
    }

    while(1)
    {
        printf("测试程序\n");
        sleep(1);
    }
    
    
    return 0;
}