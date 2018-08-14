#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H

#include "list.h"

Node *nodeWithInt(int);
Node *nodeWithUInt(unsigned int);
Node *nodeWithDouble(double);
Node *nodeWithString(const char *);
Node *nodeWithPointer(const void *);

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

Node *findByIndexForNode(List *, unsigned long long);
Node *findByIntForNode(List *, int);
Node *findByDoubleForNode(List *, double);
Node *findByStringForNode(List *, char *);
Node *findByPointerForNode(List *, void *);

List *mply_findByIntForNode(List*, int);
List *mply_findByDoubleForNode(List*, double);
List *mply_findByStringForNode(List*, char *);
List *mply_findByPointerForNode(List*, void *);

void printListInfo(List *p_list,int priority);
void printNodeInfo(Node *p_node,int priority);
void printList(List *);
void printNode(Node *p_node);

int getByIntForNode(Node *);
unsigned int getByUIntForNode(Node *);
double getByDoubleForNode(Node *);
char *getByStringForNode(Node *);
void *getByPointerForNode(Node *);
unsigned long long getIndexForNode(List *p_list,Node *p_node);
List *listThrough(List *p_list, List *(*p_func)(unsigned int type, void *value, List *), List *expand_resources);
unsigned long long calListMemory(List *);

#endif
