#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

int releaseSTDConnection(STD_CTN *p_stdc){
    free(p_stdc->f_sid);
    free(p_stdc->s_sid);
    free(p_stdc);
    return 0;
}
