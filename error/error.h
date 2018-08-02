#include "../list/list_easy.h"
#include <time.h>

#ifndef ERROR_H
#define ERROR_H

#define HIGH 0x3
#define STANDARD 0x2
#define LOW 0x1 

typedef struct Info{
	char *head;
	char *body;
	char *tail;
}Info;

typedef struct Error{
	unsigned int type;
	int pri;
	Info info;
	time_t time;
}Error;

typedef struct Notice{
	unsigned int type;
	Info *info;
	time_t time;
}Notice;

typedef struct Log{
	FILE *fp;
	int if_enable;
	unsigned long int id;
	unsigned int type;
}Log;

List *error_list = NULL;
List *log_list = NULL;
int if_error = 0;

int error_init(int if_enable);
int set_logDirectory(char *);
int push_error(unsigned int type, int pri, Info *p_info);
int push_notice(unsigned int type, Info *p_info);
int save_error(Error *p_error);
int save_notice(Notice *p_notice);
Info *init_Info(char *m_info);

int error_init(int if_enable){
	if(if_enable == 1){
		error_list = init_list();
		log_list = init_list();
		if_error = 1;
		return 1;
	}
	return 0;
}

#endif
