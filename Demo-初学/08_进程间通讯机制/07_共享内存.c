/******** 共享内存操作 ********************************************
 * 0.通过ftok()获取Key值,如果失败返回-1
 * 1.通过shmget()创建共享内存 
 * 2.通过shmat()映射共享内存
 * 3.读写直接赋值
 * 4.通过shmdt()函数撤销映射
 * 5.通过shmctl()删除共享内存
 * 注意：删除的时候共享内存的时候，一定要注意所有地址映射都销毁后在删除共享内存
 * **************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
int main()
{
    /*** 0.通过ftok()获取Key值 *****/
    key_t key = ftok(".", 'A');
    if (key == -1)
    {
        printf("获取键值失败\n");
        return -1;
    }

    /*** 通过shmget()创建共享内存 ****/
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1)
    {
        printf("创建共享内存失败\n");
        return -2;
    }

    /*** 2.通过shmat()映射共享内存 ****/
    //void *shmat(int shmid, const void *shmaddr, int shmflg);
    //int shmid:共享内存的id号
    //const void *shmaddr:默认使用NULL由系统自动映射
    //int shmflg:0默认可读可写
    char *buf = shmat(shmid, NULL, 0);
#if Write
    while (1)
    {
        printf("请输入数据:");
        scanf("%s", buf);
        if (strcmp("quit", buf) == 0)
        {
            break;
        }
    }
    /**** 4.通过shmdt()函数撤销映射 ****/
    //int shmdt(const void *shmaddr);
    shmdt(buf);
    /**** 5.通过shmctl()删除共享内存 ****/
    shmctl(shmid,IPC_RMID,NULL);
#endif

#if Read
    while (1)
    {
        printf("读取到数据:%s\n", buf);
        sleep(1);
        if (strcmp("quit", buf) == 0)
        {
            break;
        }
    }
    /**** 4.通过shmdt()函数撤销映射 ****/
    //int shmdt(const void *shmaddr);
    shmdt(buf);
#endif

    return 0;
}