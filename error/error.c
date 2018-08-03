#include "error.h"

int initErrorSystem(void) {
	error_list = initList();
	notice_list = initList();
	if_error = 1;
	return 1;
}

int setLogDirectory(const char *path) {
	logfile.id = getId();
	unsigned long memory_space = strlen(path) + 256;
	char *file_path = (char *)malloc(sizeof(char)*memory_space);

	strcat(file_path, path);
	strcat(file_path, "log");
	sprintf(file_path, "%lu", logfile.id);

	if ((logfile.fp = fopen(file_path, "w")) == NULL) {
		printf("Cannot set logfile!");
		return 0;
	}
	logfile.if_enable = 1;

	free(file_path);
	return 1;
}

int closeLogDirectory(void) {
	Node *p = error_list->head;
		while (p != NULL) {
			saveError(p->value);
			p = p->next;
		}

	p = notice_list->head;
	while (p != NULL) {
		saveNotice(p->value);
		p = p->next;
	}

	releaseList(error_list);
	releaseList(notice_list);
	if_error = 0;
	fclose(logfile.fp);
	logfile.if_enable = 0;
    return 0;
}

int loadFromFile(FILE *fp,char* number) {
	
	return 1;
}

int pushInfo(Info *p_info, const char *head, const char *body) {
	p_info->head = (char *)malloc(sizeof(char) * strlen(head));
	p_info->body = (char *)malloc(sizeof(char) * strlen(body));
	strcpy(p_info->head, head);
	strcpy(p_info->body, body);
    return 0;
}

int pushError(unsigned int type, int pri, Info *p_info) {
	Error error;
	error.type = type;
	error.priority = pri;
	error.p_info = p_info;
	error.time = time(NULL);
    return 0;
}

int pushNotice(unsigned int type, Info *p_info) {
	Notice notice;
	notice.type = type;
	notice.p_info = p_info;
	notice.time = time(NULL);
    return 0;
}

static int saveError(Error *p_error) {
	fprintf(logfile.fp,
		"--------------------\n\
		ERROR\n\
		Type : %ud\n\
		Priority : %d\n\
		Time : %s\n\
		Info : \n\
		%s\n\
		%s\n\
		---------------------\n",
		p_error->type, p_error->priority, ctime( &(p_error->time) ), p_error->p_info->head, p_error->p_info->body);
    return 0;
}
static int saveNotice(Notice *p_notice) {
	fprintf(logfile.fp,
		"--------------------\n\
		NOTICE\n\
		Type : %ud\n\
		Time : %s\n\
		Info : \n\
		%s\n\
		%s\n\
		----------------------\n",
		p_notice->type, ctime( &(p_notice->time) ), p_notice->p_info->head, p_notice->p_info->body);
    return 0;
}
