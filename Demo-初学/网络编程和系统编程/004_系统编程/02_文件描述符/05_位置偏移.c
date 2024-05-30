/********************************************
 * 需求：将文件里面的王五数据更改
 * *******************************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

struct Student
{
    char name[10];
    int age;
    char sex;
};

typedef struct Student Student_t;

Student_t stu[] = {
    {"张三", 18, 'X'},
    {"李四", 19, 'X'},
    {"王五", 14, 'Y'},
    {"赵六", 12, 'X'},
    {"蕾蕾", 18, 'X'},
};
#define FileName "Student.dat"
void Print_Student(Student_t *stus, int len);
int main()
{
#if 0   //将学生写入文件
    int len = sizeof(stu) / sizeof(stu[0]);
    Print_Student(stu, len);
    int fd = open(FileName, O_RDWR | O_CREAT, 0666);
    for (int i = 0; i < len; i++)
    {
        write(fd, &stu[i], sizeof(Student_t));
    }
    close(fd);
#endif

#if 1   //将文件数据写入内存

    Student_t stus[100] = {0};
    int fd = open(FileName, O_RDWR | O_CREAT, 0666);
    if (fd == -1)
    {
        perror("");
        return -1;
    }

    int len = 0;
    while (read(fd, &stus[len], sizeof(Student_t)) != 0)
    {
        if (strcmp(stus[len].name, "王五") == 0)
        {
            stus[len].age = 50;

            /******************************************************
             * 函数名：off_t lseek(int fd, off_t offset, int whence);
             * 功能：设置文件描述符的读写位置
             * 参数：
             *      fd：文件描述法
             *      offset：偏移量
             *      whence：位置
             *          SEEK_SET：开始位置
             *          SEEK_CUR：当前位置
             *          SEEK_END：末尾位置
             * ****************************************************/
            lseek(fd,-sizeof(Student_t),SEEK_CUR);
            write(fd,&stus[len],sizeof(Student_t));
            return 0;
        }
        len++;
    }

    Print_Student(stus, len);

#endif

#if 0   //空洞文件
    int fd = open("传输空洞文件.txt",O_RDWR|O_CREAT,0666);
    write(fd,"开始",strlen("开始"));
    lseek(fd,100L,SEEK_SET);
    write(fd,"结束",strlen("结束"));
    close(fd);

#endif

    return 0;
}

void Print_Student(Student_t *stus, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("姓名:%s\t年龄:%3d\t性别:%s\n",
               stus[i].name,
               stus[i].age,
               stus[i].sex == 'X' ? "女" : "男");
    }
}