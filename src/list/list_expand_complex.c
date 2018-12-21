#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>

Node *nodeWithComplex(void) {
    Node *p_node = initNode(0);
    p_node->type = LIST;
    p_node->value = initList(0);
    return p_node;
}

int addValueForComplex(Node * p_node, int type, void *value) {
    List *c_list;
    Node *c_node;
    if (p_node->type == LIST) {
        c_list = (List *)p_node->value;
        c_node = initNode(0);
        initMallocValueForNode(c_node, type, value);
        insertInTail(c_list, c_node);
        return  0;
    }
    return  -1;
}

int addIntForComplex(Node *p_node, int temp) {
    if (p_node->type == LIST) {
        int *p_temp = (int *)malloc(sizeof(int));
        if(p_temp == NULL){
            return -1;
        }
        *p_temp = temp;
        addValueForComplex(p_node, INT, p_temp);
        return 0;
    }
    return -1;
}

int addDoubleForComplex(Node *p_node, double temp) {
    if (p_node->type == LIST) {
        double *p_temp = (double *)malloc(sizeof(double));
        if(p_temp == NULL){
            return -1;
        }
        *p_temp = temp;
        addValueForComplex(p_node, DOUBLE, p_temp);
        return 0;
    }
    return -1;
}

int addStringForComplex(Node *p_node, char *temp) {
    if (p_node->type == LIST) {
        char *p_temp = (char *)malloc(sizeof(strlen(temp) + 1));
        if(p_temp == NULL){
            return -1;
        }
        strcpy(p_temp, temp);
        addValueForComplex(p_node, STRING, p_temp);
        return 0;
    }
    return -1;
}

int addPointerForComplex(Node *p_node, void *temp) {
    if (p_node->type == LIST) {
        addValueForComplex(p_node, POINTER, temp);
        return 0;
    }
    return -1;
}
