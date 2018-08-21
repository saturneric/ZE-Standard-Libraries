#include "list.h"

static int if_safeModeForNode = 0;
static List *node_list = NULL;
static List *list_list = NULL;

int safeModeForNode(int ifon) {
    if (ifon == 1) {
        if (node_list == NULL && list_list == NULL) {
            node_list = (List *)malloc(sizeof(List));
            if(node_list == NULL){
                showError(pushError(LIST, HIGH, initInfo("safeModeForNode()", "Error in getting the memory of node_list.")));
                return -1;
            }
            list_list = (List *)malloc(sizeof(List));
            if(list_list == NULL){
                showError(pushError(LIST, HIGH, initInfo("safeModeForNode()", "Error in getting the memory of list_list.")));
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

int releaseSingleListForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    List *plv_node = NULL;
    while (p_node != NULL) {
        plv_node = (List *)p_node->value;
        freeS_id(plv_node->s_id);
        plv_node->head = NULL;
        plv_node->length = 0;
        plv_node->tail = NULL;
        free(plv_node);
        p_node = p_node->next;
    }
    p_list->head = NULL;
    p_list->length = 0;
    p_list->tail = NULL;
    freeS_id(p_list->s_id);
    free(p_list);
    return 0;
}

int releaseSingleNodeForsafeModeForNode(List *p_list) {
    Node *p_node = p_list->head;
    Node *pnv_node = NULL;
    while (p_node != NULL) {
        pnv_node = (Node *)p_node->value;
        freeS_id(pnv_node->s_id);
        pnv_node->last = NULL;
        pnv_node->next = NULL;
        pnv_node->type = VOID;
        pnv_node->value = NULL;
        free(pnv_node);
        p_node = p_node->next;
    }
    free(p_list->s_id);
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

Node *initNode(_Bool if_sid) {
    Node *p_node = (Node *)malloc(sizeof(Node));
    if(p_node == NULL){
        showError(pushError(LIST_NODE, STANDARD, initInfo("initNode()", "Error in getting the memory of node.")));
        return NULL;
    }
    Node *prec_node = NULL;
    if (if_sid)p_node->s_id = getS_id(LIST_NODE, 1);
        else p_node->s_id = NULL;
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

inline s_Node *s_initNode(void){
    s_Node *s_p_node = (s_Node *)malloc(sizeof(s_Node));
    s_p_node->next = NULL;
    return s_p_node;
}

List *initList(_Bool if_sid) {
    Node *p_node = NULL;
    List *p_list = (List *)malloc(sizeof(List));
    if(p_list == NULL){
        showError(pushError(LIST_NODE, STANDARD, initInfo("initList()", "Error in getting the memory of list.")));
        return NULL;
    }
    if(if_sid) p_list->s_id = getS_id(LIST, 1);
        else p_list->s_id = NULL;
    p_list->head = NULL;
    p_list->tail = NULL;
    p_list->length = 0;
    p_list->p_lq = NULL;
    p_list->s_head = NULL;
    if (if_safeModeForNode) {
        if_safeModeForNode = 0;
        p_node = initNode(0);
        if_safeModeForNode = 1;
        initMallocValueForNode(p_node, POINTER, (void *)p_list);
        insertInTail(list_list, p_node);
    }
    return p_list;
}

int initMallocValueForNode(Node *p_node, unsigned int type, const void *p_value) {
    p_node->type = type;
    p_node->value = (void *)p_value;
    return 0;
}

int insertInHead(List *p_list, Node *p_node) {
    if(p_list->p_lq != NULL && p_list->p_lq->if_sort) return -1;
    if(p_list->p_lq != NULL){
        if(p_list->head->type == HOLE){
            Node *t_node = p_list->head;
            replaceNode(p_list, p_list->head, p_node);
            p_list->p_lq->fn_node[0] = p_node;
            releaseNode(t_node);
            indexChange(p_list, 0, 1);
            return 0;
        }
        indexChange(p_list, 0, 1);
    }
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

int insertInTail(List *p_list, Node *p_node) {
    if(p_list->p_lq != NULL && p_list->p_lq->if_sort) return -1;
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
    
    if(p_list->p_lq != NULL){
        p_node->f_number = p_list->p_lq->rlst_len;
        if(p_list->p_lq->rlst_len >= p_list->p_lq->rlst_len + FN_NODE_SPARE)
            p_list->p_lq->fn_node = realloc(p_list->p_lq->fn_node, sizeof(Node *) * (p_list->p_lq->rlst_len + FN_NODE_SPARE));
        p_list->p_lq->fn_node[p_list->p_lq->rlst_len] = p_node;
        p_list->p_lq->rlst_len++;
    }
    
    p_list->length += 1;
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
    p_node->f_number = 0;
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
    free(p_node);
    return 0;
}

inline int s_releaseNode(s_Node *s_p_node){
    free(s_p_node);
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
    p_list->s_head = NULL;
    p_list->s_tail = NULL;
    if (p_list->s_id != NULL) freeS_id(p_list->s_id);
    if(p_list->p_lq != NULL) disableListQuick(p_list);
    free(p_list);
    return 0;
}

int releaseListForSingle(List *p_list) {
    releaseList(p_list);
    return 0;
}

unsigned long long len(List *p_list) {
    return p_list->length;
}

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
        if(p_node != p_list->head){
            if(p_node->f_number == 0){
                Node *fn_node = findFnNode(p_list, p_node);
                indexChange(p_list, fn_node->f_number, -1);
                p_node->last->next = p_node->next;
                p_node->next->last = p_node->last;
            }
            else{
                digHole(p_list, p_node);
            }
        }
        p_list->length -= 1;
    }
    return 0;//not find
}

Node *popFromHead(List *p_list) {
    if (isListEmpty(p_list))
        return NULL;
    Node *p_node = p_list->head;
    if(p_list->p_lq != NULL){
        if(p_list->p_lq->fn_node[0] == p_list->head){
            digHole(p_list, p_list->head);
        }
    }
    else{
        //Node *tmp = p_list->head;
        p_list->head->next->last = NULL;
        p_list->head = p_list->head->next;
        //releaseNode(tmp); not necessary
        if (isListEmpty(p_list)) {
            p_list->head = NULL;
            p_list->tail = NULL;
        }
        p_list->length -= 1;
    }
    return p_node;
}

Node *popFromTail(List *p_list) {
    Node *p_node = p_list->tail;
    if (isListEmpty(p_list))
        return NULL;
    else {
        if(p_list->p_lq != NULL){
            if(p_list->p_lq->fn_node[p_list->p_lq->rlst_len] == p_list->tail)
                p_list->p_lq->fn_node = realloc(p_list->p_lq->fn_node, sizeof(p_list->p_lq->rlst_len - 1));
        }
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

Node *findByIdForNode(List *p_list, SID * s_id) {
    Node *ph_node = p_list->head;
    Node *pt_node = p_list->tail;
    int direction = 0;
    while (ph_node != pt_node) {
        if (direction == 0) {
            if (simFitS_id(ph_node->s_id, s_id)) {
                return ph_node;
            }
            else {
                ph_node = ph_node->next;
            }
            direction = 1;
        }
        else {
            if (simFitS_id(pt_node->s_id, s_id)) {
                return pt_node;
            }
            else {
                pt_node = pt_node->last;
            }
        }
    }
    return NULL;
}

Node *findByValue(List *p_list, unsigned int type, const void *value) {
    Node *p_node = p_list->head;
    while (p_node != NULL) {
        if (p_node->type != type) {
            p_node = p_node->next;
            continue;
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

List *mply_findByValue(List *p_list, unsigned int type, const void *value) {
    List *f_list = initList(0);
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

Node *copyNode(Node *p_node) {
    Node *t_node = NULL;
    if (p_node->s_id == NULL) t_node = initNode(0);
        else t_node = initNode(p_node->s_id->deep);
    t_node->s_id = copyS_id(p_node->s_id);
    t_node->last = p_node->last;
    t_node->next = p_node->next;
    t_node->type = p_node->type;
    t_node->value = p_node->value;
    t_node->f_number = p_node->f_number;
    return t_node;
}

List *copyList(List *p_list) {
    Node *p_node;
    Node *t_node;
    List *t_list = NULL;
    if (p_list->s_id == NULL) t_list = initList(0);
        else t_list = initList(p_list->s_id->deep);
    t_list->head = p_list->head;
    t_list->tail = p_list->tail;
    t_list->s_id = p_list->s_id;
    t_list->s_head = p_list->s_head;
    t_list->length = p_list->length;
    t_list->s_tail = p_list->s_tail;
    if(p_list->head != NULL && p_list->tail != NULL){
    p_node = p_list->head;
        while (p_node != NULL) {
            t_node = copyNode(p_node);
            insertInTail(t_list, t_node);
            p_node = p_node->next;
        }
    }
    return t_list;
}

int releaseOnlyNode(Node *p_node) {
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
    free(p_node);
    return 0;
}

int releaseNodeForCustom(Node *p_node, int (*func)(void *)){
    if (if_safeModeForNode) {
        removeByNode(node_list, p_node);
    }
    if (p_node->value != NULL) {
        if (func(p_node->value))
            showError(pushError(LIST_NODE, STANDARD, initInfo("releaseNodeForCustom()", "Error in using custom freeing value function.")));
        p_node->value = NULL;
    }
    p_node->last = NULL;
    p_node->next = NULL;
    p_node->type = VOID;
    p_node->value = NULL;
    if (p_node->s_id != NULL) freeS_id(p_node->s_id);
    free(p_node);
    return 0;
}

inline int s_releaseNodeForCustom(s_Node *s_p_node, int (*func)(void *)){
    func(s_p_node->value);
    free(s_p_node);
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
    if (p_list->s_id != NULL) freeS_id(p_list->s_id);
    if(p_list->p_lq != NULL) disableListQuick(p_list);
    free(p_list);
    return  0;
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

int pushInfo(Info *p_info, const char *head, const char *body) {
    strcpy(p_info->head, head);
    strcpy(p_info->body, body);
    return 0;
}

Error *pushError(unsigned int type, int pri, Info *p_info) {
    Error *p_error  = (Error *)malloc(sizeof(Error));
    p_error->type = type;
    p_error->priority = pri;
    p_error->info = *p_info;
    p_error->time = time(NULL);
    free(p_info);
    return p_error;
}

Notice *pushNotice(unsigned int type, Info *p_info) {
    Notice *p_notice = (Notice *)malloc(sizeof(Notice));
    p_notice->type = type;
    p_notice->info = *p_info;
    p_notice->time = time(NULL);
    free(p_info);
    return p_notice;
}

Info *initInfo(const char *head, const char *body){
    Info *p_info = (Info *)malloc(sizeof(Info));
    pushInfo(p_info, head, body);
    return p_info;
}

int showError(Error *p_error){
    printf("\n");
    for (int i = 0; i < p_error->priority; i++) {
        printf("!");
    }
    
    printf("(Error) %s\n",asctime(localtime(&p_error->time)));
    printf("%s: %s.\n",p_error->info.head,p_error->info.body);
    free(p_error);
    return 0;
}

int showWarning(Notice *p_notice){
    printf("\n@");
    printf("(Warning) %s\n",asctime(localtime(&p_notice->time)));
    printf("%s: %s.\n",p_notice->info.head,p_notice->info.body);
    free(p_notice);
    return 0;
}

int replaceNode(List *p_list, Node *pt_node, Node *p_node){
    p_node->next = pt_node->next;
    p_node->last = pt_node->last;
    if (p_list->head != pt_node) pt_node->last->next = p_node;
        else p_list->head = p_node;
    if(p_list->tail != pt_node) pt_node->next->last = p_node;
    else p_list->tail = p_node;
    
    if(p_list->p_lq != NULL){
        if(pt_node->f_number == 0 && p_list->p_lq->fn_node[0] != pt_node){
            p_node->f_number = pt_node->f_number;
        }
        else{
            p_list->p_lq->fn_node[pt_node->f_number] = p_node;
            p_node->f_number = pt_node->f_number;
        }
    }
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
    if(p_list->p_lq != NULL){
        p_list->p_lq->fn_node[f_node->f_number] = s_node;
        p_list->p_lq->fn_node[s_node->f_number] = f_node;
        unsigned long long temp = f_node->f_number;
        f_node->f_number = s_node->f_number;
        s_node->f_number = temp;
    }
    return 0;
}

int sortList(List *p_list, unsigned long long begin, unsigned long long end, int(*func)(Node *f_node, Node *s_node)){
    unsigned long long target_index = begin;
    register Node *t_node = findByIndexForNode(p_list, target_index);
    register Node *i_node = NULL, *j_node = NULL;
    
    register unsigned long long i = end,j = begin;
    for(; i >= begin; i--){
        if(i <= j) break;
        i_node = findByIndexForNode(p_list, i);
        if(func(t_node, i_node) < 0){
            exchangeNode(p_list, t_node, i_node);
            for(; j <= end; j++){
                if(j >= i) break;
                j_node = findByIndexForNode(p_list, j);
                if(func(t_node, j_node) > 0){
                    exchangeNode(p_list, t_node, j_node);
                    break;
                }
            }
        }
    }
    if(end - begin > 3){
        if(t_node->f_number - begin > 2)
            sortList(p_list, begin, t_node->f_number, func);
        if(end - t_node->f_number > 2)
            sortList(p_list, t_node->f_number, end, func);
    }
    return 0;
}

int sortListForCustom(List *p_list, int(*func)(Node *f_node, Node *s_node)){
    if(p_list->p_lq != NULL && !p_list->p_lq->if_sort) p_list->p_lq->if_sort = 1;
    sortList(p_list, 0, p_list->length-1, func);
    return 0;
}

int enableListQuick(List *p_list){
    if(p_list->length > ENABLE_LIST_QUICK){
        p_list->p_lq = malloc(sizeof(struct list_quick));
        register struct list_quick *p_lq = p_list->p_lq;
        p_lq->rlst_len = p_list->length;
        p_lq->fn_node = malloc(sizeof(Node *) * (p_list->length + FN_NODE_SPARE));
        p_lq->if_sort = 0;
        refreshFnNode(p_list);
        //sortListById(p_list, 0, p_list->length);
        return 0;
    }
    return -1;
}

int refreshFnNode(List *p_list){
    if(p_list->p_lq != NULL){
        initIdxcList(p_list);
        if(p_list->p_lq->fn_node != NULL) free(p_list->p_lq->fn_node);
        p_list->p_lq->fn_node = malloc(sizeof(Node *) * p_list->length);
        register Node *p_node = p_list->head;
        unsigned long long i = 0;
        while (p_node != NULL) {
            p_node->f_number = i++;
            p_list->p_lq->fn_node[i] = p_node;
            p_node = p_node->next;
        }
        return 0;
    }
    return -1;
}

int indexChange(List *p_list, unsigned long long c_index, int move){
    if(p_list->p_lq != NULL){
        struct index_change *t_idxc;
        struct list_quick *p_lq = p_list->p_lq;
        if(p_lq->idxc_count >= INDEX_CHANGE_MAX){
            refreshFnNode(p_list);
            for(int i = 0; i < INDEX_CHANGE_MAX; i++){
                free(p_lq->idxc_lst[i]);
                p_lq->idxc_lst[i] = NULL;
            }
            return 0;
        }
        for(int i = 0; p_lq->idxc_lst[i] != NULL; i++){
            if(p_lq->idxc_lst[i]->c_index == c_index){
                p_lq->idxc_lst[i]->f_count += move;
                return 0;
            }
        }
        if(p_lq->idxc_count == 0) {
            p_lq->idxc_lst[0] = malloc(sizeof(struct index_change));
            t_idxc = p_lq->idxc_lst[0];
        }
        else {
            p_lq->idxc_lst[p_lq->idxc_count] = malloc(sizeof(struct index_change));
            t_idxc = p_lq->idxc_lst[p_lq->idxc_count];
        }
        t_idxc->c_index = c_index;
        t_idxc->f_count = move;
        p_lq->idxc_count++;
    }
    return 0;
}

int indexTransfromer(List *p_list, unsigned long long m_index){
    int total_move = 0;
    struct list_quick *p_lq = p_list->p_lq;
    struct index_change **p_idxclst = p_lq->idxc_lst;
    if(p_lq->idxc_lst[0] != NULL){
        for (int i = 0; p_idxclst[i] != NULL && i < INDEX_CHANGE_MAX; i++) {
            if(p_idxclst[i]->c_index <= m_index) total_move += p_idxclst[i]->f_count;
            if(total_move >= 65535){
                refreshFnNode(p_list);
                return 0;
            }
        }
    }
    return total_move;
}

Node *getNodeByFnNode(List *p_list, unsigned long long index){
    if(p_list->p_lq != NULL){
        struct list_quick *p_lq = p_list->p_lq;
        Node *p_node = p_lq->fn_node[index];
        if(p_lq->idxc_count > 0){
            int total_move = indexTransfromer(p_list, index);
            if(total_move >=0){
                for(int i = 0; i < ABS(total_move); i++) p_node = p_node->last;
            }
            else{
                for(int i = 0; i < ABS(total_move); i++) p_node = p_node->next;
            }
            return p_node;
        }
        else{
            return p_lq->fn_node[index];
        }
        
    }
    return NULL;
}

int insertAfterNode(List *p_list, Node *t_node, Node *p_node){
    if(t_node == p_list->tail){
        insertInTail(p_list, p_node);
        return 0;
    }
    if(p_list->p_lq != NULL){
        if(t_node->next->type == HOLE){
            Node *temp_node = t_node->next;
            replaceNode(p_list, t_node->next, p_node);
            p_node->f_number = temp_node->f_number;
            releaseNode(temp_node);
            p_list->p_lq->fn_node[p_node->f_number] = p_node;
            indexChange(p_list, p_node->f_number, 1);
        }
    }
    p_node->next = t_node->next;
    p_node->last = t_node;
    if(p_list->tail != t_node)
        t_node->next->last = p_node;
    else
        p_list->tail = p_node;
    
    t_node->next = p_node;
    
    if(p_list->p_lq != NULL){
        Node *fn_node = findFnNode(p_list, p_node);
        while(fn_node->f_number != 0) fn_node = fn_node->next;
        indexChange(p_list, fn_node->f_number, 1);
    }
    p_list->length += 1;
    return 0;
}

int insertBeforeNode(List *p_list, Node*t_node, Node *p_node){
    if(t_node == p_list->head){
        insertInHead(p_list, p_node);
        return 0;
    }
    if(p_list->p_lq != NULL){
        if(t_node->last->type == HOLE){
            Node *temp_node = t_node->last;
            replaceNode(p_list, t_node->last, p_node);
            p_node->f_number = temp_node->f_number;
            releaseNode(temp_node);
            p_list->p_lq->fn_node[p_node->f_number] = p_node;
            indexChange(p_list, p_node->f_number, 1);
            return 0;
        }
    }
    p_node->last = t_node->last;
    p_node->next = t_node;
    if(p_list->head != t_node)
        t_node->last->next = p_node;
    else
        p_list->head = p_node;
    t_node->last = p_node;
    if(p_list->p_lq != NULL){
        Node *fn_node = findFnNode(p_list, p_node);
        indexChange(p_list, fn_node->f_number, 1);
    }
    p_list->length += 1;
    return 0;
}

Node *findFnNode(List *p_list, Node *p_node){
    Node *fn_node = p_node;
    while(fn_node->f_number != 0) fn_node = fn_node->next;
    return fn_node;
}

void initIdxcList(List *p_list){
    struct list_quick *p_lq = p_list->p_lq;
    for(int i = 0; i < INDEX_CHANGE_MAX; i++){
        if(p_lq->idxc_lst[i] != NULL) free(p_lq->idxc_lst[i]);
        p_lq->idxc_lst[i] = NULL;
    }
    p_lq->idxc_count = 0;
}
                
void digHole(List *p_list, Node *p_node){
    Node *c_node = copyNode(p_node);
    freeS_id(c_node->s_id);
    replaceNode(p_list, p_node, c_node);
    c_node->value = NULL;
    c_node->type = HOLE;
    indexChange(p_list, p_node->f_number, -1);
}

int disableListQuick(List *p_list){
    free(p_list->p_lq->fn_node);
    initIdxcList(p_list);
    free(p_list->p_lq);
    return 0;
}
