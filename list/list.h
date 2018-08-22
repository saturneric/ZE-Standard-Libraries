#ifndef LIST_H
#define LIST_H
#include "../type/type.h"
#include "../id/id.h"

#define lni(x) nodeWithInt(x,0)
#define lnu(x) nodeWithUInt(x,0)
#define lnull(x) nodeWithULLInt(x,0)
#define lnd(x) nodeWithDouble(x,0)
#define lns(x) nodeWithString(x,0)
#define lnp(x) nodeWithPointer(x,0)

#define lsni(x) nodeWithInt(x,1)
#define lsnd(x) nodeWithDouble(x,1)
#define lsns(x) nodeWithString(x,1)
#define lsnp(x) nodeWithPointer(x,1)

#define lisrti(list, x) insertInTail(list, lni(x));
#define lisrtd(list, x) insertInTail(list, lnd(x));
#define lisrtu(list, x) insertInTail(list, lnu(x));
#define lisrtull(list, x) insertInTail(list, lnull(x));
#define lisrtp(list, x) insertInTail(list, lnp(x));
#define lisrts(list, x) insertInTail(list, lns(x));

#define lisrhi(list, x) insertInHead(list, lni(x));
#define lisrhd(list, x) insertInHead(list, lnd(x));
#define lisrhu(list, x) insertInHead(list, lnu(x));
#define lisrhull(list, x) insertInHead(list, lnull(x));
#define lisrhp(list, x) insertInHead(list, lnp(x));
#define lisrhs(list, x) insertInHead(list, lns(x));

#define lidxp(list, x) getByPointerForNode(findByIndexForNode(list, x))
#define lidxi(list, x) getByIntForNode(findByIndexForNode(list, x))
#define lidxd(list, x) getByDoubleForNode(findByIndexForNode(list, x))
#define lidxs(list, x) getByStringForNode(findByIndexForNode(list, x))

#define lupdull(list,x,value) updateValueWithULLIntForNode(findByIndexForNode(list, x),value)

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
int insertAfterNode(List *p_list, Node *t_node, Node *p_node);
int insertBeforeNode(List *p_list, Node*t_node, Node *p_node);
int s_insertInHead(List *p_list, s_Node *s_p_node);
int s_insertInTail(List *p_list, s_Node *s_p_node);

int replaceNode(List *p_list, Node *pt_node, Node *p_node);
int exchangeNode(List *p_list, Node *f_node, Node *s_node);

Node *copyNode(Node *);

int removeById(List *p_list, SID *s_id);
int removeByNode(List *p_list, Node *p_node);
Node *popFromHead(List *p_list);
Node *popFromTail(List *p_list);

unsigned long long len(List *p_list);

Node *findByIdForNode(List *p_list, SID * s_id);
void *findByIdForCustom(List *p_list, SID *s_id, int func(SID *));
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
int refreshFnNode(List *p_list);
int sortList(List *p_list, unsigned long long begin, unsigned long long end, int(*func)(Node *f_node, Node *s_node));
int sortListForCustom(List *p_list, int(*func)(Node *f_node, Node *s_node));
int indexTransfromer(List *p_list, unsigned long long m_index);
int indexChange(List *p_list, unsigned long long c_index, int move);
Node *getNodeByFnNode(List *p_list, unsigned long long index);
Node *findFnNode(List *p_list, Node *p_node);
void initIdxcList(List *p_list);
void digHole(List *p_list, Node *p_node);
int disableListQuick(List *p_list);

Node *findByIndexForNode(List *, unsigned long long);
Node *findByIntForNode(List *, int);
Node *findByDoubleForNode(List *, double);
Node *findByStringForNode(List *, char *);
Node *findByPointerForNode(List *, void *);

Node *getListTail(List *);
Node *updateNodeByIndex(List *, void *, unsigned long long);

int getByIntForNode(Node *);
unsigned int getByUIntForNode(Node *);
double getByDoubleForNode(Node *);
char *getByStringForNode(Node *);
void *getByPointerForNode(Node *);
unsigned long long getIndexForNode(List *p_list,Node *p_node);

static int if_safeModeForNode;
static List *node_list;
static List *list_list;

#endif
