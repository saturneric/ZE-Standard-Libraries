#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int releaseSTDBlocks(STD_BLOCKS *p_stdb){
    free(p_stdb->buff);
    free(p_stdb->sid);
    free(p_stdb);
    return 0;
}
