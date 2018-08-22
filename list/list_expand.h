#ifndef LIST_EXPAND_H
#define LIST_EXPAND_H

#include "list.h"




/************************************************
 *回调函数的便捷操作相关宏
 ************************************************/

/****
 *母函数相关
 */

/*
 *若需要母函数需要向毁掉函数传递相关参数则使用该宏
 *参数: argc指示传递参数的类型格式;args为需要返回的参数.*/
#define __SEND_ARG(argc, args...) newReturn(0, -1, argc , args)

/*
 *若快速声明回调函数则使用该宏
 *参数: name为回调函数名.*/
#define __CALLBACK_STATE(name) List *_do##name(unsigned int, void *, List *)

/*
 *若快速定义回调函数则使用该宏
 *参数: name为回调函数名.*/
#define __CALLBACK_DEFINE(name) List *_do##name(unsigned int type, void *value, List *expand_resources)

/*
 *若传递回调函数指针则使用该宏
 *参数: name为回调函数名.*/
#define __CALLBACK_CALL(name) _do##name

/*
 *若母函数获取回调函数返回的指针则使用该宏
 *参数: x为该值的顺序号, type为获取的指针值的类型.*/
#define __RTN_ARGS_P(list,x,type) (type *) lidxp(list, x);

/*
 *若母函数获取回调函数返回的值则使用该宏
 *参数: x为该值的顺序号, type为获取的值的类型.*/
#define __RTN_ARGS(list,x,type) *((type *) lidxp(list, x));

/****
 *回调函数相关
 */

/*
 *若回调函数获取遍历链表中的当前节点的值则使用该宏
 *参数: c_type为获取值的类型.*/
#define __VALUE(c_type) (c_type)value

/*
 *若回调函数获取母函数传递的参数则使用该宏
 *参数: x为该值的顺序号, type为获取值的类型.*/
#define __ARGS(x, type) *((type *) lidxp(expand_resources, x));

/*
 *若回调函数获取母函数传递的指针参数则使用该宏
 *参数: x为该值的顺序号, type为获取的指针值的类型.*/
#define __ARGS_P(x, type) (type *) lidxp(expand_resources, x);

/*
 *若回调函数获取遍历链表的长度则使用该宏
 */
#define __LIST_LEN getInfoForListThrough(expand_resources,0)

/*
 *若回调函数获取遍历链表中当前节点的序号则使用该宏
 */
#define __NOW_INDEX getInfoForListThrough(expand_resources,1)

/*
 *若需要终止遍历或终止遍历并向母函数返回相关参数则使用该宏
 *参数: argc指示返回参数的个数;args为需要返回的参数.*/
#define __RETURN(argc, args...) newReturn(1, -1, argc , args)

/*
 *若继续遍历则使用该宏
 */
#define __CRETURN__ newCReturn()




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
 *单向节点的快速初始化: 为新节点分配内存空间,
 *                  并使用输入值对其进行初始化.
 ************************************************/

/*
 *为新单向节点获取内存空间, 并使用整型值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithInt(int);

/*
 *为新单向节点获取内存空间, 并使用无符号整型值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithUInt(unsigned int);

/*
 *为新单向节点获取内存空间, 并使用浮点值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithDouble(double);

/*
 *为新单向节点获取内存空间, 并使用字符串值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithString(const char *);

/*
 *为新单向节点获取内存空间, 并使用指针值初始化新单向节点
 *返回: 若成功则返回指向新单向节点的指针,若失败函数返回NULL.*/
extern s_Node *s_nodeWithPointer(const void *);




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
extern int updateValueWithULLIntForNode(Node *, unsigned long long);

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
 *链表或节点的输出: 格式化输出链表或节点的属性
 ************************************************/

/*
 *输出链表及其中节点的相关信息
 *参数: priority为每行输出信息前的空格数除以4*/
void printListInfo(List *p_list,int priority);

/*
 *输出节点中的相关信息
 *参数: priority为每行输出信息前的空格数乘以4*/
void printNodeInfo(Node *p_node,int priority);

/*
 *输出链表及其中节点的相关信息
 */
void printList(List *);

/*
 *自定义输出链表及其中节点的相关信息
 *参数: func为一个函数指针, 指向函数的职能在于输出节点中的用户自定义结构的相关信息*/
void printListForCustom(List *p_list,void (*func)(void *value));

/*
 *printListForCustom函数的回调函数
 */
__CALLBACK_STATE(printListForCustom);

/*
 *输出节点中的相关信息
 */
void printNode(Node *p_node);





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
unsigned long long calListMemory(List *);





#endif
