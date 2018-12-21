#include <type.h>
#include <list/list.h>

Node *initNode(_Bool if_sid) {
    Node *p_node = (Node *)malloc(sizeof(Node));
    if(p_node == NULL){
        return NULL;
    }
    Node *prec_node = NULL;
#ifdef id_enable
    if (if_sid)p_node->s_id = getS_id(LIST_NODE, 1);
    else p_node->s_id = NULL;
#endif
    p_node->next = NULL;
    p_node->last = NULL;
    p_node->type = VOID;
    p_node->f_number = 0;
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        prec_node = initNode(0);
        if_safeModeForNode = 1;
        initMallocValueForNode(prec_node, POINTER, (void *)p_node);
        insertInTail(node_list, prec_node);
    }
    return p_node;
}

List *initList(_Bool if_sid) {
    Node *p_node = NULL;
    List *p_list = (List *)malloc(sizeof(List));
    if(p_list == NULL){
        return NULL;
    }
#ifdef id_enable
    if(if_sid) p_list->s_id = getS_id(LIST, 1);
    else p_list->s_id = NULL;
#endif
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->length = 0;
    p_list->p_lq = NULL;
#ifdef list_simple_h
    p_list->s_head = NULL;
#endif
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        p_node = initNode(0);
        if_safeModeForNode = 1;
        initMallocValueForNode(p_node, POINTER, (void *)p_list);
        insertInTail(list_list, p_node);
    }
    return p_list;
}

inline int initMallocValueForNode(Node *p_node, unsigned int type, const void *p_value) {
    p_node->type = type;
    p_node->value = (void *)p_value;
    return 0;
}
