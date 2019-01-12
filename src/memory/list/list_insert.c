#include <type.h>
#include <list/list.h>

/**
 在链表的头部插入节点

 @param p_list 指向目标链表的指针
 @param p_node 指向目标节点的指针
 @return 函数执行成功返回0
 */
int insertInHead(List *p_list, Node *p_node) {
    if (isListEmpty(p_list)) {
        p_list->head = p_node;
        p_list->tail = p_node;
    }
    else {
        p_list->head->last = p_node;
        p_node->last = NULL;
        p_node->next = p_list->head;
        p_list->head = p_node;
    }
    p_list->length += 1;
    return 0;
}

/**
 在链表的尾部插入节点

 @param p_list 指向目标链表的指针
 @param p_node 指向目标节点的指针
 @return 函数执行成功返回0
 */
int insertInTail(List *p_list, Node *p_node) {
//    如果可能需要使用长链表模块则编译以下代码
/*
#ifdef list_quick_enable
    if(p_list->p_lq != NULL && p_list->p_lq->if_sort) return -1;
#endif
*/
    if (isListEmpty(p_list)) {
        p_list->head = p_node;
        p_list->tail = p_node;
    }
    else {
        p_list->tail->next = p_node;
        p_node->next = NULL;
        p_node->last = p_list->tail;
        p_list->tail = p_node;
    }
    p_list->length += 1;
    return 0;
}
