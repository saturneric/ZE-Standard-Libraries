#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int dataFileWriteIn(D_FILE *p_dfile){
    fwrite(p_dfile->pf_head->head_test, sizeof(char), 18, p_dfile->fp);
    fwrite(&p_dfile->pf_head->data_num, sizeof(uint32_t), 1, p_dfile->fp);
    fwrite("STDINFO", sizeof(char), 8, p_dfile->fp);
    listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(StandardDataInfoWrite), __SEND_ARG("%p", p_dfile->fp));
    fwrite("STDLST", sizeof(char), 7, p_dfile->fp);
    listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(StandardDataWrite), __SEND_ARG("%p", p_dfile->fp));
    return 0;
}
