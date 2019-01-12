#ifndef chain_h
#define chain_h

#include <chain/chain_type.h>
#include <chain/chain.h>

/************************************************
 *节点的快速初始化: 为新节点分配内存空间,
 *               并使用输入值对其进行初始化.
 ************************************************/

/*
 *为新节点获取内存空间, 并使用整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithInt(int, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用无符号整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithUInt(unsigned int, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用无符号长整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithULLInt(unsigned long long, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用浮点值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithDouble(double, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用字符串值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithString(const char *, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用指针值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithPointer(const void *, _Bool if_sid);



/************************************************
 *嵌套节点的快速初始化: 为嵌套节点节点分配内存空间,
 *                  并使用输入值对其进行初始化
 *说明: 嵌套节点指储存一个链表指针的节点.
 ************************************************/

/*
 *为新嵌套节点获取内存空间
 *返回: 若成功指向新嵌套节点的指针,若失败函数返回NULL.*/
extern CNode *nodeWithComplex(void);

/*
 *用输入的值初始化嵌套节点
 *参数: type指明所输入值的类型,value为指向所输入值的内存空间的指针
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addValueForComplex(CNode *, int type, void *value);

/*
 *用输入的整型值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addIntForComplex(CNode *, int);

/*
 *用输入的浮点值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addDoubleForComplex(CNode *, double);

/*
 *用输入的字符串初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addStringForComplex(CNode *, char *);

/*
 *用输入的指针值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addPointerForComplex(CNode *, void *);




/************************************************
 *节点值的更新: 更新既有节点中的值,并用新值直接替换旧值
 ************************************************/

/*
 *用输入的整型值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithIntForNode(CNode *,int);

/*
 *用输入的无符号长整型值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithULLIntForNode(CNode *, uint64_t);

/*
 *用输入的浮点值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithDoubleForNode(CNode *,double);

/*
 *用输入的字符串值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithStringForNode(CNode *,char *);

/*
 *用输入的指针值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithPointerForNode(CNode *,void *);




/************************************************
 *链表的查找: 依据输入值,查找链表中的多个特定类型的节点
 ************************************************/

/*
 *通过输入的整型值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
Chain *mply_findByIntForNode(Chain*, int);

/*
 *通过输入的浮点值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
Chain *mply_findByDoubleForNode(Chain*, double);

/*
 *通过输入的字符串值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
Chain *mply_findByStringForNode(Chain*, char *);

/*
 *通过输入的指针值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
Chain *mply_findByPointerForNode(Chain*, void *);






/************************************************
 *链表的遍历: 遍历链表相关函数
 ************************************************/

/*
 *链表的遍历
 *参数: p_func为一个函数指针, 指向的回调函数的职能在于接受每个节点的类型(type)/值指针(value)/传入参数链表(args),
 然后进行相关操作,并返回一个链表,其中包含返回状态,若有,也可以包含想要传递给母函数的值
 expand_resources为一个链表,储存母函数想要传递给回调函数的值
 *返回: 如果回调函数有需要返回给母函数的值,则返回包含这些值的链表,否则返回NULL.*/
extern Chain *listThrough(Chain *p_list, Chain *(*p_func)(unsigned int type, void *value, Chain *args), Chain *expand_resources);

/*
 *回调函数相关宏操作的辅助函数,用于给回调函数给母函数返回值提供便利
 */
extern Chain *newReturn(int if_status ,int status, char *argc, ...);

/*
 *回调函数相关宏操作的辅助函数,用于回调函数返回空值提供便利
 */
Chain *newCReturn(void);

/*
 *回调函数相关宏操作的辅助函数,用于给回调函数获取母函数传入的参数返提供便利
 */
uint64_t getInfoForListThrough(Chain *expand_resources, int type);





/************************************************
 *链表大小: 计算链表大小相关函数
 ************************************************/

/*
 *以字节为单位计算链表的大小
 */
uint64_t calListMemory(Chain *);




/***********************************************
 *链表或节点的属性:获取或更新链表或节点属性有关的函数
 ***********************************************/

/*
 *返回链表长度*/
extern uint64_t len(Chain *p_list);

/*
 *查询链表是否为空
 *返回: 如果链表为空返回1,如果链表不为空则返回0.*/
extern int isListEmpty(Chain *p_list);

/*
 *直接获得节点中的整型值
 *返回: 返回该节点储存的整型值*/
extern int getByIntForNode(CNode *);

/*
 *直接获得节点中的无符号整型值
 *返回: 返回该节点储存的无符号整型值*/
extern unsigned int getByUIntForNode(CNode *);

/*
 *直接获得节点中的浮点值
 *返回: 返回该节点储存的浮点值*/
extern double getByDoubleForNode(CNode *);

/*
 *直接获得节点中的字符串值
 *返回: 返回该节点储存的字符串值*/
extern char *getByStringForNode(CNode *);

/*
 *直接获得节点中的指针值
 *返回: 返回该节点储存的指针值*/
extern void *getByPointerForNode(CNode *);

/*
 *直接获得节点的序号
 *返回: 返回该节点在链表中的序号*/
extern unsigned long long getIndexForNode(Chain *p_list,CNode *p_node);

/*
 *通过节点的序号找到节点中相关的值,并更新其中的储存的值的指针.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL*/
extern CNode *updateNodeByIndex(Chain *p_list, void *new_value, unsigned long long index);




/**********************************************
 *链表或节点的复制: 链表与节点复制相关函数
 *********************************************/

/*
 *节点的复制,复制将会为新节点重新分配内存,并将源节点的所有值拷贝入新节点.
 *注意: 源节点与新节点ID相同.
 *返回: 若成功函数返回指向新节点的指针,若失败则返回NULL*/
extern CNode *copyNode(CNode *);

/*
 *链表的复制,复制将会为新链表重新分配内存,并将源链表的所有节点复制.
 *注意: 源链表与新链表ID相同.
 *返回: 若成功函数返回指向新链表的指针,若失败则返回NULL*/
Chain *copyList(Chain *p_list);


/*
 *通过序号查找相关的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern CNode *findByIndexForNode(Chain *, unsigned long long);

/*
 *通过整型值查找储存该值的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern CNode *findByIntForNode(Chain *, int);

/*
 *通过浮点值查找储存该值的单个节点
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern CNode *findByDoubleForNode(Chain *, double);

/*
 *通过字符串中查找储存该值的单个节点.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern CNode *findByStringForNode(Chain *, char *);

/*
 *通过指针值查找储存该值的单个节点.
 *返回: 如果成功返回指向该节点的指针,如果失败则返回NULL.*/
extern CNode *findByPointerForNode(Chain *, void *);




/************************************************
 *节点快速初始化相关宏,提供函数名较为简单的调用方式
 ************************************************/

/****
 *不带ID模块相关宏
 */

/*直接获取一个以整型值初始化的节点不带ID的缩略*/
#define lni(cn) nodeWithInt(cn,0)

/*直接获取一个以无符号整型值初始化的不带ID节点的缩略*/
#define lnu(cn) nodeWithUInt(cn,0)

/*直接获取一个以无符号长整形值初始化的节点的缩略*/
#define lnull(cn) nodeWithULLInt(cn,0)

/*直接获取一个以浮点值初始化的不带ID节点的缩略*/
#define lnd(cn) nodeWithDouble(cn,0)

/*直接获取一个以字符串值初始化的不带ID节点的缩略*/
#define lns(cn) nodeWithString(cn,0)

/*直接获取一个以指针值初始化的不带ID节点的缩略*/
#define lnp(cn) nodeWithPointer(cn,0)

/****
 *带ID模块的相关宏
 */

/*直接获取一个以整型值初始化的带ID节点的缩略*/
#define lsni(cn) nodeWithInt(cn,1)

/*直接获取一个以浮点值初始化的带ID节点的缩略*/
#define lsnd(cn) nodeWithDouble(cn,1)

/*直接获取一个以字符串值初始化的带ID节点的缩略*/
#define lsns(cn) nodeWithString(cn,1)

/*直接获取一个以指针值初始化的节点的缩略*/
#define lsnp(cn) nodeWithPointer(cn,1)




/************************************************
 *链表快速插入相关宏
 ************************************************/

/****
 *尾部相关
 */

/*在链表尾部直接加入一个已经用整型值初始化的不带ID的节点*/
#define lisrti(chain, cn) insertInTail(chain, lni(cn));

/*在链表尾部直接加入一个已经用浮点值初始化的不带ID的节点*/
#define lisrtd(chain, cn) insertInTail(chain, lnd(cn));

/*在链表尾部直接加入一个已经用无符号整型值初始化的不带ID的节点*/
#define lisrtu(chain, cn) insertInTail(chain, lnu(cn));

/*在链表尾部直接加入一个已经用无符号长整型值初始化的不带ID的节点*/
#define lisrtull(chain, cn) insertInTail(chain, lnull(cn));

/*在链表尾部直接加入一个已经用指针值初始化的不带ID的节点*/
#define lisrtp(chain, cn) insertInTail(chain, lnp(cn));

/*在链表尾部直接加入一个已经用字符串值初始化的不带ID的节点*/
#define lisrts(chain, cn) insertInTail(chain, lns(cn));

/****
 *头部相关
 */

/*在链表头部直接加入一个已经用整型值初始化的不带ID的节点*/
#define lisrhi(chain, cn) insertInHead(chain, lni(cn));

/*在链表头部直接加入一个已经用浮点值初始化的不带ID的节点*/
#define lisrhd(chain, cn) insertInHead(chain, lnd(cn));

/*在链表头部直接加入一个已经用无符号整型值初始化的不带ID的节点*/
#define lisrhu(chain, cn) insertInHead(chain, lnu(cn));

/*在链表头部直接加入一个已经用无符号长整型值初始化的不带ID的节点*/
#define lisrhull(chain, cn) insertInHead(chain, lnull(cn));

/*在链表头部直接加入一个已经用指针值初始化的不带ID的节点*/
#define lisrhp(chain, cn) insertInHead(chain, lnp(cn));

/*在链表头部直接加入一个已经用字符串值初始化的不带ID的节点*/
#define lisrhs(chain, cn) insertInHead(chain, lns(cn));




/************************************************
 *节点快速获得储存值相关宏
 ************************************************/

/*快速获得指针类型的节点所储存的值*/
#define lidxp(chain, cn) getByPointerForNode(findByIndexForNode(chain, cn))

/*快速获得整型类型的节点所储存的值*/
#define lidxi(chain, cn) getByIntForNode(findByIndexForNode(chain, cn))

/*快速获得浮点类型的节点所储存的值*/
#define lidxd(chain, cn) getByDoubleForNode(findByIndexForNode(chain, cn))

/*快速获得字符串类型的节点所储存的值*/
#define lidxs(chain, cn) getByStringForNode(findByIndexForNode(chain, cn))

/*快速获得无符号长整型类型的节点所储存的值*/
#define lupdull(chain,cn,value) updateValueWithULLIntForNode(findByIndexForNode(chain, cn),value)




/************************************************
 *其他快速操作相关宏
 ************************************************/

/*通过节点的序号直接得到它的值*/
#define lidxvle(chain,cn) (findByIndexForNode(chain, cn)->value)

/*通过节点序号直接移除节点*/
#define lrmvidx(chain,cn) removeByNode(chain, findByIndexForNode(chain, cn)

/*从列表头移除节点的缩略*/
#define lpoph(chain) popFromHead(chain)

/*从列表尾移除节点的缩略*/
#define lpopt(chain) popFromTail(chain)

/*通过节点的ID直接获得节点的值*/
#define lfndsid(chain,sid) (findByIdForNode(chain,sid)->value)

/*创建一个不带ID的链表的缩略*/
#define lstns() initList(0);

/*创建一个带有ID的链表缩略*/
#define lstn() initList(1);

#endif /* chain_h */
