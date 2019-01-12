#include <type.h>
#include <list/list.h>


/**
 以一个已存在的节点为模板创建一个相同的新的节点

 @param p_node 指向作为模板的节点的指针
 @return 返回指向新的节点的指针
 */
Node *copyNode(Node *p_node) {
    Node *t_node = NULL;
//当开启ID模块的时候编译
#ifdef id_enable
    if (p_node->s_id == NULL) t_node = initNode(0);
    else t_node = initNode(p_node->s_id->deep);
    t_node->s_id = copyS_id(p_node->s_id);
#endif
    t_node->last = p_node->last;
    t_node->next = p_node->next;
    t_node->type = p_node->type;
    t_node->value = p_node->value;
    return t_node;
}


/**
 根据已存在的链表创建一个相同的新的链表

 @param p_list 指向作为模板的链表的指针
 @return 返回指向新链表的指针
 */
List *copyList(List *p_list) {
    Node *p_node;
    Node *t_node;
    List *t_list = NULL;
#ifdef id_enable
    if (p_list->s_id == NULL) t_list = initList(0);
    else t_list = initList(p_list->s_id->deep);
#endif
    t_list->head = p_list->head;
    t_list->tail = p_list->tail;
    t_list->length = p_list->length;
    if(p_list->head != NULL && p_list->tail != NULL){
        p_node = p_list->head;
        while (p_node != NULL) {
            t_node = copyNode(p_node);
            insertInTail(t_list, t_node);
            p_node = p_node->next;
        }
    }
    return t_list;
}
