#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"
#include "../id/id.h"

typedef struct Node{
    SID *s_id;
    void *value;
    _Bool if_malloc;
    _Bool if_sid;
    unsigned int type;
    struct Node *next;
    struct Node *last;
} Node;


typedef struct List{
    SID *s_id;
    Node *head;
    Node *tail;
    unsigned long long length;
} List;

int safeModeForNode(int ifon);
int releaseSingleListForsafeModeForNode(List *p_list);
int releaseSingleNodeForsafeModeForNode(List *p_list);
int releaseAllForNode(void);

List *initList(void);
Node *initNode(void);

int initMallocValueForNode(Node *,unsigned int,void *);

int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);

int exchangeLocation(Node *p_node,Node *t_node);

Node *copyNode(Node *);

int removeById(List *p_list, const SID *s_id);
int removeByNode(List *p_list, Node *p_node);
int popFromHead(List *p_list);
int popFromTail(List *p_list);

unsigned long long len(List *p_list);

Node *findByIdForNode(List *p_list, const SID *s_id);
Node *findByValue(List *p_list, unsigned int type, const void *value);
List *mply_findByValue(List *p_list, unsigned int type, const void *value);

int releaseList(List *p_list);
int releaseListForSingle(List *p_list);
int releaseNode(Node *p_node);
int releaseOnlyNode(Node *p_node);

int isListEmpty(List *p_list);
List *copyList(List *p_list);

static int if_safeModeForNode;
static List *node_list;
static List *list_list;

#endif
