#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

int releaseStandardData(STD_DATA *p_std){
    releaseListForCustom(p_std->pd_blocklst, (int (*)(void *))releaseSTDBlocks);
    releaseListForCustom(p_std->pd_ctnlst, (int (*)(void *))releaseSTDConnection);
    freeS_id(p_std->s_id);
    free(p_std);
    return 0;
}
