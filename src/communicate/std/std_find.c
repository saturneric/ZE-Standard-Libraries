#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

__CALLBACK_DEFINE(findStandardDataBySid){
    SID *t_sid = __ARGS_P(0, SID);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    if(simFitS_id(p_std->s_id, t_sid)){
        return __RETURN("%p", p_std);
    }
    return __CRETURN__;
}
