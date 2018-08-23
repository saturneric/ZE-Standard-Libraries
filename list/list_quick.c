#include <type.h>
#include <list/list.h>
#include <list/list_quick.h>
#include <list/list_expand.h>

static int refreshFnNode(List *p_list);

static int indexTransfromer(List *p_list, unsigned long long m_index);

static void initIdxcList(List *p_list);

int enableListQuick(List *p_list){
    if(p_list->length > ENABLE_LIST_QUICK){
        p_list->p_lq = malloc(sizeof(struct list_quick));
        register struct list_quick *p_lq = p_list->p_lq;
        p_lq->rlst_len = p_list->length;
        p_lq->fn_node = NULL;
        p_lq->if_sort = 0;
        p_lq->idxc_count = 0;
        p_lq->stdid_lst = initList(0);
        for(int i = 0; i < INDEX_CHANGE_MAX; i++) p_lq->idxc_lst[i] = NULL;
        refreshFnNode(p_list);
        //sortListById(p_list, 0, p_list->length);
    }
    return 0;
}

int refreshFnNode(List *p_list){
    if(p_list->p_lq != NULL){
        struct list_quick *blk_plq = p_list->p_lq;
        initIdxcList(p_list);
        if(p_list->p_lq->fn_node != NULL) free(p_list->p_lq->fn_node);
        p_list->p_lq->fn_node = malloc(sizeof(Node *) * (p_list->length + FN_NODE_SPARE));
        p_list->p_lq->fn_len = p_list->length + FN_NODE_SPARE;
        p_list->p_lq->rlst_len = p_list->length;
        register Node *p_node = p_list->head;
        unsigned long long i = 0;
        p_list->p_lq = NULL;
        while (p_node != NULL) {
            if(p_node->type == HOLE){
                removeByNode(p_list, p_node);
                releaseNode(p_node);
                p_node = p_node->next;
                continue;
            }
            p_node->f_number = i;
            blk_plq->fn_node[i] = p_node;
            p_node = p_node->next;
            i++;
        }
        p_list->p_lq = blk_plq;
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
        Node *p_node = NULL;
        if(p_lq->rlst_len > index) p_node = p_lq->fn_node[index];
        else p_node = p_lq->fn_node[p_lq->rlst_len - 1];
        if(p_lq->idxc_count > 0){
            int total_move = indexTransfromer(p_list, index);
            int temp = ABS(total_move);
            if(p_lq->rlst_len > index){
                if(total_move >=0){
                    for(int i = 0; i < temp; ){
                        p_node = p_node->last;
                        if(p_node->type != HOLE) i++;
                    }
                }
                else{
                    for(int i = 0; i < temp; ){
                        p_node = p_node->next;
                        if(p_node->type != HOLE) i--;
                    }
                }
            }
            else{
                unsigned long long jump = index - temp;
                for(int i = 0; i < jump; i++) p_node = p_node->next;
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
    while(fn_node->f_number == 0) fn_node = fn_node->next;
    return fn_node;
}

static void initIdxcList(List *p_list){
    struct list_quick *p_lq = p_list->p_lq;
    for(int i = 0; i < INDEX_CHANGE_MAX; i++){
        if(p_lq->idxc_lst[i] != NULL) free(p_lq->idxc_lst[i]);
        p_lq->idxc_lst[i] = NULL;
    }
    p_lq->idxc_count = 0;
}

void digHole(List *p_list, Node *p_node){
    Node *c_node = copyNode(p_node);
#ifdef id_enable
    freeS_id(c_node->s_id);
#endif
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
