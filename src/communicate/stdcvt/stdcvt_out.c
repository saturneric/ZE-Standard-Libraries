#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

List *standardDataToList(STD_DATA *p_std){
    List *p_list = initList(0);
    listThrough(p_std->pd_blocklst, __CALLBACK_CALL(StandardDataToList), __SEND_ARG("%p", p_list));
    return p_list;
}

__CALLBACK_DEFINE(StandardDataToList){
    List *p_list = __ARGS_P(0, List);
    STD_BLOCKS *p_stdb = __VALUE(STD_BLOCKS *);
    Node *p_node = initNode(0);
    p_node->s_id = setS_idWithString(p_stdb->sid);
    p_node->type = p_stdb->type;
    p_node->value = malloc(sizeof(p_stdb->blocks_num));
    memcpy(p_node->value, p_stdb->buff, sizeof(p_stdb->blocks_num));
    insertInTail(p_list, p_node);
    return __CRETURN__;
}
