#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int standardDataAddBlock(STD_DATA *p_std, SID *p_sid ,uint16_t type, void *data, uint32_t data_size){
    if (p_std->lock) return -1;
    STD_BLOCKS *p_stdb = initStandardDBlocks(p_sid, type,data_size);
    dataForStandardDBlock(p_stdb, data);
    insertInTail(p_std->pd_blocklst, nodeWithPointer(p_stdb,0));
    return 0;
}

int standardDataAddConnection(STD_DATA *p_std, SID *f_sid, SID *s_sid){
    if (p_std->lock) return -1;
    STD_CTN *p_stdb = initStandardDConnection(f_sid, s_sid);
    insertInTail(p_std->pd_ctnlst, nodeWithPointer(p_stdb,0));
    return 0;
}
