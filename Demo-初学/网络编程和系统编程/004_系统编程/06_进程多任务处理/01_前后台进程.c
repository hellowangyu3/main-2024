#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/*********************************
 * fork()函数作用创建一个子进程  -> 子进程还可以创建子子进程(可以无休止延续下去)
 * 返回值:1.fork返回 >0 的pid(进程号) 现在执行的是父进程
 *       2.fork返回 ==0 的pid(进程号) 现在执行的是子进程
 *       3.fork返回 -1 则父进程创建子进程失败
 * 
 * 注意：父进程结束会将他创建的子进程也结束，除非该子进程脱离了父进程(守护进程)
 * 
 * 问题：fork()的执行顺序是？
 *     答：fork()的父子进程时间片有关,如果父进程还有时间片则执行父进程的代码,如果没有时间片则执行子进程代码
 *         所以他的顺序是随机的。
 * 
 * 问题:fork()函数之后再fork()，进程个数
 *     答：都会执行fork(),所以他的个数会以指数级方式增长。
 * 
 * 问题：父进程运行fork后执行那一段代码，子进程执行那一段代码?
 *     答:父子进程都从 fork()函数的下一句执行
 * 
 * ******************************/
#if 0
int main()
{
    int i = 1;
    fork();
    i = i * 2;
    //2个任务

    fork();
    //4个任务
    i = i * 2;
    fork();

    i = i * 2;
    printf("进程数量:%d\n",i);
    while(1)
    {
        
    }
}
#endif 
#if 1

int main() //CEO
{
    pid_t pid1 = fork(); //创建进程
    if (pid1 == -1)      //创建子进程失败
    {
        printf("招员工失败\n");
    }
    else if (pid1 == 0) //创建子进程成功并执行子进程代码
    {
        printf("成功招聘扫地经理阿姨1个\n");
        pid_t pid1_1 = fork();
        if (pid1_1 == -1)
        {
            printf("扫地经理招扫地员工失败\n");
        }
        else if (pid1_1 == 0)
        {
            while (1) //扫地
            {
                printf("扫地1\n");
                sleep(1);
            }
            exit(0); //结束的是 子进程（扫地）
        }

        pid1_1 = fork();
        if (pid1_1 == -1)
        {
            printf("扫地经理招扫地员工失败\n");
        }
        else if (pid1_1 == 0)
        {
            while (1) //扫地
            {
                printf("扫地2\n");
                sleep(1);
            }
            exit(0); //结束的是 子进程（扫地）
        }

        while(1)
        {
            printf("扫地经理阿姨工作\n");
            sleep(1);
        }
        exit(0); //结束的是 子进程（扫地经理阿姨）
    }

    pid_t pid2 = fork(); //创建进程
    if (pid2 == -1)      //创建子进程失败
    {
        printf("招员工失败\n");
    }
    else if (pid2 == 0) //创建子进程成功并执行子进程代码
    {
        printf("成功招聘保安大哥1个\n");
        // while (1) //保安
        // {
            printf("保安\n");
            sleep(1);
        // }
        // exit(0); //结束的是 子进程（保安）
    }

    while (1)
    {
        printf("CEO\n");
        sleep(1);
    }
    exit(0); //结束的是 父进程（CEO）
}
#endif