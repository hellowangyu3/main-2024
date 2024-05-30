#ifndef __mysqlite3_h__
#define __mysqlite3_h__

#include <sqlite3.h>
#include "student.h"

#define table_student "student"
#define dabase_name "student.db"

//插入
int SQLITE3_insert(sqlite3 *dp, Student_t stu);
int SQLITE3_Delete_Id(sqlite3 *dp);
int SQLITE3_Update(sqlite3 *dp);
int SQLITE3_Find(sqlite3 *dp);
int SQLITE3_Sort(sqlite3 *dp);
#endif
