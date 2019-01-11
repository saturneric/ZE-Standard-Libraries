#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std){
    insertInTail(p_dfile->pf_stdlst, nodeWithPointer(p_std,0));
    p_dfile->pf_head->data_num = (uint32_t)p_dfile->pf_stdlst->length;
    return 0;
}
