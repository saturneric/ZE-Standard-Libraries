#ifndef list_print_h
#define list_print_h

#include <chain/chain.h>
#include <event/event.h>

/************************************************
 *链表或节点的输出: 格式化输出链表或节点的属性
 ************************************************/

/*
 *输出链表及其中节点的相关信息
 *参数: priority为每行输出信息前的空格数除以4*/
void printListInfo(Chain *p_list,int priority);

/*
 *输出节点中的相关信息
 *参数: priority为每行输出信息前的空格数乘以4*/
void printNodeInfo(CNode *p_node,int priority);

/*
 *输出链表及其中节点的相关信息
 */
void printList(Chain *);

/*
 *自定义输出链表及其中节点的相关信息
 *参数: func为一个函数指针, 指向函数的职能在于输出节点中的用户自定义结构的相关信息*/
void printListForCustom(Chain *p_list,void (*func)(void *value));

/*
 *printListForCustom函数的回调函数
 */
__CALLBACK_STATE(printListForCustom);

/*
 *输出节点中的相关信息
 */
void printNode(CNode *p_node);


#endif /* list_print_h */
