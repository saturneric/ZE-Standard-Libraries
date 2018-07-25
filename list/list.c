#include "list.h"

static int if_safeModeForNode = 0;
static List *node_list = NULL; //储存声明过的节点.
static List *list_list = NULL; //储存声明过的链表.

int safeModeForNode(int ifon) {
    if (ifon == 1) {
        if (node_list == NULL && list_list == NULL) {
            node_list = (List *)malloc(sizeof(List));
            list_list = (List *)malloc(sizeof(List));
            
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

int releaseSingleListForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    List *plv_node = NULL;
    while (p_node != NULL) {
        plv_node = (List *)p_node->value;
        plv_node->id = 0;
        plv_node->head = NULL;
        plv_node->length = 0;
        plv_node->tail = NULL;
        free(plv_node);
        p_node = p_node->next;
    }
    p_list->head = NULL;
    p_list->length = 0;
    p_list->tail = NULL;
    p_list->id = 0;
    free(p_list);
    return 0;
}

int releaseSingleNodeForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    Node *pnv_node = NULL;
    while (p_node != NULL) {
        pnv_node = (Node *)p_node->value;
        pnv_node->id = 0;
        pnv_node->if_malloc = 0;
        pnv_node->last = NULL;
        pnv_node->next = NULL;
        pnv_node->type = VOID;
        pnv_node->value = NULL;
        free(pnv_node);
        p_node = p_node->next;
    }
    p_list->id = 0;
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

Node *initNode(void) {
    Node *p_node = (Node *)malloc(sizeof(Node));
    Node *prec_node = NULL;
    p_node->id = getId();
    p_node->if_malloc = 0;
    p_node->next = NULL;
    p_node->last = NULL;
    p_node->type = VOID;
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        prec_node = initNode();
        if_safeModeForNode = 1;
        initMallocValueForNode(prec_node, POINTER, (void *)p_node);
        insertInTail(node_list, prec_node);
    }
    return p_node;
}

List *initList(void) {
    Node *p_node;
    List *p_list = (List *)malloc(sizeof(List));
    p_list->id = getId();
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->length = 0;
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        p_node = initNode();
        if_safeModeForNode = 1;
        initMallocValueForNode(p_node, POINTER, (void *)p_list);
        insertInTail(list_list, p_node);
    }
    return p_list;
}

int initMallocValueForNode(Node *p_node, int type, void *p_value) {
    p_node->if_malloc = 1;
    p_node->type = type;
    p_node->value = p_value;
    return 0;
}

int insertInHead(List *p_list, Node *p_node) {
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
    p_list->length += 1;
    return 0;
}

int releaseNode(Node *p_node) {
    if (if_safeModeForNode == 1) {
        removeByNode(node_list, p_node);
    }
    if (p_node->if_malloc == 1) {
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
    p_node->id = 0;
    p_node->if_malloc = 0;
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
    p_list->id = 0;
    free(p_list);
    return 0;
}

int releaseListForSingle(List *p_list) {
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->id = 0;
    p_list->length = 0;
    free(p_list);
    return 0;
}

unsigned long long len(List *p_list) {
    return p_list->length;
}

int removeById(List *p_list, unsigned long long id) {
    Node *tmp = p_list->head;
    if (isListEmpty(p_list))
        return -1;
    do {
        if (tmp->id == id) {
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

int removeByNode(List *p_list, Node *p_node) {
    Node *tmp = p_list->head;
    if (isListEmpty(p_list))
        return -1;
    do {
        if (tmp == p_node) {
            tmp->last->next = tmp->next;
            tmp->next->last = tmp->last;
            p_list->length -= 1;
            return 1;//found
        }
        else {
            tmp = tmp->next;
        }
    } while (tmp != NULL);
    
    return 0;//not find
}

int popFromHead(List *p_list) {
    if (isListEmpty(p_list))
        return -1;
    else {
        //Node *tmp = p_list->head;
        p_list->head->next->last = NULL;
        p_list->head = p_list->head->next;
        //releaseNode(tmp); not necessary
        p_list->length -= 1;
    }
    
    if (isListEmpty(p_list)) {
        p_list->head = NULL;
        p_list->tail = NULL;
    }
    return 0;
}

int popFromTail(List *p_list) {
    if (isListEmpty(p_list))
        return -1;
    else {
        //Node *tmp = p_list->tail;
        p_list->tail->last->next = NULL;
        p_list->tail = p_list->tail->last;
        //releaseNode(tmp); not necessary
        p_list->length -= 1;
    }
    
    if (isListEmpty(p_list)) {
        p_list->head = NULL;
        p_list->tail = NULL;
    }
    return 0;
}

/*该函数算法需要改进*/
Node *findByIdForNode(List *p_list, const unsigned long long id) {
    Node *ph_node = p_list->head;
    Node *pt_node = p_list->tail;
    int direction = 0;
    while (ph_node != pt_node) {
        if (direction == 0) {
            if (ph_node->id == id) {
                return ph_node;
            }
            else {
                ph_node = ph_node->next;
            }
            direction = 1;
        }
        else {
            if (pt_node->id == id) {
                return pt_node;
            }
            else {
                pt_node = pt_node->last;
            }
        }
    }
    return NULL;
}


Node *findByValue(List *p_list, int type, const void *value) {
    Node *p_node = p_list->head;
    while (p_node != NULL) {
        if (p_node->type != type) {
            p_node = p_node->next;
            continue;//跳过不合类型的节点
        }
        if (type == INT) {
            if (*((int *)p_node->value) == *((int *)value)) {
                return copyNode(p_node);
            }
        }
        else if (type == DOUBLE) {
            if (*((double *)p_node->value) == *((double *)value)) {
                return copyNode(p_node);
            }
        }
        else if (type == STRING) {
            if (!strcmp((char *)p_node->value, (char *)value))
            {
                return copyNode(p_node);
            }
        }
        else if (type == POINTER) {
            if (p_node->value == value) {
                return copyNode(p_node);
            }
        }
        
        p_node = p_node->next;
        
    }
    return NULL;
}

List *mply_findByValue(List *p_list, int type, const void *value) {
    List *f_list = initList();
    Node *p_node = p_list->head;
    while (p_node != NULL) {
        if (p_node->type != type) {
            p_node = p_node->next;
            continue;
        }
        if (type == INT) {
            if (*((int *)p_node->value) == *((int *)value)) {
                Node *f_node = copyNode(p_node);
                insertInTail(f_list, f_node);
            }
        }
        else if (type == DOUBLE) {
            if (*((double *)p_node->value) == *((double *)value)) {
                Node *f_node = copyNode(p_node);
                insertInTail(f_list, f_node);
            }
        }
        else if (type == STRING) {
            if (!strcmp((char *)p_node->value, (char *)value))
            {
                Node *f_node = copyNode(p_node);
                insertInTail(f_list, f_node);
            }
        }
        else if (type == POINTER) {
            if (p_node->value == value) {
                Node *f_node = copyNode(p_node);
                insertInTail(f_list, f_node);
            }
        }
        
        p_node = p_node->next;
        
    }
    return f_list;
}

int isListEmpty(List *p_list) {
    if (p_list->head == NULL || p_list->tail == NULL)// If its head or tail is NULL,it would be thought as empty.
        return 1;                // But we should ensure that both of them are NULL when we
    return 0;                    // want to make a list empty.
}

int exchangeLocation(Node *p_node, Node *t_node) {
    Node *temp_next = p_node->next;
    Node *temp_last = p_node->last;
    p_node->last->next = t_node;
    p_node->next->last = t_node;
    t_node->last->next = p_node;
    t_node->next->last = p_node;
    p_node->next = t_node->next;
    p_node->last = t_node->last;
    t_node->next = temp_next;
    t_node->last = temp_last;
    return 0;
}

Node *copyNode(Node *p_node) {
    Node *t_node = initNode();
    t_node->id = p_node->id;
    t_node->last = p_node->last;
    t_node->next = p_node->next;
    t_node->if_malloc = p_node->if_malloc;
    t_node->type = p_node->type;
    t_node->value = p_node->value;
    return t_node;
}

List *copyList(List *p_list) {
    Node *p_node;
    Node *t_node;
    List *t_list = initList();
    t_list->head = p_list->head;
    t_list->tail = p_list->tail;
    t_list->id = p_list->id;
    p_node = p_list->head;
    while (p_node != NULL) {
        t_node = copyNode(p_node);
        insertInTail(t_list, t_node);
        p_node = p_node->next;
    }
    return t_list;
}

int releaseOnlyNode(Node *p_node) {
    p_node->id = 0;
    p_node->if_malloc = 0;
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
    free(p_node);
    return 0;
}
