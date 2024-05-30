#ifndef __fcntl_lock_h__
#define __fcntl_lock_h__
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
/**** 锁的操作 ***/
int lock_reg(int fd, int cmd, short lock_type, short lock_whence, off_t lock_start, off_t lock_len);  

/**** 非阻塞上锁 ****/
int reg_lock(int fd);

/**** 非阻塞解锁 ****/
int reg_unlock(int fd);

/**** 阻塞上锁 *****/
int reg_lockw(int fd);

/**** 阻塞解锁 *****/
int reg_unlockw(int fd);

#endif