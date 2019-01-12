#include <type.h>
#include <list/list.h>

//如果ID模块可能启用则编译以下代码
#ifdef id_enable
/**
 通过ID查找链表中符合条件的第一个节点

 @param p_list 指向目标链表的指针
 @param s_id ID值
 @return 成功返回指向符合条件的节点的指针，不成功则返回NULL
 */
Node *findByIdForNode(List *p_list, SID * s_id) {
    Node *ph_node = p_list->head;
    Node *pt_node = p_list->tail;
    int direction = 0;
    while (ph_node != pt_node) {
        if (direction == 0) {
            if (simFitS_id(ph_node->s_id, s_id)) {
                return ph_node;
            }
            else {
                ph_node = ph_node->next;
            }
            direction = 1;
        }
        else {
            if (simFitS_id(pt_node->s_id, s_id)) {
                return pt_node;
            }
            else {
                pt_node = pt_node->last;
            }
        }
    }
    return NULL;
}
#endif


/**
 通过值来查找链表中符合条件的第一个节点

 @param p_list 指向目标链表的指针
 @param type 值的类型
 @param value 值
 @return 成功返回指向符合条件的节点的指针，不成功则返回NULL
 */
Node *findByValue(List *p_list, uint type, const void *value) {
    Node *p_node = p_list->head;
    while (p_node != NULL) {
        if (p_node->type != type) {
            p_node = p_node->next;
            continue;
        }
        if (type == INT) {
            if (*((int *)p_node->value) == *((int *)value)) {
                return p_node;
            }
        }
        else if (type == DOUBLE) {
            if (*((double *)p_node->value) == *((double *)value)) {
                return p_node;
            }
        }
        else if (type == STRING) {
            if (!strcmp((char *)p_node->value, (char *)value))
            {
                return p_node;
            }
        }
        else if (type == POINTER) {
            if (p_node->value == value) {
                return p_node;
            }
        }
        
        p_node = p_node->next;
        
    }
    return NULL;
}

/**
 通过值来查找链表中符合条件的所有节点
 
 @param p_list 指向目标链表的指针
 @param type 值的类型
 @param value 值
 @return 返回含有所有符合条件的节点的重组链表
 */
List *mply_findByValue(List *p_list, unsigned int type, const void *value) {
    List *f_list = initList(0);
    Node *p_node = p_list->head;
    while (p_node != NULL) {
        if (p_node->type != type) {
            p_node = p_node->next;
            continue;
        }
        if (type == INT) {
            if (*((int *)p_node->value) == *((int *)value)) {
                Node *f_node = p_node;
                insertInTail(f_list, f_node);
            }
        }
        else if (type == DOUBLE) {
            if (*((double *)p_node->value) == *((double *)value)) {
                Node *f_node = p_node;
                insertInTail(f_list, f_node);
            }
        }
        else if (type == STRING) {
            if (!strcmp((char *)p_node->value, (char *)value))
            {
                Node *f_node = p_node;
                insertInTail(f_list, f_node);
            }
        }
        else if (type == POINTER) {
            if (p_node->value == value) {
                Node *f_node = p_node;
                insertInTail(f_list, f_node);
            }
        }
        
        p_node = p_node->next;
        
    }
    return f_list;
}
