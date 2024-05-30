#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

struct Student
{
    char name[20];
    int age;
    char sex[10];
    int height;
};
typedef struct Student Student_t;

/**** 数据列表 ****/
struct shm_Students
{
    Student_t stu[10];
    int size;
    int size_max;
};
typedef struct shm_Students shm_Students_t;

void Write_Student(shm_Students_t *shm_Students);
void for_each_Students(shm_Students_t *shm_Students);
int main()
{
    /*** 0.通过ftok()获取Key值 *****/
    key_t key = ftok(".", 'W');
    if (key == -1)
    {
        printf("获取键值失败\n");
        return -1;
    }

    /*** 通过shmget()创建共享内存 ****/
    int shmid = shmget(key, sizeof(shm_Students_t) + 20, IPC_CREAT | 0666);
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
    shm_Students_t *shm_Students = shmat(shmid, NULL, 0);
#if Write
    shm_Students->size_max = 10;
    shm_Students->size = 0;
    while(1)
    {
        Write_Student(shm_Students);
    }
#endif

#if Read
    while(1)
    {
        for_each_Students(shm_Students);
        sleep(1);
    }
#endif

}

void Write_Student(shm_Students_t *shm_Students)
{
    printf("请输入姓名:");
    scanf("%s",shm_Students->stu[shm_Students->size].name);
    printf("请输入年龄:");
    scanf("%d",&shm_Students->stu[shm_Students->size].age);
    printf("请输入性别:");
    scanf("%s",shm_Students->stu[shm_Students->size].sex);
    printf("请输入身高:");
    scanf("%d",&shm_Students->stu[shm_Students->size].height);
    shm_Students->size++;   //成功录入
}

void Print_Student(Student_t *stu)
{
    
    printf("%10s\t%03d\t%6s\t%03d\n",stu->name,stu->age,stu->sex,stu->height);
}

void for_each_Students(shm_Students_t *shm_Students)
{
    printf("\n\n    姓名\t年龄\t 性别\t身高\n");
    for(int i = 0; i < shm_Students->size;i++)
    {
        Print_Student(&(shm_Students->stu[i]));
    }
}

