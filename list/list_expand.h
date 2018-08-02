#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H
#include "list.c"

Node *nodeWithInt(int);//快速初始化一个单一值节点并赋值
Node *nodeWithDouble(double);//快速初始化一个节单一值点并赋值
Node *nodeWithString(const char *);//快速初始化一个单一值节点并赋值
Node *nodeWithPointer(void *);//快速初始化一个单一值节点并赋值

Node *nodeWithComplex(void);//快速初始化一个复合值节点并赋值
int addValueForComplex(Node *, int type, void *value);//为复合节点添加值
int addIntForComplex(Node *, int);//为复合节点添加一个特定类型的值
int addDoubleForComplex(Node *, double);//为复合节点添加一个特定类型的值
int addStringForComplex(Node *, char *);//为复合节点添加一个特定类型的值
int addPointerForComplex(Node *, void *);//为复合节点添加一个特定类型的值

Node *findByIndexForNode(List *, unsigned long long);//根据位置查找一个节点
Node *findByIntForNode(List *, int);//依照特定类型查找一个节点
Node *findByDoubleForNode(List *, double);//依照特定类型查找一个节点
Node *findByStringForNode(List *, char *);//依照特定类型查找一个节点
Node *findByPointerForNode(List *, void *);//依照特定类型查找一个节点

List *m_findByIntForNode(List*, int);//根据位置查找所有匹配的节点
List *m_findByDoubleForNode(List*, double);//根据位置查找所有匹配的节点
List *m_findByStringForNode(List*, char *);//根据位置查找所有匹配的节点
List *m_findByPointerForNode(List*, void *);//根据位置查找所有匹配的节点

void printListInfo(List *p_list,int priority);//打印列表的详细信息
void printNodeInfo(Node *p_node,int priority);//打印节点的详细信息
void printList(List *);//打印列表
void printNode(Node *p_node);//打印节点

int getByIntForNode(Node *);//直接得到节点的值
double getByDoubleForNode(Node *);//直接得到节点的值
char *getByStringForNode(Node *);//直接得到节点的值
void *getByPointerForNode(Node *);//直接得到节点的值
unsigned long long getIndexByNode(List *p_list,Node *p_node);
int listThrough(List *p_list, int (*p_func)(unsigned int type, void *value));//遍历链表并不断调用目标函数。目标函数将接受节点储存值的指针及其类型。

unsigned long long calListMemory(List *);

#endif
