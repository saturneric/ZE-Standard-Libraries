#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

int releaseSTDBlocks(STD_BLOCKS *p_stdb){
    free(p_stdb->buff);
    free(p_stdb->sid);
    free(p_stdb);
    return 0;
}
