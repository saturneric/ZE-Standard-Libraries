#include <type.h>
#include <list/list.h>


/**
 返回链表的长度

 @param p_list 指向目标链表的指针
 @return 返回目标链表的长度
 */
uint64_t len(List *p_list) {
    return p_list->length;
}

/**
 检查链表是否为空

 @param p_list 指向目标链表的指针
 @return 目标链表为空返回1，不为空返回0
 */
int isListEmpty(List *p_list) {
    if (p_list->head == NULL || p_list->tail == NULL)// If its head or tail is NULL,it would be thought as empty.
        return 1;                // But we should ensure that both of them are NULL when we
    return 0;                    // want to make a list empty.
}
