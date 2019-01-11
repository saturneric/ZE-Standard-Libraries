#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>


__CALLBACK_DEFINE(StandardDConnectionWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_CTN *p_stdc = __VALUE(STD_CTN *);
    fwrite(p_stdc->f_sid, sizeof(char), SID_LEN, fp);
    fwrite(p_stdc->s_sid, sizeof(char), SID_LEN, fp);
    return __CRETURN__;
}
