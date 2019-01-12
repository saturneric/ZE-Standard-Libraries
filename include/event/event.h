#ifndef list_expand_1_h
#define list_expand_1_h

#include <chain/chain.h>

/************************************************
 *节点快速初始化相关宏,提供函数名较为简单的调用方式
 ************************************************/

/****
 *不带ID模块相关宏
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
 *带ID模块的相关宏
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

#endif /* list_expand_1_h */



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
