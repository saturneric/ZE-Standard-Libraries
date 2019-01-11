#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int releaseSTDConnection(STD_CTN *p_stdc){
    free(p_stdc->f_sid);
    free(p_stdc->s_sid);
    free(p_stdc);
    return 0;
}
