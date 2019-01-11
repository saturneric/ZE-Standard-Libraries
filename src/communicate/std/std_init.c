#include <id/id.h>
#include <list/list.h>
#include <list/list_expand.h>
#include <list/list_expand_1.h>
#include <communicate/communicate_file.h>

STD_CTN *initStandardDConnection(SID *f_sid, SID *s_sid){
    STD_CTN *p_stdc = (STD_CTN *)malloc(sizeof(STD_CTN));
    p_stdc->f_sid = s_idToASCIIString(f_sid);
    p_stdc->s_sid = s_idToASCIIString(s_sid);
    p_stdc->location = 0;
    return p_stdc;
}

STD_DATA *initStandardData(uint16_t type, SID *s_id){
    STD_DATA *p_std = (STD_DATA *)malloc(sizeof(STD_DATA));
    p_std->pd_blocklst = initList(0);
    p_std->pd_ctnlst = initList(0);
    p_std->lock = 0;
    p_std->type = type;
    p_std->size = 0;
    p_std->location = 0;
    p_std->read_data = 0;
    
    if(s_id == NULL) p_std->s_id = getS_id(STANDARD_DATA, 2);
    else p_std->s_id = copyS_id(s_id);
    setSidToASCIIString(p_std->s_id);
    return p_std;
}


