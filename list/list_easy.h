#include "list.h"

#ifndef LIST_EASY_H
#define LIST_EASY_H

Node *new_nodeWithInt(int);
Node *new_nodeWithFloat(int);
Node *new_nodeWithString(int);
Node *new_nodeWithPointer(void *);
Node *find_nodeByInt(int);
Node *find_nodesByInt(int);
int list_through(List *p_list,void *p_func(void *));//Go through the list.Call p_func every time.

#endif
