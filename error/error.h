#include "../list/list_expand.h"
#include <string.h>
#include <time.h>

#ifndef ERROR_H
#define ERROR_H

#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1

typedef struct Info{
	char *head;
	char *body;
}Info;

typedef struct Error{
	unsigned int type;
	int priority;
	Info *p_info;
	time_t time;
}Error;

typedef struct Notice{
	unsigned int type;
	Info *p_info;
	time_t time;
}Notice;

typedef struct Log{
	FILE *fp;
	int if_enable;
	unsigned long int id;
}Log;

Log logfile;
List *error_list = NULL;
List *notice_list = NULL;
int if_error = 0;

int initErrorSystem(void);

int setLogDirectory(const char *path);
int closeLogDirectory(void);
int loadFromFile(FILE *fp,char* number);

int pushInfo(Info *p_info, const char *head,const char *body);
int pushError(unsigned int type, int pri, Info *p_info);
int pushNotice(unsigned int type, Info *p_info);

//为保证处理效果，不允许外调下列函数
static int saveError(Error *p_error);
static int saveNotice(Notice *p_notice);

#endif