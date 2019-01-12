#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

int releaseDFile(D_FILE *p_dfile){
    releaseListForCustom(p_dfile->pf_stdlst, (int (*)(void *))releaseStandardData);
    fclose(p_dfile->fp);
    free(p_dfile->pf_head);
    free(p_dfile);
    return 0;
}
