#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std){
    insertInTail(p_dfile->pf_stdlst, nodeWithPointer(p_std,0));
    p_dfile->pf_head->data_num = (uint32_t)p_dfile->pf_stdlst->length;
    return 0;
}
