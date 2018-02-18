#include "list.h"

#ifndef LIST_EASY_H
#define LIST_EASY_H

Node *new_nodeWithInt(int);
Node *new_nodeWithDouble(double);
Node *new_nodeWithString(const char *);
Node *new_nodeWithPointer(void *);
Node *find_nodeByIndex(List *, unsigned long long);
int list_through(List *p_list, int (*p_func)(void *, const char *));//Go through the list.Call p_func every time.


Node *new_nodeWithInt(int m_int){
	int *p_int = (int *)malloc(sizeof(int));
	*p_int = m_int;
	Node *p_node = init_node();
	init_value(p_node,"int",(void *)p_int);
	return p_node;
}

Node *new_nodeWithDouble(double m_double){
	double *p_double = (double *)malloc(sizeof(double));
	*p_double = m_double;
	Node *p_node = init_node();
	init_value(p_node,"double",(void *)p_double);
	return p_node;
}

Node *new_nodeWithString(const char *m_string){
	char *p_string = (char *)malloc(sizeof(char)*(strlen(m_string)+1));
	strcpy(p_string,m_string);
	Node *p_node = init_node();
	init_value(p_node,"string",(void *)p_string);
	return p_node;
}

Node *new_nodeWithPointer(void *m_pointer){
	Node *p_node = init_node();
	init_value(p_node,"pointer",(void *)m_pointer);
	return p_node;
}

Node *find_nodeByIndex(List *p_list, unsigned long long m_index){
	Node *p_node = p_list->head;
	for(unsigned long long i= 0; i < m_index; i++){
		p_node = p_node->next;
	}
	return p_node;
}

int list_through(List *p_list, int (*p_func)(void *, const char *)){
	Node *p_node = p_list->head;
	while(p_node != NULL){
		if(p_node->if_setvalue == 1){
			int m_return = (*p_func)(p_node->value, p_node->type);
			if (m_return == -1) break;
			else if (m_return == 1){
				p_node = p_node->last;
				continue;
			}
			else{
				
			}
		}
		p_node = p_node->next;
	}
	return 0;
}
#endif
