#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H

#include "list.h"

#define __RETURN(argc, args...) newReturn(1, -1, argc , args)
#define __CRETURN__ newCReturn()
#define __SEND_ARG(argc, args...) newReturn(0, -1, argc , args)
#define __CALLBACK_STATE(name) List *_do##name(unsigned int, void *, List *)
#define __CALLBACK_DEFINE(name) List *_do##name(unsigned int type, void *value, List *expand_resources)
#define __VALUE(c_type) (c_type)value
#define __ARGS(x, type) *((type *) lidxp(expand_resources, x));
#define __ARGS_P(x, type) (type *) lidxp(expand_resources, x);
#define __CALLBACK_CALL(name) _do##name
#define __LIST_LEN getInfoForListThrough(expand_resources,0)
#define __NOW_INDEX getInfoForListThrough(expand_resources,1)
#define __RTN_ARGS_P(list,x,type) (type *) lidxp(list, x);
#define __RTN_ARGS(list,x,type) *((type *) lidxp(list, x));

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
int updateValueWithULLIntForNode(Node *, unsigned long long);
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
void printListForCustom(List *p_list,void (*func)(void *value));
void printNode(Node *p_node);

__CALLBACK_STATE(printListForCustom);

List *listThrough(List *p_list, List *(*p_func)(unsigned int type, void *value, List *), List *expand_resources);
List *newReturn(int if_status ,int status, char *argc, ...);
List *newCReturn(void);
unsigned long long getInfoForListThrough(List *expand_resources, int type);
unsigned long long calListMemory(List *);

#endif
