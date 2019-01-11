#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int releaseDFile(D_FILE *p_dfile){
    releaseListForCustom(p_dfile->pf_stdlst, (int (*)(void *))releaseStandardData);
    fclose(p_dfile->fp);
    free(p_dfile->pf_head);
    free(p_dfile);
    return 0;
}
