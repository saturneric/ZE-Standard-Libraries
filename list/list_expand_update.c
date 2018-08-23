#include <type.h>
#include <list/list.h>
#include <list/list_expand.h>

int updateValueWithIntForNode(Node *p_node,int value){
    int *p_value = (int *)malloc(sizeof(int));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithULLIntForNode(Node *p_node, unsigned long long value){
    unsigned long long *p_value = (unsigned long long *)malloc(sizeof(unsigned long long));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithDoubleForNode(Node *p_node, double value){
    double *p_value = (double *)malloc(sizeof(double));
    if(p_value == NULL){
        return -1;
    }
    *p_value = value;
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithStringForNode(Node *p_node, char *string){
    char *p_value = (char *)malloc(sizeof(strlen(string)) + 1);
    if(p_value == NULL){
        return -1;
    }
    strcpy(p_value, string);
    free(p_node->value);
    p_node->value = p_value;
    return 0;
}

int updateValueWithPointerForNode(Node *p_node, void *pointer){
    free(p_node->value);
    p_node->value = pointer;
    return 0;
}
