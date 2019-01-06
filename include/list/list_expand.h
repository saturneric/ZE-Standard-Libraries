#ifndef list_expand_h
#define list_expand_h

#include <list/list_type.h>


/************************************************
 *节点的快速初始化: 为新节点分配内存空间,
 *               并使用输入值对其进行初始化.
 ************************************************/

/*
 *为新节点获取内存空间, 并使用整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithInt(int, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用无符号整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithUInt(unsigned int, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用无符号长整型值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithULLInt(unsigned long long, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用浮点值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithDouble(double, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用字符串值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithString(const char *, _Bool if_sid);

/*
 *为新节点获取内存空间, 并使用指针值初始化新节点
 *参数if_sid指示函数是否为节点获取ID
 *返回: 若成功则返回指向新节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithPointer(const void *, _Bool if_sid);



/************************************************
 *嵌套节点的快速初始化: 为嵌套节点节点分配内存空间,
 *                  并使用输入值对其进行初始化
 *说明: 嵌套节点指储存一个链表指针的节点.
 ************************************************/

/*
 *为新嵌套节点获取内存空间
 *返回: 若成功指向新嵌套节点的指针,若失败函数返回NULL.*/
extern Node *nodeWithComplex(void);

/*
 *用输入的值初始化嵌套节点
 *参数: type指明所输入值的类型,value为指向所输入值的内存空间的指针
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addValueForComplex(Node *, int type, void *value);

/*
 *用输入的整型值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addIntForComplex(Node *, int);

/*
 *用输入的浮点值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addDoubleForComplex(Node *, double);

/*
 *用输入的字符串初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addStringForComplex(Node *, char *);

/*
 *用输入的指针值初始化嵌套节点
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int addPointerForComplex(Node *, void *);




/************************************************
 *节点值的更新: 更新既有节点中的值,并用新值直接替换旧值
 ************************************************/

/*
 *用输入的整型值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithIntForNode(Node *,int);

/*
 *用输入的无符号长整型值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithULLIntForNode(Node *, uint64_t);

/*
 *用输入的浮点值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithDoubleForNode(Node *,double);

/*
 *用输入的字符串值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithStringForNode(Node *,char *);

/*
 *用输入的指针值更新节点中的值
 *返回: 若成功则返回0,若失败函数返回-1.*/
extern int updateValueWithPointerForNode(Node *,void *);




/************************************************
 *链表的查找: 依据输入值,查找链表中的多个特定类型的节点
 ************************************************/

/*
 *通过输入的整型值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
List *mply_findByIntForNode(List*, int);

/*
 *通过输入的浮点值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
List *mply_findByDoubleForNode(List*, double);

/*
 *通过输入的字符串值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
List *mply_findByStringForNode(List*, char *);

/*
 *通过输入的指针值,查找链表中多个含有该值的节点
 *返回: 若成功则返回一个储存由这些指向这些节点指针组成的链表,若失败函数返回NULL.*/
List *mply_findByPointerForNode(List*, void *);






/************************************************
 *链表的遍历: 遍历链表相关函数
 ************************************************/

/*
 *链表的遍历
 *参数: p_func为一个函数指针, 指向的回调函数的职能在于接受每个节点的类型(type)/值指针(value)/传入参数链表(args),
       然后进行相关操作,并返回一个链表,其中包含返回状态,若有,也可以包含想要传递给母函数的值
       expand_resources为一个链表,储存母函数想要传递给回调函数的值
 *返回: 如果回调函数有需要返回给母函数的值,则返回包含这些值的链表,否则返回NULL.*/
extern List *listThrough(List *p_list, List *(*p_func)(unsigned int type, void *value, List *args), List *expand_resources);

/*
 *回调函数相关宏操作的辅助函数,用于给回调函数给母函数返回值提供便利
 */
extern List *newReturn(int if_status ,int status, char *argc, ...);

/*
 *回调函数相关宏操作的辅助函数,用于回调函数返回空值提供便利
 */
List *newCReturn(void);

/*
 *回调函数相关宏操作的辅助函数,用于给回调函数获取母函数传入的参数返提供便利
 */
unsigned long long getInfoForListThrough(List *expand_resources, int type);





/************************************************
 *链表大小: 计算链表大小相关函数
 ************************************************/

/*
 *以字节为单位计算链表的大小
 */
uint64_t calListMemory(List *);




/***********************************************
 *链表或节点的属性:获取或更新链表或节点属性有关的函数
 ***********************************************/

/*
 *返回链表长度*/
extern uint64_t len(List *p_list);

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

#endif
