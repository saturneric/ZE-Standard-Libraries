#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int checkIfDataFile(D_FILE *p_dfile){
    char test_info[FILE_TSET_LEN];
    fread(test_info, sizeof(char), FILE_TSET_LEN, p_dfile->fp);
    strcpy(p_dfile->pf_head->head_test, test_info);
    if(!strcmp(test_info, "ZESTDLIB_STDDFILE"))return 1;
    return 0;
}
