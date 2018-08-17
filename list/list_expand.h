#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H

#include "list.h"

#define RETURN(argc, args...) newReturn(1, -1, argc , args)
#define C_RETURN newCReturn()
#define SEND_ARG(argc, args...) newReturn(0, -1, argc , args)
#define CALLBACK_STATE(name) List *do_##name(unsigned int, void *, List *)
#define CALLBACK_DEFINE(name) List *do_##name(unsigned int type, void *value, List *args)
#define VALUE(c_type) (c_type)value
#define ARGS(x, type)\
if(#type == "int") lidxi(args, x);\
else if if(#type == "double") lidxd(args, x);\
else if(#type == "string") lidxs(args, x);\
else lidxi(args, x);
#define CALLBACK_CALL(name) do_##name

Node *nodeWithInt(int, _Bool if_sid);
Node *nodeWithUInt(unsigned int, _Bool if_sid);
Node *nodeWithULLInt(unsigned long long, _Bool if_sid);
Node *nodeWithDouble(double, _Bool if_sid);
Node *nodeWithString(const char *, _Bool if_sid);
Node *nodeWithPointer(const void *, _Bool if_sid);

s_Node *s_nodeWithInt(int);
s_Node *s_nodeWithUInt(unsigned int);
s_Node *s_nodeWithDouble(double);
s_Node *s_nodeWithString(const char *);
s_Node *s_nodeWithPointer(const void *);

Node *nodeWithComplex(void);
int addValueForComplex(Node *, int type, void *value);
int addIntForComplex(Node *, int);
int addDoubleForComplex(Node *, double);
int addStringForComplex(Node *, char *);
int addPointerForComplex(Node *, void *);

int updateValueWithIntForNode(Node *,int);
int updateValueWithDoubleForNode(Node *,double);
int updateValueWithStringForNode(Node *,char *);
int updateValueWithPointerForNode(Node *,void *);

List *mply_findByIntForNode(List*, int);
List *mply_findByDoubleForNode(List*, double);
List *mply_findByStringForNode(List*, char *);
List *mply_findByPointerForNode(List*, void *);

void printListInfo(List *p_list,int priority);
void printNodeInfo(Node *p_node,int priority);
void printList(List *);
void printNode(Node *p_node);

List *listThrough(List *p_list, List *(*p_func)(unsigned int type, void *value, List *), List *expand_resources);
List *newReturn(int if_status ,int status, char *argc, ...);
List *newCReturn(void);
unsigned long long calListMemory(List *);

#endif
