#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
/*********  目录操作 ********
 * 1.创建 mkdir
 * 2.删除 rmdir
 * 3.读取 opendir(),readdir(),closedir(),
 * *****************/

int main()
{
    /***** 1.创建 mkdir ****/
    mkdir("测试目录", 0777);

    sleep(1);
    /***** 2.删除 rmdir ****/
    rmdir("测试目录");

    //切换共工作路径 chdir
    chdir("..");    //服务器放置位置:mnt目录 或者 temp目录 或者 / 

    //打印绝对路径 getcwd
    char buf_dir[228] = "";
    char *ptr_dir;
    ptr_dir = getcwd(buf_dir,sizeof(buf_dir)-1);    //用户需要反馈绝对路径需要用到
    printf("ptr_dir = %s\n",ptr_dir);
    printf("buf_dir = %s\n",ptr_dir);

    /***** 3.目录的读取 ****/
    DIR *dir = opendir("."); //3.1 打开目录
    if (dir == NULL)
    {
        printf("没有当前目录\n");
        return -1;
    }
    
    while(1)
    {
        //3.2 读取目录 
        struct dirent *dire = readdir(dir);
        if(dire == NULL)
        {
            break;
        }
        unsigned char type[] = {DT_BLK, DT_CHR, DT_DIR, DT_FIFO, DT_LNK, DT_REG, DT_SOCK};
        char *type_name[] = {"块设备", "字符设备", "目录", "管道", "链接", "普通", "套接字"};
        printf("文件名:%-30s  ", dire->d_name);
        for (int i = 0; i < 7; i++)
        {
            if (dire->d_type == type[i])
            {
                printf("文件类型:%s\n", type_name[i]);
            }
        }
    }

    closedir(dir);  //3.3 关闭目录
}