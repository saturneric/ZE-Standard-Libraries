#include <type.h>
#include <list/list.h>
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

int replaceNode(List *p_list, Node *pt_node, Node *p_node){
    p_node->next = pt_node->next;
    p_node->last = pt_node->last;
    if (p_list->head != pt_node) pt_node->last->next = p_node;
    else p_list->head = p_node;
    if(p_list->tail != pt_node) pt_node->next->last = p_node;
    else p_list->tail = p_node;
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        if(pt_node->f_number == 0 && p_list->p_lq->fn_node[0] != pt_node){
            p_node->f_number = pt_node->f_number;
        }
        else{
            p_list->p_lq->fn_node[pt_node->f_number] = p_node;
            p_node->f_number = pt_node->f_number;
        }
    }
#endif
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
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        p_list->p_lq->fn_node[f_node->f_number] = s_node;
        p_list->p_lq->fn_node[s_node->f_number] = f_node;
        unsigned long long temp = f_node->f_number;
        f_node->f_number = s_node->f_number;
        s_node->f_number = temp;
    }
#endif
    return 0;
}
