#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

D_FILE *initDataFileForWrite(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "wb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    strcpy(p_dfile->pf_head->head_test,"ZESTDLIB_STDDFILE");
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList(0);
    return p_dfile;
}

D_FILE *initDataFileForRead(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "rb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList(0);
    return p_dfile;
}
