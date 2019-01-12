#include <type.h>
#include <list/list.h>

int releaseNode(Node *p_node) {
    if (if_safeModeForNode == 1) {
        removeByNode(node_list, p_node);
    }
    if (p_node->value != NULL) {
        if (p_node->type != POINTER) {
            if (p_node->type == LIST) {
                releaseList((List *)p_node->value);
            }
            else {
                free(p_node->value);
            }
        }
        p_node->value = NULL;
    }
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
#ifdef id_enable
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
#endif
    free(p_node);
    return 0;
}

int releaseOnlyNode(Node *p_node) {
#ifdef id_enable
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
#endif
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
    free(p_node);
    return 0;
}

int releaseList(List *p_list) {
    Node *p_node, *pl_node;
    p_node = p_list->head;
    if (if_safeModeForNode == 1) {
        Node *tar_list = findByValue(list_list, POINTER, (void *)p_list);//turn pointer in to int to compare.
        removeByNode(list_list, tar_list);
    }
    while (p_node != NULL) {
        pl_node = p_node;
        p_node = p_node->next;
        pl_node->next = NULL;
        pl_node->last = NULL;
        releaseNode(pl_node);
    }
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->length = 0;
    free(p_list);
    return 0;
}

int releaseListForSingle(List *p_list) {
    releaseList(p_list);
    return 0;
}

int releaseNodeForCustom(Node *p_node, int (*func)(void *)){
    if (if_safeModeForNode) {
        removeByNode(node_list, p_node);
    }
    if (p_node->value != NULL) {
        if (func(p_node->value))
        p_node->value = NULL;
    }
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
#ifdef id_enable
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
#endif
    free(p_node);
    return 0;
}

int releaseListForCustom(List *p_list, int (*func)(void *)){
    Node *p_node, *pl_node;
    p_node = p_list->head;
    if (if_safeModeForNode == 1) {
        Node *tar_list = findByValue(list_list, POINTER, (void *)p_list);
        removeByNode(list_list, tar_list);
    }
    while (p_node != NULL) {
        pl_node = p_node;
        p_node = p_node->next;
        pl_node->next = NULL;
        pl_node->last = NULL;
        releaseNodeForCustom(pl_node,func);
    }
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->length = 0;
#ifdef id_enable
    if (p_list->s_id != NULL) freeS_id(p_list->s_id);
#endif
    free(p_list);
    return  0;
}
