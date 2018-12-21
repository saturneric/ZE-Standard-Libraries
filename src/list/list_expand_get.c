#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>

#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

/*直接获得节点中储存的字符串值*/
char *getByStringForNode(Node *p_node) {
	if (p_node->type == STRING) return (char *)(p_node->value);
	else return NULL;
}

double getByDoubleForNode(Node *p_node) {
	if (p_node->type == DOUBLE) return *(double *)(p_node->value);
	else return -1;
}

void *getByPointerForNode(Node *p_node) {
	return (void *)(p_node->value);
}

unsigned long long getIndexByNode(List *p_list, Node *p_node) {
#ifdef list_quick_enable
    if (p_list->p_lq != NULL){
        register Node **p_fn_node = p_list->p_lq->fn_node;
        register Node *rp_node = p_node;
        for (register int i = 0; i < p_list->length; i++) if (p_fn_node[i] == rp_node) return i;
    }
#endif
    register Node *t_node = p_list->head;
    register unsigned long long index = 0;
    while (t_node != NULL) {
#ifdef id_enable
        if (p_node->s_id == t_node->s_id) return index;
#endif
        index++;
        t_node = t_node->next;
    }
	return 0;
}
