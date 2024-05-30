/**** 信号灯集  和   共享内存 ****/
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define ShmSize 128
/**** 信号灯集初始化共用体 ****/
union semun
{
    int val;               /* 初始化的信号量资源个数 */
    struct semid_ds *buf;  /* Buffer for IPC_STAT, IPC_SET */
    unsigned short *array; /* Array for GETALL, SETALL */
    struct seminfo *__buf; /* Buffer for IPC_INFO*/
};

#if Creat
/****** 创建程序 *****/
int main()
{
    /***** 获取key ******/
    key_t key = ftok("/", 'a');
    /***** 创建 共享内存 和 信号灯集******/
    int shmid = shmget(key, ShmSize, IPC_CREAT | 0666); //共享内存创建 128字节
    int semid = semget(key, 2, IPC_CREAT | 0666);       //信号灯集 2 个信号量
    /***** 初始化信号灯集 *******/
    union semun semnu_temp;
    semnu_temp.val = 1;
    if (semctl(semid, 0, SETVAL, semnu_temp) == -1) //初始化0"写"号信号量的资源为1
    {
        perror("失败原因:");
        printf("初始化信号灯0失败\n");
    }

    semnu_temp.val = 0;
    if (semctl(semid, 1, SETVAL, semnu_temp) == -1) //初始化1"读"号信号量的资源为0
    {
        perror("失败原因:");
        printf("初始化信号灯1失败\n");
    }

    return 0;
}
#endif

#if Write
/****** 生产者 ******/
int main()
{
    /***** 获取key ******/
    key_t key = ftok("/", 'a');
    /***** 创建 共享内存 和 信号灯集******/
    int shmid = shmget(key, ShmSize, IPC_CREAT | 0666); //共享内存创建 128字节
    int semid = semget(key, 2, IPC_CREAT | 0666);       //信号灯集 2 个信号量
    /***** 内存映射 *******/
    char *buf = shmat(shmid, NULL, 0);
    /***** 生产 *********/
    //1.P操作信号量{0_写的信号量}
    struct sembuf sembuf_temp;
    sembuf_temp.sem_num = 0; //操作的信号量编号 0
    sembuf_temp.sem_op = -1; //P操作
    sembuf_temp.sem_flg = 0; //阻塞
    semop(semid, &sembuf_temp, 1);
    //2.开始生产
    int i = 0;
    for (i = 0; i < strlen("ABCDEFG"); i++)
    {
        buf[i] = 'A' + i;
        printf("生产了:%c\n", 'A' + i);
        sleep(1);
    }
    buf[i] = '\0'; //封尾
    //3.V操作信号量{1_读的信号量}
    sembuf_temp.sem_num = 1; //操作的信号量编号 1
    sembuf_temp.sem_op = 1;  //V操作
    sembuf_temp.sem_flg = 0; //阻塞
    semop(semid, &sembuf_temp, 1);

    return 0;
}
#endif

#if Read
/****** 消费者 *****/
int main()
{
    /***** 获取key ******/
    key_t key = ftok("/", 'a');
    /***** 创建 共享内存 和 信号灯集******/
    int shmid = shmget(key, ShmSize, IPC_CREAT | 0666); //共享内存创建 128字节
    int semid = semget(key, 2, IPC_CREAT | 0666);       //信号灯集 2 个信号量
    /***** 内存映射 *******/
    char *buf = shmat(shmid, NULL, 0);

    /***** 生产 *********/
    //1.P操作信号量{1_度的信号量}
    struct sembuf sembuf_temp;
    sembuf_temp.sem_num = 1; //操作的信号量编号 1
    sembuf_temp.sem_op = -1; //P操作
    sembuf_temp.sem_flg = 0; //阻塞
    semop(semid,&sembuf_temp,1);
    //2.开始生产
    printf("消费了:%s\n", buf);
    //3.V操作信号量{0_读的信号量}
    sembuf_temp.sem_num = 0; //操作的信号量编号 0
    sembuf_temp.sem_op = 1;  //V操作
    sembuf_temp.sem_flg = 0; //阻塞
    semop(semid, &sembuf_temp, 1);

    return 0;
}
#endif