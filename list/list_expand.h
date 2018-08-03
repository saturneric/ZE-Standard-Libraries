#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H

#include "list.h"

Node *nodeWithInt(int);
Node *nodeWithDouble(double);
Node *nodeWithString(const char *);
Node *nodeWithPointer(void *);

Node *nodeWithComplex(void);
int addValueForComplex(Node *, int type, void *value);
int addIntForComplex(Node *, int);
int addDoubleForComplex(Node *, double);
int addStringForComplex(Node *, char *);
int addPointerForComplex(Node *, void *);

Node *findByIndexForNode(List *, unsigned long long);
Node *findByIntForNode(List *, int);
Node *findByDoubleForNode(List *, double);
Node *findByStringForNode(List *, char *);
Node *findByPointerForNode(List *, void *);

List *m_findByIntForNode(List*, int);
List *m_findByDoubleForNode(List*, double);
List *m_findByStringForNode(List*, char *);
List *m_findByPointerForNode(List*, void *);

void printListInfo(List *p_list,int priority);
void printNodeInfo(Node *p_node,int priority);
void printList(List *);
void printNode(Node *p_node);

int getByIntForNode(Node *);
double getByDoubleForNode(Node *);
char *getByStringForNode(Node *);
void *getByPointerForNode(Node *);
unsigned long long getIndexByNode(List *p_list,Node *p_node);
int listThrough(List *p_list, int (*p_func)(unsigned int type, void *value));
unsigned long long calListMemory(List *);

#endif
