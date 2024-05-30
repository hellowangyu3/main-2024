
/*******************************
 *int stat(const char *pathname, struct stat *buf);     //路径的文件属性,如果有链接文件则直接到绝对路径
 *int fstat(int fd, struct stat *buf);                  //文件描述符指向的文件属性
 *int lstat(const char *pathname, struct stat *buf);    //路径的文件属性,如果有链接文件则指向链接文件
 *功能：获取文件的属性
 *参数:
       pathname:路径文件名
       fd:描述符
       buf:文件属性结构体
 *返回值：
       成功:0
       失败:!0
 * *******************************/
// struct stat       //文件信息结构体
// {
//        dev_t st_dev;         /* 包含文件的设备ID */
//        ino_t st_ino;         /* inode编号 */
//        mode_t st_mode;       /* 权限用户|组|其他的读写执行权限 */
//        nlink_t st_nlink;     /* 硬链接数 */
//        uid_t st_uid;         /* 拥有者用户ID */
//        gid_t st_gid;         /* 组用户ID */
//        dev_t st_rdev;        /* 设备ID(如果是特殊文件) */
//        off_t st_size;        /* 以字节为单位的大小 */
//        blksize_t st_blksize; /* 文件系统I/O的块大小 */
//        blkcnt_t st_blocks;   /* 分配的512B块数 */
// };
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#define FileName "test.txt"
int main(int argv, char *argc[])
{
       struct stat file_stat;

       for (int i = 1; i < argv; i++)
       {
              stat(argc[i], &file_stat);

              // printf("硬链接数:%ld\n", file_stat.st_nlink);
              // printf("文件大小:%ld\n", file_stat.st_size);

              char dir = ' ';
              if (S_ISREG(file_stat.st_mode) > 0){dir = '-';}
              if (S_ISDIR(file_stat.st_mode) > 0){dir = 'd';}
              if (S_ISCHR(file_stat.st_mode) > 0){dir = 'c';}
              if (S_ISBLK(file_stat.st_mode) > 0){dir = 'b';}
              /**********************************************
              * 0000 0000 0010 1111  = 读取标志位   file_stat.st_mode
              * 0000 0000 0000 0001  = 读的标志位
              *&0000 0001   
              * *********************************************/
              char Power[10] = {'-', '-', '-', '-', '-', '-', '-', '-', '-', '\0'};
              //切记 &的优先级 低于 == 的优先级,所以需要加上一个()增加他的优先级
              if ((file_stat.st_mode & S_IRUSR) == S_IRUSR){Power[0] = 'r';}
              if ((file_stat.st_mode & S_IWUSR) == S_IWUSR){Power[1] = 'w';}
              if ((file_stat.st_mode & S_IXUSR) == S_IXUSR){Power[2] = 'x';}
              if ((file_stat.st_mode & S_IRGRP) == S_IRGRP){Power[3] = 'r';}
              if ((file_stat.st_mode & S_IWGRP) == S_IWGRP){Power[4] = 'w';}
              if ((file_stat.st_mode & S_IXGRP) == S_IXGRP){Power[5] = 'x';}
              if ((file_stat.st_mode & S_IROTH) == S_IROTH){Power[6] = 'r';}
              if ((file_stat.st_mode & S_IWOTH) == S_IWOTH){Power[7] = 'w';}
              if ((file_stat.st_mode & S_IXOTH) == S_IXOTH){Power[8] = 'x';}
              printf("%c", dir);
              printf("%s ", Power);
              printf("%ld ", file_stat.st_nlink);
              printf("%ld ", file_stat.st_size);

              /**** 将其转换成时间结构体 *****/
              struct tm *time = localtime(&file_stat.st_mtim.tv_sec);
              printf("%d月 ", time->tm_mon);
              printf("%d日 ", time->tm_mday);

              printf("%02d:%02d ", time->tm_hour, time->tm_min);

              printf(" %s\n", FileName);
       }

       //     S_ISUID     04000   set-user-ID bit
       //     S_ISGID     02000   set-group-ID bit (see below)
       //     S_ISVTX     01000   sticky bit (see below)

       //     S_IRUSR     00400   owner has read permission
       //     S_IWUSR     00200   owner has write permission
       //     S_IXUSR     00100   owner has execute permission

       //     S_IRWXG     00070   group has read, write, and execute permission
       //     S_IRGRP     00040   group has read permission
       //     S_IWGRP     00020   group has write permission
       //     S_IXGRP     00010   group has execute permission

       //     S_IROTH     00004   others have read permission
       //     S_IWOTH     00002   others have write permission
       //     S_IXOTH     00001   others have execute permission

       return 0;
}