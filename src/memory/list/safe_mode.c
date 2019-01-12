#include <type.h>
#include <list/list.h>

static int if_safeModeForNode = 0;
static List *node_list = NULL;
static List *list_list = NULL;

/*属于安全模式操作内部调用,释放节点而不释放其中的值.*/
static int releaseSingleNodeForsafeModeForNode(List *p_list);

/*属于安全模式操作内部调用,释放链表而不释放其中的值.*/
static int releaseSingleListForsafeModeForNode(List *p_list);


int safeModeForNode(int ifon) {
    if (ifon == 1) {
        if (node_list == NULL && list_list == NULL) {
            node_list = (List *)malloc(sizeof(List));
            if(node_list == NULL){
                return -1;
            }
            list_list = (List *)malloc(sizeof(List));
            if(list_list == NULL){
                return -1;
            }
            list_list->head = NULL;
            list_list->length = 0;
            list_list->tail = NULL;
            
            node_list->head = NULL;
            node_list->length = 0;
            node_list->tail = NULL;
            
            if_safeModeForNode = 1;
        }
        else {
            return -1;
        }
    }
    
    return ifon;
}

static int releaseSingleListForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    List *plv_node = NULL;
    while (p_node != NULL) {
        plv_node = (List *)p_node->value;
#ifdef id_enable
        freeS_id(plv_node->s_id);
#endif
        plv_node->head = NULL;
        plv_node->length = 0;
        plv_node->tail = NULL;
        free(plv_node);
        p_node = p_node->next;
    }
    p_list->head = NULL;
    p_list->length = 0;
    p_list->tail = NULL;
#ifdef id_enable
    freeS_id(p_list->s_id);
#endif
    free(p_list);
    return 0;
}

static int releaseSingleNodeForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    Node *pnv_node = NULL;
    while (p_node != NULL) {
        pnv_node = (Node *)p_node->value;
#ifdef id_enable
        freeS_id(pnv_node->s_id);
#endif
        pnv_node->last = NULL;
        pnv_node->next = NULL;
        pnv_node->type = VOID;
        pnv_node->value = NULL;
        free(pnv_node);
        p_node = p_node->next;
    }
#ifdef id_enable
    free(p_list->s_id);
#endif
    p_list->head = NULL;
    p_list->length = 0;
    p_list->tail = NULL;
    free(p_list);
    return 0;
}

int releaseAllForNode(void) {
    if (if_safeModeForNode == 1) {
        if_safeModeForNode = 0;
        releaseSingleNodeForsafeModeForNode(node_list);
        releaseSingleListForsafeModeForNode(list_list);
    }
    return 0;
}
