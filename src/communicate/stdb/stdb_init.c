#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>

STD_BLOCKS *initStandardDBlocks(SID *p_sid, uint16_t type, uint32_t data_size){
    STD_BLOCKS *p_stdb = (STD_BLOCKS *)malloc(sizeof(STD_BLOCKS));
    if(p_sid != NULL){
        p_stdb->sid = s_idToASCIIString(p_sid);
    }
    else p_stdb->sid = NULL;
    p_stdb->if_data = 0;
    p_stdb->location = 0;
    uint32_t blocks_num = (uint32_t)(data_size/sizeof(char));
    p_stdb->blocks_num = blocks_num;
    p_stdb->type = type;
    p_stdb->buff = (char *)malloc(sizeof(char) * blocks_num);
    return p_stdb;
}

int dataForStandardDBlock(STD_BLOCKS *p_stdb,void *data){
    char *t_data = (char *)data;
    /*unsigned int data_size = sizeof(data);*/
    for(int i = 0; i < p_stdb->blocks_num; i++){
        p_stdb->buff[i] = t_data[i];
    }
    p_stdb->if_data = 1;
    return 0;
}
