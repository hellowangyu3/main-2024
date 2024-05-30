#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
void *pthread_func_1(void *arg);
void *pthread_func_2(void *arg);
/*************** 互斥锁 *******************
 * 1.锁的初始化：pthread_mutex_init 默认阻塞
 *      int  pthread_mutex_init(pthread_mutex_t  *mutex,  const  pthread_mutex‐attr_t *mutexattr);
 * 2.申请上锁:pthread_mutex_lock
 *      int pthread_mutex_lock(pthread_mutex_t *mutex);
 * 3.申请解锁pthread_mutex_unlock
 *      int pthread_mutex_unlock(pthread_mutex_t *mutex);
 * 4.销毁锁:pthread_mutex_destroy
 *      int pthread_mutex_destroy(pthread_mutex_t *mutex);
 * ***********************************/

pthread_mutex_t mutex_read;
pthread_mutex_t mutex_wrote;
char buf[30] = "";
int main()
{
    pthread_t pthread_value;

    /**** 初始化锁 ****/
    pthread_mutex_init(&mutex_read, NULL);
    pthread_mutex_init(&mutex_wrote, NULL);
    pthread_mutex_lock(&mutex_read); //先上读锁

    /**** 消费者 ****/
    pthread_create(&pthread_value, NULL, pthread_func_2, NULL);

    /**** 生产者 ****/
    pthread_create(&pthread_value, NULL, pthread_func_1, "ABCDEFG");

    /**** 回收线程 *****/
    pthread_join(pthread_value, NULL);
    pthread_join(pthread_value, NULL);
    return 0;
}













void *pthread_func_1(void *arg)
{
    for (int j = 0; j < 5; j++)
    {
        pthread_mutex_lock(&mutex_wrote); //上写锁
        char *str = (char *)arg;
        printf("生产者\n");
        for (int i = 0; i < strlen(str); i++) //生产ABCDEFG
        {
            buf[i] = str[i] + j;
            printf("生产了:%c\n", str[i]+j);
            sleep(1);
        }
        pthread_mutex_unlock(&mutex_read); //解除读锁
    }

    pthread_exit(NULL);
}

void *pthread_func_2(void *arg)
{
    for (int j = 0; j < 5; j++)
    {
        pthread_mutex_lock(&mutex_read); //阻塞，等待读锁的打开，我才能再次上读锁
        printf("消费者\n");
        printf("消费:%s\n", buf);
        memset(buf, 0, sizeof(buf)); //清空
        pthread_mutex_unlock(&mutex_wrote); //解除写锁
    }
    pthread_exit(NULL);
}

