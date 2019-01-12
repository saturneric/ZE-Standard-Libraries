#include <type.h>
#include <id/id.h>
#include <chain/chain.h>
#include <event/event.h>
#include <communicate/communicate_file.h>


int dataFileReadOut(D_FILE *p_dfile){
    if(!readDataFileInfo(p_dfile)){
        listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(dataFileReadOut), __SEND_ARG("%p", p_dfile));
    }
    return -1;
}

__CALLBACK_DEFINE(dataFileReadOut){
    D_FILE *p_dfile = __ARGS_P(0, D_FILE);
    readStandardData(p_dfile, __VALUE(STD_DATA *));
    return __CRETURN__;
}

int readDataFileInfo(D_FILE *p_dfile){
    if(checkIfDataFile(p_dfile)){
        uint32_t std_num = 0,std_size;
        uint16_t std_type = VOID;
        char info_begin[INFO_TEST_LEN], s_id[SID_LEN];
        uint32_t location = 0;
        fread(&std_num, sizeof(uint32_t), 1, p_dfile->fp);
        fread(info_begin, sizeof(char),INFO_TEST_LEN,p_dfile->fp);
        location += INFO_TEST_LEN + sizeof(uint32_t) + FILE_TSET_LEN;
        if(!strcmp(info_begin, "STDINFO")){
            location += std_num * 45 + 7;
            for(int i = 0; i < std_num; i++){
                fread(s_id, sizeof(char), SID_LEN, p_dfile->fp);
                fread(&std_type, sizeof(uint16_t), 1, p_dfile->fp);
                fread(&std_size, sizeof(uint32_t), 1, p_dfile->fp);
                SID *temp_sid = setS_idWithString(s_id);
                STD_DATA *p_std = initStandardData(std_type,temp_sid);
                freeS_id(temp_sid);
                p_std->size = std_size;
                p_std->type = std_type;
                p_std->location = location;
                dataFileAddStandardData(p_dfile, p_std);
                location += std_size;
            }
        }
    }
    return 0;
}

