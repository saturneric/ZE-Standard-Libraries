#include <type.h>
#include <list/list.h>
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

int insertInHead(List *p_list, Node *p_node) {
#ifdef list_quick_enable
    if(p_list->p_lq != NULL && p_list->p_lq->if_sort) return -1;
    if(p_list->p_lq != NULL){
        if(p_list->head->type == HOLE){
            Node *t_node = p_list->head;
            while(t_node->type == HOLE) t_node = t_node->next;
            replaceNode(p_list, t_node->last, p_node);
            p_list->p_lq->fn_node[t_node->last->f_number] = p_node;
            indexChange(p_list, t_node->last->f_number, 1);
            releaseNode(t_node->last);
            return 0;
        }
        indexChange(p_list, 0, 1);
    }
#endif
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

int insertInTail(List *p_list, Node *p_node) {
#ifdef list_quick_enable
    if(p_list->p_lq != NULL && p_list->p_lq->if_sort) return -1;
#endif
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
    
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        p_node->f_number = p_list->p_lq->rlst_len;
        if(p_list->p_lq->rlst_len >= p_list->p_lq->fn_len){
            p_list->p_lq->fn_node = realloc(p_list->p_lq->fn_node, sizeof(Node *) * (p_list->p_lq->fn_len + FN_NODE_SPARE));
            p_list->p_lq->fn_len += FN_NODE_SPARE;
        }
        p_list->p_lq->fn_node[p_list->p_lq->rlst_len] = p_node;
        p_list->p_lq->rlst_len++;
    }
#endif
    p_list->length += 1;
    return 0;
}
