#ifndef ERROR_H
#define ERROR_H

#include "../type/type.h"
#include "../list/list_expand.h"

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
