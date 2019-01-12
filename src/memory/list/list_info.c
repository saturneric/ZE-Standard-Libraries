#include <type.h>
#include <list/list.h>


/**
 返回链式结构的长度

 @param p_list 指向目标链式结构的指针
 @return 返回目标链式结构的长度
 */
uint64_t len(List *p_list) {
    return p_list->length;
}

/**
 检查链式结构是否为空

 @param p_list 指向目标链式结构的指针
 @return 目标链式结构为空返回1，不为空返回0
 */
int isListEmpty(List *p_list) {
    if (p_list->head == NULL || p_list->tail == NULL)// If its head or tail is NULL,it would be thought as empty.
        return 1;                // But we should ensure that both of them are NULL when we
    return 0;                    // want to make a list empty.
}
