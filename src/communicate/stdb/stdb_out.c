#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

__CALLBACK_DEFINE(StandardDBlockWrite){
    STD_BLOCKS *p_stdb = value;
    FILE *fp = __ARGS_P(0, FILE);
    unsigned long blocks_num = p_stdb->blocks_num;
    int if_sid = 0;
    if(p_stdb->sid != NULL){
        if_sid = 1;
        fwrite(&if_sid, sizeof(int), 1, fp);
        fwrite(p_stdb->sid, sizeof(char), SID_LEN, fp);
    }
    else{
        fwrite(&if_sid, sizeof(int), 1, fp);
    }
    fwrite(&p_stdb->type, sizeof(uint16_t), 1, fp);
    fwrite(&blocks_num, sizeof(uint32_t), 1, fp);
    fwrite(p_stdb->buff, sizeof(char), p_stdb->blocks_num, fp);
    return __CRETURN__;
}
