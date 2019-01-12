#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

__CALLBACK_DEFINE(findStandardDataBySid){
    SID *t_sid = __ARGS_P(0, SID);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    if(simFitS_id(p_std->s_id, t_sid)){
        return __RETURN("%p", p_std);
    }
    return __CRETURN__;
}
