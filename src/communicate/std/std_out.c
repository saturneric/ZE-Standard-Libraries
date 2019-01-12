#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>


__CALLBACK_DEFINE(StandardDataInfoWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    fwrite(p_std->s_id->decrypt_str, sizeof(char), SID_LEN, fp);
    fwrite(&p_std->type, sizeof(uint16_t), 1, fp);
    uint32_t std_size = calStandardData(p_std);
    p_std->size = std_size;
    fwrite(&std_size, sizeof(uint32_t), 1, fp);
    return __CRETURN__;
}

__CALLBACK_DEFINE(StandardDataWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    fwrite("STD", sizeof(char), 4, fp);
    fwrite(p_std->s_id->decrypt_str, sizeof(char), SID_LEN, fp);
    fwrite(&p_std->pd_ctnlst->length, sizeof(uint32_t), 1, fp);
    fwrite(&p_std->pd_blocklst->length, sizeof(uint32_t), 1, fp);
    listThrough(p_std->pd_ctnlst, __CALLBACK_CALL(StandardDConnectionWrite), __SEND_ARG("%p", fp));
    listThrough(p_std->pd_blocklst, __CALLBACK_CALL(StandardDBlockWrite), __SEND_ARG("%p", fp));
    return __CRETURN__;
}
