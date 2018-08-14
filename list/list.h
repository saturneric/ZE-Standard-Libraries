#ifndef LIST_H
#define LIST_H
#include "../type/type.h"
#include "../id/id.h"

int safeModeForNode(int ifon);
int releaseSingleListForsafeModeForNode(List *p_list);
int releaseSingleNodeForsafeModeForNode(List *p_list);
int releaseAllForNode(void);

List *initList(_Bool if_sid);
Node *initNode(_Bool if_sid);
s_Node *s_initNode(void);

int initMallocValueForNode(Node *,unsigned int,const void *);

int insertInHead(List *p_list, Node *p_node);
int insertInTail(List *p_list, Node *p_node);
int s_insertInHead(List *p_list, s_Node *s_p_node);
int s_insertInTail(List *p_list, s_Node *s_p_node);

int replaceNode(List *p_list, Node *pt_node, Node *p_node);

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
int s_releaseList(List *p_list);

int releaseListForCustom(List *p_list, int (*func)(void *));
int s_releaseListForCustom(List *p_list, int (*func)(void *));

int releaseListForSingle(List *p_list);

int releaseNode(Node *p_node);
int s_releaseNode(s_Node *s_p_node);

int releaseNodeForCustom(Node *p_node, int (*func)(void *));
int s_releaseNodeForCustom(s_Node *s_p_node, int (*func)(void *));

int releaseOnlyNode(Node *p_node);

int isListEmpty(List *p_list);
List *copyList(List *p_list);

int pushInfo(Info *p_info, const char *head,const char *body);
Error *pushError(unsigned int type, int pri, Info *p_info);
Notice *pushNotice(unsigned int type, Info *p_info);

Info *initInfo(const char *head, const char *body);
Error *createError(Info *info,unsigned int type,int pri);
Notice *createWarning(Info *info, unsigned int type, int pri);
int showError(Error *);
int showWarning(Notice *);

int enableListQuick(List *p_list);
int sortListById(List *p_list);

static int if_safeModeForNode;
static List *node_list;
static List *list_list;

#endif
