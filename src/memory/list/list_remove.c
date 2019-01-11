#include <type.h>
#include <list/list.h>

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
    p_node->last->next = p_node->next;
    p_node->next->last = p_node->last;
    p_list->length -= 1;
    return 0;//not find
}

Node *popFromHead(List *p_list) {
    if (isListEmpty(p_list))
        return NULL;
    Node *p_node = p_list->head;
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
