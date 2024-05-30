/*********** 消息队列 ************
 * 1.创建/打开消息队列
 * 2.发送消息/接收消息
 * 3.删除消息队列
 *******************************/

// int msgsnd(int msqid, const void *msgp, size_t msgsz, int msgflg);
// ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp,int msgflg);

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

struct Student
{
    long type;  //消息队列固定的，所以他必须有
    char name[20];
    int age;
    
};

typedef struct Student Student_t;
#define TypeA 100
#define TypeB 200
#define Len sizeof(Student_t)-sizeof(long)
//发送和接收的时候不需要计算long类型的大小，只需要传入数据的大小

#if WriteA
/***** 发送主程序 ******/
int main()
{
    key_t key = ftok(".", 'A');

    /*** 1.创建/打开消息队列 ***/
    int msgid = msgget(key, IPC_CREAT | 0666);

    /*** 2.发送或者接收 ****/
    Student_t stu;
    stu.type = TypeA;
    strcpy(stu.name,"张三");
    stu.age = 20;

    msgsnd(msgid,&stu,Len,0);
    return 0;
}
#endif

#if WriteB
/***** 发送主程序 ******/
int main()
{
    key_t key = ftok(".", 'A');

    /*** 1.创建/打开消息队列 ***/
    int msgid = msgget(key, IPC_CREAT | 0666);

    /*** 2.发送或者接收 ****/
    Student_t stu;
    stu.type = TypeB;
    strcpy(stu.name,"李四");
    stu.age = 50;

    msgsnd(msgid,&stu,Len,0);
    return 0;
}
#endif

#if ReadA
/**** 接收主程序 *****/
int main()
{
    key_t key = ftok(".", 'A');

    /*** 1.创建/打开消息队列 ***/
    int msgid = msgget(key, IPC_CREAT | 0666);

    /*** 2.发送或者接收 ****/
    Student_t stu;

    msgrcv(msgid,&stu,Len,TypeA,0);
    printf("姓名：%s \t年龄:%d\n",stu.name,stu.age);
    return 0;
}
#endif

#if ReadB
/**** 接收主程序 *****/
int main()
{
    key_t key = ftok(".", 'A');

    /*** 1.创建/打开消息队列 ***/
    int msgid = msgget(key, IPC_CREAT | 0666);

    /*** 2.发送或者接收 ****/
    Student_t stu;

    msgrcv(msgid,&stu,Len,TypeB,0);
    printf("姓名：%s \t年龄:%d\n",stu.name,stu.age);
    return 0;
}
#endif

#if Remove
/**** 接收主程序 *****/
int main()
{
    key_t key = ftok(".", 'A');

    /*** 1.创建/打开消息队列 ***/
    int msgid = msgget(key, IPC_CREAT | 0666);

    /*** 2.删除消息队列 ****/
    //int msgctl(int msqid, int cmd, struct msqid_ds *buf);
    msgctl(msgid,IPC_RMID,NULL);
    return 0;
}
#endif