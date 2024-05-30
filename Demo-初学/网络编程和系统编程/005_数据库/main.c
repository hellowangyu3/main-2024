
/***************************************************
#include <sqlite3.h>
函数名:int sqlite3_open(char *path,sqlite3 **db);
功能:打开/创建sqlite数据库
参数:
    path:数据库文件路径
    db：指向sqlite句柄的指针
返回值:
	成功:0
    失败：错误码
**************************************************/

/***************************************************
#include <sqlite3.h>
函数名:int sqlite3_close(sqlite3 *db);
功能:关闭sqlite数据库
参数:
	db:sqlite句柄
返回值:
	成功:0
	失败:错误码
**************************************************/

/***************************************************
功能:执行SQL操作
函数名: int sqlite3_exec(
        sqlite3 *db,                                     数据库句柄 
        const char *sql,                                 SQL语句 
        int (*callback)(void *, int, char **, char **),  回调函数,可以填写NULL 
        void *,                                          callback的第一个参数 
        char **errmsg                                    错误信息 
    );
返回值:
	成功:0
	失败:返回错误码
**************************************************/
#include <sqlite3.h> //编译的时候需要链接到sqlite3的库中
#include <stdio.h>

#define Sqlite3FIleName "student.db"

#define find_sql "select * from student;"
#define find_name_sql "select * from student where 姓名 = '张三';"

int callback(void *para, int f_fum, char **f_value, char **f_name);
int main()
{
    sqlite3 *ppDb;
    char *errmsg = NULL; //错误码
    //1.打开/创建 数据库
    if (sqlite3_open(Sqlite3FIleName, &ppDb) != 0)
    {
        perror("数据库打开失败\n");
        return -1;
    }

    //2.操作数据库sqlite3_exec
    //回调函数:int callback(void *para, int f_fum, char**f_value, char **f_name)
    if (sqlite3_exec(ppDb, find_sql, callback, NULL, &errmsg) != 0)
    {
        printf("%s\n", errmsg);
        printf("操作失败\n");
    }

    printf("查找姓名:\n");
    if (sqlite3_exec(ppDb, find_name_sql, callback, NULL, &errmsg) != 0)
    {
        printf("%s\n", errmsg);
        printf("操作失败\n");
    }

    return 0;
}
/***************************************************
功能：没找到一条记录自动执行回调函数
参数:
	para:传递给回调函数的参数
    f_num:记录中包含的字段数目
    f_value:包含每个字段值的指针数组
    f_name:每包含每个字段名称的指针数组
返回值:
	成功:0
    失败:-1
**************************************************/
int callback(void *para, int f_fum, char **f_value, char **f_name)
{
    for (int i = 0; i < f_fum; i += 3)
    {
        printf("%10s\t%10s\t%10s\n", f_value[i], f_value[i + 1], f_value[i + 2]);
    }
    return 0;
}
