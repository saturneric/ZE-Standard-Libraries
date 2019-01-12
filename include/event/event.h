#ifndef event_h
#define event_h

#include <chain/chain.h>

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

#endif /* event_h */
