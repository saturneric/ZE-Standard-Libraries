#ifndef ERROR_H
#define ERROR_H

#include <type.h>
#include <list/list.h>
#include <error/error.h>

/*
 *错误管理中日志信息的管理及操作的结构
 */
typedef struct Log{
    FILE *fp;//日志文件的指针
    int if_enable;//日志文件是否启用
    unsigned long int id;//日志文件的ID
}Log;

Log logfile;
List *error_list = NULL;
List *notice_list = NULL;
int if_error = 0;

int initErrorSystem(void);

int setLogDirectory(const char *path);
int closeLogDirectory(void);

int loadFromFile(FILE *fp,char* number);

int saveError(Error *p_error);
int saveNotice(Notice *p_notice);

#endif
