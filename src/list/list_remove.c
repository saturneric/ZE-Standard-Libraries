#include <type.h>
#include <list/list.h>
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

#ifdef id_enable
int removeById(List *p_list, SID *s_id) {
    Node *tmp = p_list->head;
    if (isListEmpty(p_list))
        return -1;
    do {
        if (simFitS_id(tmp->s_id, s_id)) {
            if (tmp != p_list->head) {
                tmp->last->next = tmp->next;
            }
            else {
                p_list->head = tmp->next;
            }
            if (tmp != p_list->tail) {
                tmp->next->last = tmp->last;
            }
            else {
                p_list->tail = tmp->last;
            }
            
            p_list->length -= 1;
            return 1;//found
        }
        else {
            tmp = tmp->next;
        }
    } while (tmp != NULL);
    
    return 0;//not find
}

#endif

int removeByNode(List *p_list, Node *p_node) {
    if (isListEmpty(p_list))
        return -1;
    if(p_node == p_list->head){
        popFromHead(p_list);
        return 0;
    }
    else if(p_node == p_list->tail){
        popFromTail(p_list);
        return 0;
    }
    if(p_list->p_lq == NULL){
        p_node->last->next = p_node->next;
        p_node->next->last = p_node->last;
    }
    else{
#ifdef list_quick_enable
        if(p_node->f_number == 0){
            Node *fn_node = findFnNode(p_list, p_node);
            indexChange(p_list, fn_node->f_number, -1);
            p_node->last->next = p_node->next;
            p_node->next->last = p_node->last;
        }
        else{
            digHole(p_list, p_node);
        }
#endif
    }
    p_list->length -= 1;
    return 0;//not find
}

Node *popFromHead(List *p_list) {
    if (isListEmpty(p_list))
        return NULL;
    Node *p_node = p_list->head;
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        if(p_list->head->type == HOLE){
            Node *t_node = p_list->head;
            while(t_node->type == HOLE) t_node = t_node->next;
            if(t_node->f_number != 0){
                Node *r_node = t_node;
                digHole(p_list, t_node);
                return r_node;
            }
            p_node = t_node;
        }
        else{
            if(p_list->p_lq->fn_node[0] == p_list->head){
                Node *r_node = p_list->head;
                digHole(p_list, p_list->head);
                return r_node;
            }
        }
    }
#endif
    //Node *tmp = p_list->head;
    p_list->head->next->last = NULL;
    p_list->head = p_list->head->next;
    //releaseNode(tmp); not necessary
    if (isListEmpty(p_list)) {
        p_list->head = NULL;
        p_list->tail = NULL;
    }
    p_list->length -= 1;
    return p_node;
}

Node *popFromTail(List *p_list) {
    Node *p_node = p_list->tail;
    if (isListEmpty(p_list))
        return NULL;
    else {
#ifdef list_quick_enable
        if(p_list->p_lq != NULL){
            if(p_list->p_lq->fn_node[p_list->p_lq->rlst_len - 1] == p_list->tail){
                p_list->p_lq->fn_node[p_list->p_lq->rlst_len - 1] = NULL;
                p_list->p_lq->rlst_len--;
                if(p_list->p_lq->fn_len - p_list->p_lq->rlst_len > FN_NODE_SPARE * 2){
                    p_list->p_lq->fn_node = realloc(p_list->p_lq->fn_node, sizeof(p_list->p_lq->fn_len - FN_NODE_SPARE));
                    p_list->p_lq->fn_len -= FN_NODE_SPARE;
                }
            }
        }
#endif
        //Node *tmp = p_list->tail;
        p_list->tail->last->next = NULL;
        p_list->tail = p_list->tail->last;
        //releaseNode(tmp); not necessary
    }
    if (isListEmpty(p_list)) {
        p_list->head = NULL;
        p_list->tail = NULL;
    }
    p_list->length -= 1;
    return p_node;
}
