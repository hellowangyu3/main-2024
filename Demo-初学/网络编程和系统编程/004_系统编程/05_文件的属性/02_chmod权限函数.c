#include <stdio.h>
#include <sys/stat.h>

// int chmod(const char *pathname, mode_t mode);
// int fchmod(int fd, mode_t mode);

#define FileName "test.txt"
int main()
{
    chmod(FileName,0777);  

}