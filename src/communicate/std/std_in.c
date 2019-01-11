#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

int readStandardData(D_FILE *p_dfile,STD_DATA *p_std){
    char s_id[SID_LEN],std_text[STD_TEXT_LEN];
    fseek(p_dfile->fp, p_std->location, SEEK_SET);
    fread(std_text, sizeof(char), STD_TEXT_LEN, p_dfile->fp);
    if(strcmp(std_text, "STD")) return -1;
    fread(s_id, sizeof(char), SID_LEN, p_dfile->fp);
    
    if(!strcmp(s_id, p_std->s_id->decrypt_str)){
        uint32_t ctn_num = 0, blk_num = 0;
        fread(&ctn_num, sizeof(uint32_t), 1, p_dfile->fp);
        fread(&blk_num, sizeof(uint32_t), 1, p_dfile->fp);
        for(int i = 0; i < ctn_num; i++){
            SID *fs_id = NULL, *ss_id = NULL;
            char t_sid[SID_LEN];
            fread(t_sid, sizeof(char), SID_LEN, p_dfile->fp);
            fs_id = setS_idWithString(t_sid);
            fread(t_sid, sizeof(char), SID_LEN, p_dfile->fp);
            ss_id = setS_idWithString(t_sid);
            standardDataAddConnection(p_std, fs_id, ss_id);
            freeS_id(fs_id);
            freeS_id(ss_id);
        }
        for(int i = 0; i < blk_num; i++){
            int if_sid = 0;
            uint16_t type = VOID;
            uint32_t blk_size = 0;
            char t_sid[SID_LEN];
            fread(&if_sid, sizeof(int32_t), 1, p_dfile->fp);
            if(if_sid){
                fread(t_sid, sizeof(char), SID_LEN, p_dfile->fp);
            }
            fread(&type, sizeof(int32_t), 1, p_dfile->fp);
            fread(&blk_size, sizeof(uint32_t), 1, p_dfile->fp);
            char *buff = malloc(sizeof(char) * blk_size);
            fread(buff, sizeof(char), blk_size, p_dfile->fp);
            SID *sb_sid = NULL;
            if (if_sid) setS_idWithString(t_sid);
            standardDataAddBlock(p_std, sb_sid, type, buff, blk_size);
            free(buff);
            freeS_id(sb_sid);
        }
    }
    p_std->read_data = 1;
    return 0;
}

int readStandardDataBySid(D_FILE *p_dfile, SID *p_sid){
    List *rtn = listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(findStandardDataBySid), __SEND_ARG("%p", p_sid));
    //STD_DATA *p_std = __RTN_ARGS_P(rtn, 0, STD_DATA);
    releaseList(rtn);
    //if(p_std != NULL) readStandardData(p_dfile, p_std);
    return 0;
}
