#ifndef list_print_h
#define list_print_h

#include <list/list_type.h>
#include <list/list_expand_1.h>

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


#endif /* list_print_h */
