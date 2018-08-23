#include <type.h>
#include <list/list_simple.h>
#include <list/list_type.h>
#include <list/list.h>

inline s_Node *s_initNode(void){
    s_Node *s_p_node = (s_Node *)malloc(sizeof(s_Node));
    s_p_node->next = NULL;
    return s_p_node;
}

inline int s_insertInHead(List *p_list, s_Node *s_p_node){
    if(p_list->s_head == NULL && p_list->s_tail == NULL){
        p_list->s_head = s_p_node;
        p_list->s_tail = s_p_node;
    }
    else{
        s_p_node->next = p_list->s_head;
        p_list->s_head = s_p_node;
    }
    return 0;
}

inline int s_insertInTail(List *p_list, s_Node *s_p_node){
    if(p_list->s_head == NULL && p_list->s_tail == NULL){
        p_list->s_head = s_p_node;
        p_list->s_tail = s_p_node;
    }
    else{
        p_list->s_tail->next = s_p_node;
        p_list->s_tail = s_p_node;
    }
    return 0;
}

s_Node *s_findByIndexForNode(List *p_list, unsigned long long m_index) {
    s_Node *s_p_node = p_list->s_head;
    unsigned long long i;
    for (i = 0; i < m_index; i++) {
        s_p_node = s_p_node->next;
    }
    return s_p_node;
}

inline int s_releaseNode(s_Node *s_p_node){
    free(s_p_node);
    return 0;
}

inline int s_releaseNodeForCustom(s_Node *s_p_node, int (*func)(void *)){
    func(s_p_node->value);
    free(s_p_node);
    return 0;
}

int s_releaseListForCustom(List *p_list, int (*func)(void *)){
    register s_Node *s_p_node, *s_pl_node;
    s_p_node = p_list->s_head;
    while (s_p_node != NULL) {
        s_pl_node = s_p_node;
        s_p_node = s_p_node->next;
        s_pl_node->next = NULL;
        s_releaseNodeForCustom(s_pl_node,func);
    }
    free(p_list);
    return  0;
}
