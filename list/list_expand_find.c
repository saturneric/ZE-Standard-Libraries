#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>
#ifdef list_quick_enable
#include <list/list_quick.h>
#endif

Node *findByIntForNode(List *p_list, int target) {
    Node *t_node;
    int *p_target = (int *)malloc(sizeof(int));
    *p_target = target;
    t_node = findByValue(p_list, INT, p_target);
    free(p_target);
    return t_node;
}

Node *findByDoubleForNode(List *p_list, double target) {
    Node *t_node;
    double *p_target = (double *)malloc(sizeof(double));
    *p_target = target;
    t_node = findByValue(p_list, DOUBLE, p_target);
    free(p_target);
    return t_node;
}

Node *findByStringForNode(List *p_list, char *target) {
    Node *t_node;
    char *p_temp = (char *)malloc(sizeof(char)*(strlen(target) + 1));
    strcpy(p_temp, target);
    t_node = findByValue(p_list, STRING, p_temp);
    free(p_temp);
    return t_node;
}

Node *findByPointerForNode(List *p_list, void *target) {
    Node *t_node = findByValue(p_list, POINTER, target);
    return t_node;
}

List *mply_findByInt(List* p_list, int temp) {
    int *p_temp = (int *)malloc(sizeof(int));
    if(p_temp == NULL){
        return NULL;
    }
    List *t_list;
    *p_temp = temp;
    t_list = mply_findByValue(p_list, INT, (void *)p_temp);
    free(p_temp);
    return t_list;
}

List *mply_findByDouble(List* p_list, double temp) {
    List *t_list;
    double *p_temp = (double *)malloc(sizeof(double));
    if(p_temp == NULL){
        return NULL;
    }
    *p_temp = temp;
    t_list = mply_findByValue(p_list, DOUBLE, (void *)p_temp);
    free(p_temp);
    return t_list;
}

List *mply_findByString(List* p_list, char *temp) {
    List *t_list;
    char *p_temp = (char *)malloc(sizeof(char)*(strlen(temp) + 1));
    if(p_temp == NULL){
        return NULL;
    }
    strcpy(p_temp, temp);
    t_list = mply_findByValue(p_list, STRING, (void *)p_temp);
    free(p_temp);
    return t_list;
}

List *mply_findByPointer(List* p_list, void *temp) {
    List *t_list = mply_findByValue(p_list, DOUBLE, (void *)temp);
    return t_list;
}

List *mply_findByIntForNode(List* p_list, int temp) {
    int *p_temp = (int *)malloc(sizeof(int));
    if(p_temp == NULL){
        return NULL;
    }
    *p_temp = temp;
    return mply_findByValue(p_list, INT, (void *)p_temp);
}

List *mply_findByDoubleForNode(List* p_list, double temp) {
    double *p_temp = (double *)malloc(sizeof(double));
    if(p_temp == NULL){
        return NULL;
    }
    *p_temp = temp;
    return mply_findByValue(p_list, DOUBLE, (void *)p_temp);
}

List *mply_findByStringForNode(List* p_list, char *temp) {
    char *p_temp = (char *)malloc(sizeof(char) * (strlen(temp) + 1));
    if(p_temp == NULL){
        return NULL;
    }
    strcpy(p_temp, temp);
    return mply_findByValue(p_list, STRING, (void *)p_temp);
}

List *mply_findByPointerForNode(List* p_list, void *temp) {
    return mply_findByValue(p_list, POINTER, (void *)temp);
}

Node *findByIndexForNode(List *p_list, unsigned long long m_index) {
    if(p_list == NULL) return NULL;
#ifdef list_quick_enable
    if(p_list->p_lq != NULL){
        register struct list_quick *p_lq = p_list->p_lq;
        if(p_lq->fn_node != NULL) return getNodeByFnNode(p_list, m_index);
    }
#endif
    Node *p_node = p_list->head;
    unsigned long long i;
    for (i = 0; i < m_index; i++) {
        p_node = p_node->next;
    }
    return p_node;
}
