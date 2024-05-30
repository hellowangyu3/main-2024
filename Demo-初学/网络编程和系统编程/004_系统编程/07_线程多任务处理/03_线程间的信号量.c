#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
void *pthread_func_1(void *arg);
void *pthread_func_2(void *arg);
/*********** 信号量 **************
 * 1.初始化:sem_init//初始化资源数量
 *      int sem_init(sem_t *sem, int pshared, unsigned int value);
 *      参数:
 *          sem:     信号量
 *          pshared: 0线程，1进程
 *          value:   资源数量
 * 2.P操作:sem_wait //申请使用资源
 *      int sem_wait(sem_t *sem);
 * 3.V操作:sem_post //向信号量增加资源
 *      int sem_post(sem_t *sem);
 * *******************************/
char buf[30] = "";
/**** 信号量结构体变量 ****/
sem_t sem_read;
sem_t sem_write;

int main()
{
    pthread_t pthread_value;   
    /**** 初始化信号量 ****/
    sem_init(&sem_read, 0, 0);
    sem_init(&sem_write, 0, 1);
    /**** 消费者 ****/
    pthread_create(&pthread_value, NULL, pthread_func_2, NULL);

    /**** 生产者 ****/
    pthread_create(&pthread_value, NULL, pthread_func_1, "ABCDEFG");

    /**** 回收线程 *****/
    pthread_join(pthread_value, NULL);
    pthread_join(pthread_value, NULL);
    return 0;
}

//操作：同步或者异步的时候一定要考虑到死锁情况
void *pthread_func_1(void *arg)
{
    for (int j = 0; j < 2; j++)
    {
        sem_wait(&sem_write);   //消耗 写资源从 1 -> 0
        char *str = (char *)arg;
        printf("生产者\n");
        for (int i = 0; i < strlen(str); i++) //生产ABCDEFG
        {
            buf[i] = str[i] + j;
            printf("生产了:%c\n", str[i] + j);
            sleep(1);
        }
        sem_post(&sem_read);    //增加 读资源从 0 -> 1
    }

    pthread_exit(NULL);
}

void *pthread_func_2(void *arg)
{
    for (int j = 0; j < 2; j++)
    {
        sem_wait(&sem_read);    //消耗 读资源从 1 - >
        printf("消费者\n");
        printf("消费:%s\n", buf);
        memset(buf, 0, sizeof(buf)); //清空
        sem_post(&sem_write);   //增加 写资源 0 -> 1
    }
    pthread_exit(NULL);
}


