/***************************************
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
函数名:int semget(key_t key, int nsems, int semflg);
功能:信号灯的创建/打开
参数:
	key:key和信号灯关联的key
			IPC_PRIVATE:私有的信号灯对象
			ftok函数生成:共享的信号灯对象
	nsems:集合中包含的计数信号灯个数(每一个信号灯表示一类资源)
	shmflg:指定信号灯的标志位 （IPC_CREAT|0666）
        	 IPC_CREAT:创建
			IPC_EXCL:判断是否存在，存在则返回EOF,返回errno错误码 = EEXIST
返回值:
	成功:信号灯id
	失败:将返回-1，并返回表示错误的errno
附加说明:信号灯只能初始化一次需要用到IPC_EXCL标志位
    	所以：创建信号灯的负责初始化
*******************************************/


/**********************************************
函数名:int semop(int semid, struct sembuf *sops, size_t nsops);
功能:信号灯的P/V操作 
参数:
	semid:要操作的信号灯集id
	sops:描述对信号灯操作的结构体(对多个信号灯的话，可以定义结构体数组)
	nsops:要操作信号灯的个数
返回值:
	成功:0
	失败:将返回-1，并返回表示错误的errno
**************************************************************/
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
union semun //需要自己定义
{
    int val;               /* 值SETVAL */
    struct semid_ds *buf;  /* IPC_STAT, IPC_SET的缓冲区 */
    unsigned short *array; /* 数组的GETALL, SETALL */
    struct seminfo *__buf; /* IPC_INFO缓冲区(linux) */
};

int main()
{
    /**** 获取Key 值 ****/
    key_t key = ftok(".", 'A');

    /**** 创建信号灯集 ****/
    int semid = semget(key, 2, IPC_CREAT | 0666); //创建了2个信号灯的一个集合
#if 0   
    /**** 初始化信号灯集 ****/
    union semun semnum1;
    semnum1.val = 2;
    semctl(semid, 0, SETVAL, &semnum1); //注意：信号灯编号从0开始|操作了信号灯0设置他的资源有2个

    semnum1.val = 0;
    semctl(semid, 1, SETVAL, &semnum1); //注意：信号灯编号从0开始|操作了信号灯1设置他的资源有0个
#endif
    struct sembuf sembufdata[10];

    sembufdata[0].sem_num = 0; 
    sembufdata[0].sem_op = 1; //P操作
    sembufdata[0].sem_flg = 0; //阻塞

    semop(semid,sembufdata,1);  //上面的参数使用的是阻塞方式
    // printf("失败\n");


    return 0;
}

/**************************************
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
函数名:int semctl(int semid, int semnum, int cmd, ...);
功能:信号灯初始化
参数:
	semid:要操作的信号灯集id
	semnum:要操作的集合中的信号灯编号（注意：信号灯编号从0开始）
	cmd:执行的操作命令字
		IPC_STAT：从关联的内核数据结构中复制信息将semid放入arg.buf所指向的semid_ds结构中					 semnum被忽略
		IPC_SET:写入semid_ds结构的一些成员的值,semnum被忽略
		IPC_RMID:立即删除信号量集，唤醒所有进程,semnum被忽略
		IPC_INFO:返回有关系统范围信号量限制和的信息,结构的类型是seminfo
		GETNCNT:返回semncnt的semncnt值
		GETPID:返回sempid值
		GETVAL:返回semval的值
		GETZCNT:返回semzcnt的semzcnt值
	...:取决于命令字是一个共用体类型()	
返回值:
	成功:系统调用根据cmd返回一个非负值
		GETNCNT:semncnt.
		GETPID:sempid.
		GETVAL:semval.
		GETZCNT:semzcnt.
	失败:将返回-1，并返回表示错误的errno
附加说明:信号灯只能初始化一次需要用到IPC_EXCL标志位
    	所以：创建信号灯的负责初始化
***************************************/