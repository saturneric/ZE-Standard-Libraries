#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

STD_DATA *listToSTD(List *p_list){
    Node *p_node = p_list->head;
    STD_DATA *p_std = NULL;
    if (p_list->s_id != NULL){
        p_std = initStandardData(LIST,p_list->s_id);
    }
    else p_std = initStandardData(LIST, NULL);
    while (p_node != NULL) {
        if(p_node->type == HOLE) continue;
        uint32_t data_size = 0;
        if(p_node->type == INT) data_size = sizeof(int);
        else if (p_node->type == DOUBLE) data_size = sizeof(double);
        else if (p_node->type == STRING) data_size = (uint32_t)strlen((char *)p_node->value) + 1;
        else data_size = sizeof(void *);
        standardDataAddBlock(p_std, p_node->s_id, p_node->type, p_node->value, data_size);
        p_node = p_node->next;
    }
    return p_std;
}
