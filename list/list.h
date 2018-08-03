#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"
#include "../id/id.h"

typedef struct Node{
    SID *s_id;//唯一标识符
    void *value;
    _Bool if_malloc;//记录是否已经初始化值
    _Bool if_sid;
    unsigned int type;//记录值的类型
    struct Node *next;
    struct Node *last;
} Node;


typedef struct List{
    SID *s_id;//唯一标识符
    Node *head;
    Node *tail;
    unsigned long long length;//链表长度
} List;

int safeModeForNode(int ifon);//安全模式确保显式声明过的内存都会被释放
int releaseSingleListForsafeModeForNode(List *p_list);//释放list_list
int releaseSingleNodeForsafeModeForNode(List *p_list);//释放node_list
int releaseAllForNode(void);//安全模式最后调用的函数

List *initList(void);
Node *initNode(void);

int initMallocValueForNode(Node *,unsigned int,void *);//赋予已分配内存的值，并标明类型

/*插入函数*/
int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);

/*交换函数*/
int exchangeLocation(Node *p_node,Node *t_node);

/*复制函数*/
Node *copyNode(Node *);

/*移除函数*/
int removeById(List *p_list, const SID *s_id);
int removeByNode(List *p_list, Node *p_node);
int popFromHead(List *p_list);
int popFromTail(List *p_list);

unsigned long long len(List *p_list);//查看链表的长度

Node *findByIdForNode(List *p_list, const SID *s_id);//通过id查找目标链表中的匹配节点
Node *findByValue(List *p_list, unsigned int type, const void *value);//通过值来查找目标链表中的匹配节点
List *mply_findByValue(List *p_list, unsigned int type, const void *value);//寻找多个值匹配的节点

int releaseList(List *p_list);//释放List并可选择是否释放中所有的其中的Node
int releaseListForSingle(List *p_list);//单独释放List
int releaseNode(Node *p_node);//释放Node
int releaseOnlyNode(Node *p_node);//释放Node

int isListEmpty(List *p_list);//判断List是否为空
List *copyList(List *p_list);//复制链表

/*有关安全模式的变量*/
static int if_safeModeForNode;
static List *node_list; //储存声明过的节点.
static List *list_list; //储存声明过的链表.

#endif