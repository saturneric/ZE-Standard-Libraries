#ifndef LIST_H
#define LIST_H
#include "../type/type.h"
#include "../id/id.h"

/************************************************
 *节点快速初始化相关宏
 ************************************************/

/****
 *不带ID相关
 */

/*直接获取一个以整型值初始化的节点不带ID的缩略*/
#define lni(x) nodeWithInt(x,0)

/*直接获取一个以无符号整型值初始化的不带ID节点的缩略*/
#define lnu(x) nodeWithUInt(x,0)

/*直接获取一个以无符号长整形值初始化的节点的缩略*/
#define lnull(x) nodeWithULLInt(x,0)

/*直接获取一个以浮点值初始化的不带ID节点的缩略*/
#define lnd(x) nodeWithDouble(x,0)

/*直接获取一个以字符串值初始化的不带ID节点的缩略*/
#define lns(x) nodeWithString(x,0)

/*直接获取一个以指针值初始化的不带ID节点的缩略*/
#define lnp(x) nodeWithPointer(x,0)

/****
 *带ID相关
 */

/*直接获取一个以整型值初始化的带ID节点的缩略*/
#define lsni(x) nodeWithInt(x,1)

/*直接获取一个以浮点值初始化的带ID节点的缩略*/
#define lsnd(x) nodeWithDouble(x,1)

/*直接获取一个以字符串值初始化的带ID节点的缩略*/
#define lsns(x) nodeWithString(x,1)

/*直接获取一个以指针值初始化的节点的缩略*/
#define lsnp(x) nodeWithPointer(x,1)




/************************************************
 *链表快速插入相关宏
 ************************************************/

/****
 *尾部相关
 */

/*在链表尾部直接加入一个已经用整型值初始化的不带ID的节点*/
#define lisrti(list, x) insertInTail(list, lni(x));

/*在链表尾部直接加入一个已经用浮点值初始化的不带ID的节点*/
#define lisrtd(list, x) insertInTail(list, lnd(x));

/*在链表尾部直接加入一个已经用无符号整型值初始化的不带ID的节点*/
#define lisrtu(list, x) insertInTail(list, lnu(x));

/*在链表尾部直接加入一个已经用无符号长整型值初始化的不带ID的节点*/
#define lisrtull(list, x) insertInTail(list, lnull(x));

/*在链表尾部直接加入一个已经用指针值初始化的不带ID的节点*/
#define lisrtp(list, x) insertInTail(list, lnp(x));

/*在链表尾部直接加入一个已经用字符串值初始化的不带ID的节点*/
#define lisrts(list, x) insertInTail(list, lns(x));

/****
 *头部相关
 */

/*在链表头部直接加入一个已经用整型值初始化的不带ID的节点*/
#define lisrhi(list, x) insertInHead(list, lni(x));

/*在链表头部直接加入一个已经用浮点值初始化的不带ID的节点*/
#define lisrhd(list, x) insertInHead(list, lnd(x));

/*在链表头部直接加入一个已经用无符号整型值初始化的不带ID的节点*/
#define lisrhu(list, x) insertInHead(list, lnu(x));

/*在链表头部直接加入一个已经用无符号长整型值初始化的不带ID的节点*/
#define lisrhull(list, x) insertInHead(list, lnull(x));

/*在链表头部直接加入一个已经用指针值初始化的不带ID的节点*/
#define lisrhp(list, x) insertInHead(list, lnp(x));

/*在链表头部直接加入一个已经用字符串值初始化的不带ID的节点*/
#define lisrhs(list, x) insertInHead(list, lns(x));




/************************************************
 *节点快速获得储存值相关宏
 ************************************************/

/*快速获得指针类型的节点所储存的值*/
#define lidxp(list, x) getByPointerForNode(findByIndexForNode(list, x))

/*快速获得整型类型的节点所储存的值*/
#define lidxi(list, x) getByIntForNode(findByIndexForNode(list, x))

/*快速获得浮点类型的节点所储存的值*/
#define lidxd(list, x) getByDoubleForNode(findByIndexForNode(list, x))

/*快速获得字符串类型的节点所储存的值*/
#define lidxs(list, x) getByStringForNode(findByIndexForNode(list, x))

/*快速获得无符号长整型类型的节点所储存的值*/
#define lupdull(list,x,value) updateValueWithULLIntForNode(findByIndexForNode(list, x),value)




/************************************************
 *其他快速操作相关宏
 ************************************************/

/*通过节点的序号直接得到它的值*/
#define lidxvle(list,x) (findByIndexForNode(list, x)->value)

/*通过节点序号直接移除节点*/
#define lrmvidx(list,x) removeByNode(list, findByIndexForNode(list, x)

/*从列表头移除节点的缩略*/
#define lpoph(list) popFromHead(list)

/*从列表尾移除节点的缩略*/
#define lpopt(list) popFromTail(list)

/*通过节点的ID直接获得节点的值*/
#define lfndsid(list,sid) (findByIdForNode(list,sid)->value)

/*创建一个不带ID的链表的缩略*/
#define lstns() initList(0);

/*创建一个带有ID的链表缩略*/
#define lstn() initList(1);

/********************************************************************************************************/

/*********************************************************************************************************
 *安全模式开启函数:在开启安全模式后,记录代码段区间所有用户已经分配过内存的链表和节点.在结束时,释放记录在案的还未释放的链表和节点.
 *注意:在开启后,只有使用库提供的初始化函数的时候才有效.安全模式打开后,只有调用安全模式结束函数后,才可以重新打开.
 *运用:可以在逻辑较为复杂的代码段使用,预防内存泄漏的情况发生.可以免去繁琐的内存泄漏检查过程.
 *返回: 若成功函数返回0,若失败函数返回-1.
 ********************************************************************************************************/
extern int safeModeForNode(int ifon);

/*属于安全模式操作内部调用,释放链表而不释放其中的值.*/
static int releaseSingleListForsafeModeForNode(List *p_list);

/*属于安全模式操作内部调用,释放节点而不释放其中的值.*/
static int releaseSingleNodeForsafeModeForNode(List *p_list);

/*安全模式结束时调用,调用后将会释放所有在安全模式区间内用户已经分配过的链表和节点,安全模式将会关闭.*/
extern int releaseAllForNode(void);

/*
 *初始化链表,并返回指向新链表的指针,参数if_sid指示是否为新链表分配ID号
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern List *initList(_Bool if_sid);

/*
 *初始化节点,并返回指向新链表的指针,参数if_sid指示是否为新节点分配ID号
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *initNode(_Bool if_sid);




/************************************************
 *链表的初始化相关函数
 ************************************************/

/*
 *初始化单向链表节点,该种类节点可以与普通储存在List结构中.
 *单向链表的引入主要在于对于简单问题提供更小开销的解决方案.但相应的操作函数较少,不如一般链表方便.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern s_Node *s_initNode(void);

/*库中内部调用函数,旨在为新节点的储存值获取内存,并将相应的储存值储存在获取到的内存中,并指明储存值的类型.*/
static int initMallocValueForNode(Node *,unsigned int,const void *);




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

/*在单项链表的头部插入一个节点
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int s_insertInHead(List *p_list, s_Node *s_p_node);

/*
 *在单项链表的尾部插入一个节点
 *返回: 若成功函数返回0,若失败函数返回-1.*/
extern int s_insertInTail(List *p_list, s_Node *s_p_node);




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




/**********************************************
 *链表或节点的复制: 链表与节点复制相关函数
 *********************************************/

/*
 *节点的复制,复制将会为新节点重新分配内存,并将源节点的所有值拷贝入新节点.
 *注意: 源节点与新节点ID相同.
 *返回: 若成功函数返回指向新节点的指针,若失败则返回NULL*/
extern Node *copyNode(Node *);

/*
 *链表的复制,复制将会为新链表重新分配内存,并将源链表的所有节点复制.
 *注意: 源链表与新链表ID相同.
 *返回: 若成功函数返回指向新链表的指针,若失败则返回NULL*/
List *copyList(List *p_list);




/***********************************************
 *节点的删除: 节点移除相关函数
 ***********************************************/

/*
 *通过ID查找链表中的特定节点并从链表中移除相关节点,但并不释放节点内存.
 *若成功函数返回0,若失败函数返回-1.*/
extern int removeById(List *p_list, SID *s_id);

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
 *链表或节点的属性:获取或更新链表或节点属性有关的函数
 ***********************************************/

/*
 *返回链表长度*/
extern unsigned long long len(List *p_list);

/*
 *查询链表是否为空
 *返回: 如果链表为空返回1,如果链表不为空则返回0.*/
extern int isListEmpty(List *p_list);

/*
 *直接获得节点中的整型值
 *返回: 返回该节点储存的整型值*/
extern int getByIntForNode(Node *);

/*
 *直接获得节点中的无符号整型值
 *返回: 返回该节点储存的无符号整型值*/
extern unsigned int getByUIntForNode(Node *);

/*
 *直接获得节点中的浮点值
 *返回: 返回该节点储存的浮点值*/
extern double getByDoubleForNode(Node *);

/*
 *直接获得节点中的字符串值
 *返回: 返回该节点储存的字符串值*/
extern char *getByStringForNode(Node *);

/*
 *直接获得节点中的指针值
 *返回: 返回该节点储存的指针值*/
extern void *getByPointerForNode(Node *);

/*
 *直接获得节点的序号
 *返回: 返回该节点在链表中的序号*/
extern unsigned long long getIndexForNode(List *p_list,Node *p_node);

/*
 *通过节点的序号找到节点中相关的值,并更新其中的储存的值的指针.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL*/
extern Node *updateNodeByIndex(List *p_list, void *new_value, unsigned long long index);




/***********************************************
 *链表查找:查找链表中的指定节点有关的函数
 **********************************************/

/*
 *通过ID查找链表中相关的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByIdForNode(List *p_list, SID * s_id);

/*
 *通过节点中的值查找相关单个节点
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByValue(List *p_list, unsigned int type, const void *value);

/*
 *通过序号查找相关的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByIndexForNode(List *, unsigned long long);

/*
 *通过整型值查找储存该值的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByIntForNode(List *, int);

/*
 *通过浮点值查找储存该值的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByDoubleForNode(List *, double);

/*
 *通过字符串中查找储存该值的单个节点.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByStringForNode(List *, char *);

/*
 *通过指针值查找储存该值的单个节点.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern Node *findByPointerForNode(List *, void *);

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
 *内部函数: 通过节点中的值查找相关多个节点.
 *参数: type指明相关值的类型;value为指向储存相关值的内存的指针.
 *返回: 如果成功返回0,如果失败则返回-1.*/
static int sortList(List *p_list, unsigned long long begin, unsigned long long end, int(*func)(Node *f_node, Node *s_node));

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
 *释放单向链表所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseList(List *p_list);

/*
 *自定义释放链表所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,用于释放用户自定义的结构体的所占用内存.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseListForCustom(List *p_list, int (*func)(void *));

/*
 *自定义释放单向链表所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,
 *     接收储存在节点中的值的指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseListForCustom(List *p_list, int (*func)(void *));

/*
 *释放链表所占的内存,但不释放链表中的节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseListForSingle(List *p_list);

/*
 *释放相关节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseNode(Node *p_node);

/*
 *释放单向节点所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseNode(s_Node *s_p_node);

/*
 *自定义释放节点所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放节点时调用,
 *     接收储存在节点中的值的指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseNodeForCustom(Node *p_node, int (*func)(void *));

/*
 *自定义释放单向节点所占的内存空间
 *参数: func是一个函数指针,它指向的函数现在每次释放单项节点时调用,
 *     接收储存在单项节点中的值得指针,释放用户自定义的结构体的所占用内存.
 *     回调函数返回0代表释放成功,返回-1代表释放失败.
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int s_releaseNodeForCustom(s_Node *s_p_node, int (*func)(void *));

/*
 *释放节点所占的内存空间,不释放节点所储存的值所占的内存空间
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int releaseOnlyNode(Node *p_node);

/***********************************************
 *错误的提示:出现错误时,以下函数用于快捷地通报错误信息,
 *         以便根据信息快速找到错误原因.
 **********************************************/

extern int pushInfo(Info *p_info, const char *head,const char *body);

extern Error *pushError(unsigned int type, int pri, Info *p_info);

extern Notice *pushNotice(unsigned int type, Info *p_info);

extern Info *initInfo(const char *head, const char *body);

extern Error *createError(Info *info,unsigned int type,int pri);

extern Notice *createWarning(Info *info, unsigned int type, int pri);

extern int showError(Error *);

extern int showWarning(Notice *);

/***********************************************
 *长链表模式:当链表长度很长时,链表查找的代价将会很大.
 *         该模式用于优化长链表的查找过程.降低时间复杂度.
 ***********************************************/
/*
 *打开长链表模式
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int enableListQuick(List *p_list);

/*
 *关闭长链表模式
 *返回: 如果成功返回0, 失败则返回-1.*/
extern int disableListQuick(List *p_list);

static int refreshFnNode(List *p_list);

static int indexTransfromer(List *p_list, unsigned long long m_index);

static int indexChange(List *p_list, unsigned long long c_index, int move);

static Node *getNodeByFnNode(List *p_list, unsigned long long index);

static Node *findFnNode(List *p_list, Node *p_node);

static void initIdxcList(List *p_list);

static void digHole(List *p_list, Node *p_node);


//Node *getListTail(List *);




/***********************************************
 *相关的全局变量
 ***********************************************/

static int if_safeModeForNode;
static List *node_list;
static List *list_list;




#endif
