#include <stdio.h>
/******************************/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
/******************************/
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
/*
 * stdin(0),    //行缓存
 * stdout(1),   //行缓存    \n 结束
 * stderr(2),   //无缓存区
 */
char buf[] = "#include <stdio.h> \n \
FILE *fopen( const char *fname, const char *mode );\
fopen()函数打开由fname(文件名)指定的文件, 并返回一个关联该文件的流.如果发生错误, fopen()返回NULL. mode(方式)是用于决定文件的用途(例如 用于输入,输出,等等)\n \
\" r \" 打开一个用于读取的文本文件\n \
\" w \" 创建一个用于写入的文本文件\n \
\" a \" 附加到一个文本文件\n \
\" rb \" 打开一个用于读取的二进制文件\n \
\" wb \" 创建一个用于写入的二进制文件\n \
\" ab \" 附加到一个二进制文件\n \
\" r + \" 打开一个用于读/写的文本文件\n \
\" w + \" 创建一个用于读/写的文本文件（清空写）\n \
\" a + \" 打开一个用于读/写的文本文件(追加写)\n \
\" rb + \" 打开一个用于读/写的二进制文件\n \
\" wb + \" 创建一个用于读/写的二进制文件\n \
\" ab + \" 打开一个用于读/写的二进制文件\n ";
char buf3[] = "函数名：off_t lseek(int fd, off_t offset, int whence) \n\
             * 功能：设置文件描述符的读写位置\n\
             * 参数：\n\
             *      fd：文件描述法\n \
             *      offset：偏移量\n \
             *      whence：位置\n \
             *          SEEK_SET：开始位置\n \
             *          SEEK_CUR：当前位置\n \
             *          SEEK_END：末尾位置";
int main(int argc, char *argv[])
{
    write(1, "吃了没\n", sizeof("吃了没\n")); //向标准输出流输写入   也就是向屏幕输出
    FILE *fp1 = fopen("test.txt", "w+");      //打开文件  ---  FILE 里面拥有文件描述符

    //int filfprintfeno(FILE *stream);
    int fd1 = fileno(fp1); //转换成文件描述符
    printf("文件描述符号:%d\n", fd1);
    char buf2[] = "[fprintf%s格式 文件描述符：]";
    fprintf(fp1, "%s %d", buf2, fd1); //带缓存区的，遇到\n才会输出
    fflush(fp1);                      //清空缓存区，如果没有这一行就会先输出write的buf到文件中
    write(fd1, buf, sizeof(buf) - 1); //数组的\n丢弃 为 sizeof()-1
    char buffer[2048] = {0};
    lseek(fd1, 0, SEEK_SET); //此时文件有偏移，需要用lseek进行调整位置
    while (fgets(buffer, sizeof(buffer), fp1))
    {
        printf("%s", buffer);
    }
    fclose(fp1);                                               //fd1也跟着关闭了
    int fd2 = open("./test.txt", O_CREAT | O_RDWR | O_APPEND); //读写权限，没有文件就创建，O_APPEND追加写
    write(fd2, buf3, sizeof(buf3) - 1);
    return 0;
}