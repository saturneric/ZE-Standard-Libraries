#include <type.h>
#include <list/list_type.h>

unsigned long long calListMemory(List * p_list){
    Node *p_node = p_list->head;
    unsigned long long nodes_size = 0LL;
    unsigned long long list_size = sizeof(p_list);
    while(p_node != NULL){
        nodes_size += sizeof(p_node);
        p_node = p_node->next;
    }
    return  list_size + nodes_size;
}
