#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifndef LIST_H 
#define LIST_H

typedef struct Node{
	unsigned long long id;
	void *value;
	int if_setvalue;
	const char *type;
	struct Node *next;
	struct Node *last;
}Node;


typedef struct List{
	Node *head;
	Node *tail;
	unsigned long long length;
}List;

int safeMode(int ifon);//Safe mode is used to make sure that all malloced will be freed.
int releaseAll(void);
List *init_list(void);
Node *init_node(void);
int init_value(Node *,const char *,void *);
void init_rand(void);

unsigned long long getId(void);

int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);

int removeById(List *p_list, unsigned long id);
int removeByNode(List *p_list, Node *p_node);

int popFromHead(List *p_list);
int popFromTail(List *p_list);

unsigned long long len(List *p_list);

Node *findById(List *p_list, const unsigned long long id);
Node *findByValue(List *p_list, const char *type, const void *value);
List *mply_findByValue(List *p_list, const char *type, const void *value);

int releaseList(List *p_list);
int releaseNode(Node *p_node);

int isListEmpty(List *p_list);

/*Something about safe mode*/
int if_safeMode = 0;
List *node_list = NULL; //Store nodes which haven't been freed.
List *list_list = NULL; //Store lists which haven't been freed. 

int safeMode(int ifon){
	if(ifon == 1){
		if (node_list == NULL && list_list == NULL){
			node_list = (List *)malloc(sizeof(List));
			list_list = (List *)malloc(sizeof(List));
			if_safeMode = 1;
		}
		else{
			return -1;
		}
	}
	
	return ifon;
}

int releaseAll(void){
	if(if_safeMode == 1){
		if_safeMode = 0;
		releaseList(node_list);
		releaseList(list_list);
	}
	return 0;
}

Node *init_node(void){
	Node *p_node = (Node *) malloc(sizeof(Node));
	p_node->id = getId();
	p_node->if_setvalue = 0;
	if(if_safeMode) insertInTail(node_list,p_node);
	return p_node;
}

List *init_list(void){
	List *p_list = (List *) malloc(sizeof(List));
	p_list->head = NULL;
	p_list->tail = NULL;
	if(if_safeMode){
		Node *p_node = init_node();
		init_value(p_node,"pointer",(void *)p_list);
		insertInTail(list_list,p_node);
	}
	return p_list;
}

int init_value(Node *p_node,const char *type,void * p_value){
	p_node->if_setvalue = 1;
	p_node->type = type;
	p_node->value = p_value;
	return 0;
}

void rand_init(void){
	srandom((unsigned)time(NULL));
}

unsigned long long getId(void){
	unsigned long long id = 0;
	id = ((random()%9)+1);
	for(int i = 0; i < 15; i++){
		id *= 10;
		id += random()%10;
	}
	return id;
}

int insertInHead(List *p_list, Node *p_node){
	if( isListEmpty(p_list) ){
		p_list->head = p_node;
		p_list->tail = p_node;
	}
	else{
		p_list->head->last = p_node;
		p_node->last = NULL;
		p_node->next = p_list->head;
		p_list->head = p_node;
	}
	p_list->length += 1;
	return 0;
}

int insertInTail(List *p_list, Node *p_node){
	if( isListEmpty(p_list) ){
		p_list->head = p_node;
		p_list->tail = p_node;
	}
	else{
		p_list->tail->next = p_node;
		p_node->next = NULL;
		p_node->last = p_list->tail;
		p_list->tail = p_node;
	}
	p_list->length += 1;
	return 0;
}

int releaseNode(Node *p_node){
	if(if_safeMode == 1){
		removeByNode(node_list,p_node);
	}
	if(p_node->if_setvalue == 1){
		free(p_node->value);
		p_node->value = NULL;
	}
	p_node->last = NULL;
	p_node->next = NULL;
	free(p_node);
	return 0;
}

int releaseList(List *p_list){
	Node *p_node, *pl_node;
	p_node = p_list->head;
	if(if_safeMode == 1){
		Node *tar_list = findByValue(list_list,"pointer",(void *)p_list);//turn pointer in to int to compare.
		removeByNode(list_list,tar_list);
	}
	while (p_node != NULL){
		pl_node = p_node;
		p_node = p_node->next;
		pl_node->next = NULL;
		pl_node->last = NULL;
		releaseNode(pl_node);
	}
	p_list->head = NULL;
	p_list->tail = NULL;
	p_list->length = 0;
	free(p_list);
	return 0;
}

unsigned long long len(List *p_list){
	return p_list->length;
}

int removeById(List *p_list, unsigned long id){
	Node *tmp = p_list->head;
	if( isListEmpty(p_list) )
		return -1;
	do{	
		if(tmp->id == id) {
			tmp->last->next = tmp->next;
			tmp->next->last = tmp->last;
			//releaseNode(tmp); not necessary
			p_list->length -= 1;
			return 1;//found
		}
		else{
			tmp = tmp->next;
		}
	}while(tmp != NULL);

	return 0;//not find
}

int removeByNode(List *p_list, Node *p_node){
	Node *tmp = p_list->head;
	if( isListEmpty(p_list) )
		return -1;
	do{
		if(tmp == p_node){
			tmp->last->next = tmp->next;
			tmp->next->last = tmp->last;
			//releaseNode(tmp); not necessary
			p_list->length -= 1;
			return 1;//found
		}
		else{
			tmp = tmp->next;
		}	
	}while(tmp != NULL);

	return 0;//not find
}

int popFromHead(List *p_list){
	if( isListEmpty(p_list) )
		return -1;
	else{
		//Node *tmp = p_list->head;
		p_list->head->next->last = NULL;
		p_list->head = p_list->head->next;
		//releaseNode(tmp); not necessary
		p_list->length -= 1;
	}

	if( isListEmpty(p_list) ){
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	return 0;
}

int popFromTail(List *p_list){
	if( isListEmpty(p_list) )
		return -1;
	else{
		//Node *tmp = p_list->tail;
		p_list->tail->last->next = NULL;
		p_list->tail = p_list->tail->last;
		//releaseNode(tmp); not necessary
		p_list->length -= 1;
	}

	if( isListEmpty(p_list) ){
		p_list->head = NULL;
		p_list->tail = NULL;
	}
	return 0;
}

/*The method in this function won't be better than going through the list 
 * node by node.The worst situation happens when the matched node is in 
 * the middle of the list.*/
Node *findById(List *p_list, const unsigned long long id){
	Node *ph_node = p_list->head;
	Node *pt_node = p_list->tail;
	int direction = 0;
	while(ph_node != pt_node){
		if (direction == 0){
			if (ph_node->id == id){
				return ph_node;
			}
			else{
				ph_node = ph_node->next;
			}
			direction = 1;
		}
		else{
			if (pt_node->id == id){
				return pt_node;
			}
			else{
				pt_node = pt_node->last;
			}
		}
	}
	return NULL;
}

Node *findByValue(List *p_list, const char *type, const void *value){
	Node *p_node = p_list->head;
	while(p_node != NULL){
		if(strcmp(p_node->type,type)) continue;//continue when type is not the same.
		if(!strcmp(type,"int")){
			if(*((int *)p_node->value) == *((int *)value)){
				return p_node;
			}
		}
		else if(!strcmp(type,"double")){
			if(*((double *)p_node->value) == *((double *)value)){
				return p_node;
			}
		}
		else if(!strcmp	(type,"string")){
			if(!strcmp((char *)p_node->value,(char *)value))
			{
				return p_node;
			}
		}
		else if(!strcmp(type,"pointer")){
			if(p_node->value == value){
				return p_node;
			}
		}
		
		p_node = p_node->next;
		
	}
	return NULL;
}

List *mply_findByValue(List *p_list, const char *type, const void *value){
	List *f_list = init_list();
	Node *p_node = p_list->head;
	while(p_node != NULL){
		if(strcmp(p_node->type,type)) continue;
		if(!strcmp(type,"int")){
			if(*((int *)p_node->value) == *((int *)value)){
				Node *f_node = init_node();
				init_value(f_node,"pointer",(void *)p_node);
				insertInTail(f_list,f_node);
			}
		}
		else if(!strcmp(type,"double")){
			if(*((double *)p_node->value) == *((double *)value)){
				Node *f_node = init_node();
				init_value(f_node,"pointer",(void *)p_node);
				insertInTail(f_list,f_node);
			}
		}
		else if(!strcmp	(type,"string")){
			if(!strcmp((char *)p_node->value,(char *)value))
			{
				Node *f_node = init_node();
				init_value(f_node,"pointer",(void *)p_node);
				insertInTail(f_list,f_node);
			}
		}
		else if(!strcmp(type,"pointer")){
			if(p_node->value == value){
				Node *f_node = init_node();
				init_value(f_node,"pointer",(void *)p_node);
				insertInTail(f_list,f_node);
			}
		}
		
		p_node = p_node->next;
		
	}
	return f_list;
}

int isListEmpty(List *p_list){
	if(p_list->head == NULL || p_list->tail == NULL)// If its head or tail is NULL,it would be thought as empty.
		return 1;				// But we should ensure that both of them are NULL when we
	return 0;					// want to make a list empty.
}

#endif
