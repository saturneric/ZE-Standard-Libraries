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
	Info info;
	time_t time;
}Notice;

typedef struct Log{
	FILE *fp;
	int if_enable;
	unsigned long int id;
	unsigned int type;
}Log;

List *error_list;
List *log_list;



#endif
