#include <type.h>
#include <list/list.h>
#include <list/list_simple.h>

inline s_Node *s_nodeWithInt(int t_int){
    s_Node *s_p_node = s_initNode();
    int *pt_int = malloc(sizeof(int));
    *pt_int = t_int;
    s_p_node->value = pt_int;
    return s_p_node;
}

inline s_Node *s_nodeWithUInt(unsigned int t_uint){
    s_Node *s_p_node = s_initNode();
    unsigned int *pt_uint = malloc(sizeof(unsigned int));
    *pt_uint = t_uint;
    s_p_node->value = pt_uint;
    return s_p_node;
}

inline s_Node *s_nodeWithDouble(double t_double){
    s_Node *s_p_node = s_initNode();
    unsigned int *pt_double = malloc(sizeof(double));
    *pt_double = t_double;
    s_p_node->value = pt_double;
    return s_p_node;
}

inline s_Node *s_nodeWithString(const char *t_string){
    s_Node *s_p_node = s_initNode();
    char *pt_string = malloc(strlen(t_string) + 1);
    strcpy(pt_string, t_string);
    s_p_node->value = pt_string;
    return s_p_node;
}

inline s_Node *s_nodeWithPointer(const void *t_pointer){
    s_Node *s_p_node = s_initNode();
    s_p_node->value = (void *) t_pointer;
    return s_p_node;
}
