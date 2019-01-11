#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

uint32_t calStandardData(STD_DATA *p_std){
    List *rtn_lst = NULL;
    uint32_t size = 4 + sizeof(unsigned long long) * 2;
    if(p_std->s_id != NULL) size += SID_LEN * sizeof(char);
    rtn_lst = listThrough(p_std->pd_ctnlst, __CALLBACK_CALL(calStandardDataCTN), __SEND_ARG("%d", size));
    if(rtn_lst != NULL){
        size = __RTN_ARGS(rtn_lst, 0, uint32_t);
        releaseList(rtn_lst);
    }
    rtn_lst = listThrough(p_std->pd_blocklst, __CALLBACK_CALL(calStandardDataBLK), __SEND_ARG("%d", size));
    if(rtn_lst != NULL){
        size = __RTN_ARGS(rtn_lst, 0, uint32_t);
        releaseList(rtn_lst);
    }
    return size;
}

__CALLBACK_DEFINE(calStandardDataBLK){
    uint32_t size = __ARGS(0, uint32_t);
    STD_BLOCKS *p_stdb = __VALUE(STD_BLOCKS *);
    if(p_stdb->sid != NULL) size += SID_LEN + sizeof(int32_t);
    else size += sizeof(int32_t);
    size += p_stdb->blocks_num + sizeof(uint16_t) + sizeof(uint32_t);
    //unsigned long long temp = __NOW_INDEX;
    if(__NOW_INDEX == __LIST_LEN - 1){
        return __RETURN("%ull", size);
    }
    return __CRETURN__;
}

void printStandardData(void *value){
    STD_DATA *p_std = (STD_DATA *)value;
    printf("SID:%s\n",p_std->s_id->decrypt_str);
    printf("Loaction:%u\n",p_std->location);
    printf("Size:%u\n",p_std->size);
    printf("Ctn number:%llu\n",p_std->pd_ctnlst->length);
    printf("Blk number:%llu\n",p_std->pd_blocklst->length);
}
