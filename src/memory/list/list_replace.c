#include <type.h>
#include <list/list.h>

int replaceNode(List *p_list, Node *pt_node, Node *p_node){
    p_node->next = pt_node->next;
    p_node->last = pt_node->last;
    if (p_list->head != pt_node) pt_node->last->next = p_node;
    else p_list->head = p_node;
    if(p_list->tail != pt_node) pt_node->next->last = p_node;
    else p_list->tail = p_node;
    return 0;
}

int exchangeNode(List *p_list, Node *f_node, Node *s_node){
    Node *fl_node = f_node->last, *fn_node = f_node->next;
    if(p_list->head != f_node) f_node->last->next = s_node;
    else p_list->head = s_node;
    if(p_list->tail != f_node) f_node->next->last = s_node;
    else p_list->tail = s_node;
    
    if(p_list->head != s_node) s_node->last->next = f_node;
    else p_list->head = f_node;
    if(p_list->tail != s_node) s_node->next->last = f_node;
    else p_list->tail = f_node;
    f_node->next = s_node->next;
    f_node->last = s_node->last;
    s_node->next = fn_node;
    s_node->last = fl_node;
    return 0;
}
