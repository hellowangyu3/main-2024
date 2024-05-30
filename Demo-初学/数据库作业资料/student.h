#ifndef __student_h__
#define __student_h__

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long u64;
/**** 学生结构体 ****/
struct Student
{
                        u64 Id;
					    char Pass[20];
					    char Name[20];
					    u32 Age;
					    u32 ClassNum;
					    u64 PhoneNumber;
					    u32 Math;
					    u32 Eglish;
					    u32 Sum;
};

typedef struct Student Student_t;

/**** 学生基本操作 ****/
Student_t Student_entering();   //录入

void Student_Print(Student_t stu);  //打印

#endif
