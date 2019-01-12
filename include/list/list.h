#ifndef list_h
#define list_h

#include <list/list_type.h>


/************************************************
 *链表的初始化相关函数
 ************************************************/

/*
 *初始化链表,并返回指向新链表的指针,参数if_sid指示是否为新链表分配ID号
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
#ifdef id_enable
extern List *initList(_Bool if_sid);
#else
extern List *initList(void);
#endif

/*
 *初始化节点,并返回指向新链表的指针,参数if_sid指示是否为新节点分配ID号
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
#ifdef id_enable
extern Node *initNode(_Bool if_sid);
#else
extern Node *initNode(void);
#endif

/*库中内部调用函数,旨在为新节点的储存值获取内存,并将相应的储存值储存在获取到的内存中,并指明储存值的类型.*/
extern int initMallocValueForNode(Node *,unsigned int,const void *);




/*************************************************
 *节点的插入: 节点的插入操作相关函数
 *************************************************/

/*
 *在链表的头部插入一个节点*
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int insertInHead(List *p_list, Node *p_node);

/*
 *在链表的尾部插入一个节点
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int insertInTail(List *p_list, Node *p_node);

/*
 *在一个节点的后面插入一个节点
 *参数说明: t_node为指向目标节点的指针;p_node为指向新节点的指针;
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int insertAfterNode(List *p_list, Node *t_node, Node *p_node);

/*
 *在一个节点的前面插入一个节点
 *参数: t_node为指向目标节点的指针;p_node为指向新节点的指针;
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int insertBeforeNode(List *p_list, Node*t_node, Node *p_node);




/***********************************************
 节点的替换与调换: 节点的替换与调换相关的函数
 ***********************************************/

/*
 *用一个新节点,替换掉链表中已经存在的节点
 *参数: t_node为指向目标节点的指针;p_node为指向新节点的指针;
 */
extern int replaceNode(List *p_list, Node *t_node, Node *p_node);

/*
 *交换两个已经在链表中的节点的位置
 *参数: t_node为指向目标节点的指针;p_node为指向新节点的指针;
 */

extern int exchangeNode(List *p_list, Node *f_node, Node *s_node);




/***********************************************
 *节点的删除: 节点移除相关函数
 ***********************************************/

#ifdef id_enable
/*
 *通过ID查找链表中的特定节点并从链表中移除相关节点,但并不释放节点内存.
 *若成功函数返回0,若失败函数返回-1.*/
extern int removeById(List *p_list, SID *s_id);
#endif

/*
 *通过指向节点的指针直接从链表中移除相关节点,但不释放节点内存
 *若成功函数返回0,若失败函数返回-1.*/
extern int removeByNode(List *p_list, Node *p_node);

/*
 *从链表头部移除第一个节点,不释放节点内存,返回节点指向该节点的指针,方便后续操作
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *popFromHead(List *p_list);

/*
 *从链表尾部移除最后一个节点,不释放节点内存,返回节点指向该节点的指针,方便后续操作
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *popFromTail(List *p_list);




/***********************************************
 *链表查找:查找链表中的指定节点有关的函数
 **********************************************/

#ifdef id_enable
/*
 *通过ID查找链表中相关的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByIdForNode(List *p_list, SID * s_id);
#endif

/*
 *通过节点中的值查找相关单个节点
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByValue(List *p_list, unsigned int type, const void *value);

//void *findByIdForCustom(List *p_list, SID *s_id, int func(SID *));

/*
 *通过节点中的值查找相关多个节点.
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回一个链表,储存所有满足该值的节点的指针.如果失败则返回NULL.*/
extern List *mply_findByValue(List *p_list, unsigned int type, const void *value);




/***********************************************
 *链表的排序: 使用快速排序算法,按照指定规则排序链表
 **********************************************/

/*
 *自定义排序链表.
 *参数: func是一个函数指针, 指向的函数接受两个指向链表中节点的指针,并对他们进行比较
        如果前一的相关值个大于后一个得相关值则返会大于0的数, 反之则返回小于0的数.
 *返回: 如果成功返回0,如果失败则返回-1.*/
extern int sortListForCustom(List *p_list, int(*func)(Node *f_node, Node *s_node));




/***********************************************
 *链表或节点的释放: 释放链表或节点所占内存的相关函数
 **********************************************/

/*
 *释放链表所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseList(List *p_list);

/*
 *自定义释放链表所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,用于释放用户自定义的结构体的所占用内存.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseListForCustom(List *p_list, int (*func)(void *));

/*
 *释放链表所占的内存,但不释放链表中的节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseListForSingle(List *p_list);

/*
 *释放相关节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseNode(Node *p_node);

/*
 *自定义释放节点所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,
 *     接收储存在节点中的值的指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseNodeForCustom(Node *p_node, int (*func)(void *));

/*
 *释放节点所占的内存空间,不释放节点所储存的值所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseOnlyNode(Node *p_node);


extern int isListEmpty(List *p_list);



/***********************************************
 *相关的全局变量
 ***********************************************/

static int if_safeModeForNode;
static List *node_list;
static List *list_list;




#endif
