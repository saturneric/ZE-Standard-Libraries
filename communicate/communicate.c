#include "communicate.h"

STD_BLOCKS *initStandardDBlocks(SID *p_sid, unsigned int type, unsigned long long data_size){
    STD_BLOCKS *p_stdb = (STD_BLOCKS *)malloc(sizeof(STD_BLOCKS));
    if(p_sid != NULL){
        p_stdb->sid = s_idToASCIIString(p_sid);
    }
    else p_stdb->sid = NULL;
    p_stdb->if_data = 0;
    p_stdb->location = 0;
    unsigned int blocks_num = (unsigned int)(data_size/sizeof(char));
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

STD_CTN *initStandardDConnection(SID *f_sid, SID *s_sid){
    STD_CTN *p_stdc = (STD_CTN *)malloc(sizeof(STD_CTN));
    p_stdc->f_sid = s_idToASCIIString(f_sid);
    p_stdc->s_sid = s_idToASCIIString(s_sid);
    p_stdc->location = 0;
    return p_stdc;
}

STD_DATA *initStandardData(unsigned int type, SID *s_id){
    STD_DATA *p_std = (STD_DATA *)malloc(sizeof(STD_DATA));
    p_std->pd_blocklst = initList(0);
    p_std->pd_ctnlst = initList(0);
    p_std->lock = 0;
    p_std->type = type;
    p_std->size = 0;
    p_std->location = 0;
    
    if(s_id == NULL) p_std->s_id = getS_id(STANDARD_DATA, 2);
    else p_std->s_id = copyS_id(s_id);
    setSidToASCIIString(p_std->s_id);
    return p_std;
}

int standardDataAddBlock(STD_DATA *p_std, SID *p_sid ,unsigned int type, void *data, unsigned long long data_size){
    if (p_std->lock) return -1;
    STD_BLOCKS *p_stdb = initStandardDBlocks(p_sid, type,data_size);
    dataForStandardDBlock(p_stdb, data);
    insertInTail(p_std->pd_blocklst, nodeWithPointer(p_stdb,0));
    return 0;
}

int standardDataAddConnection(STD_DATA *p_std, SID *f_sid, SID *s_sid){
    if (p_std->lock) return -1;
    STD_CTN *p_stdb = initStandardDConnection(f_sid, s_sid);
    insertInTail(p_std->pd_ctnlst, nodeWithPointer(p_stdb,0));
    return 0;
}

D_FILE *initDataFileForWrite(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "wb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    strcpy(p_dfile->pf_head->head_test,"ZESTDLIB_STDDFILE");
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList(0);
    return p_dfile;
}

D_FILE *initDataFileForRead(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "rb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList(0);
    return p_dfile;
}

int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std){
    insertInTail(p_dfile->pf_stdlst, nodeWithPointer(p_std,0));
    p_dfile->pf_head->data_num = p_dfile->pf_stdlst->length;
    return 0;
}

int dataFileWriteIn(D_FILE *p_dfile){
    fwrite(p_dfile->pf_head->head_test, sizeof(char), 18, p_dfile->fp);
    fwrite(&p_dfile->pf_head->data_num, sizeof(unsigned long long), 1, p_dfile->fp);
    fwrite("STDINFO", sizeof(char), 8, p_dfile->fp);
    listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(StandardDataInfoWrite), __SEND_ARG("%p", p_dfile->fp));
    fwrite("STDLST", sizeof(char), 7, p_dfile->fp);
    listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(StandardDataWrite), __SEND_ARG("%p", p_dfile->fp));
    return 0;
}

__CALLBACK_DEFINE(StandardDataInfoWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    fwrite(p_std->s_id->decrypt_str, sizeof(char), SID_LEN, fp);
    fwrite(&p_std->type, sizeof(unsigned int), 1, fp);
    unsigned long long std_size = calStandardData(p_std);
    p_std->size = std_size;
    fwrite(&std_size, sizeof(unsigned long long), 1, fp);
    return __CRETURN__;
}

__CALLBACK_DEFINE(StandardDataWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    fwrite("STD", sizeof(char), 4, fp);
    fwrite(p_std->s_id->decrypt_str, sizeof(char), SID_LEN, fp);
    fwrite(&p_std->pd_ctnlst->length, sizeof(unsigned long long), 1, fp);
    fwrite(&p_std->pd_blocklst->length, sizeof(unsigned long long), 1, fp);
    listThrough(p_std->pd_ctnlst, __CALLBACK_CALL(StandardDConnectionWrite), __SEND_ARG("%p", fp));
    listThrough(p_std->pd_blocklst, __CALLBACK_CALL(StandardDBlockWrite), __SEND_ARG("%p", fp));
    return __CRETURN__;
}

__CALLBACK_DEFINE(StandardDConnectionWrite){
    FILE *fp = __ARGS_P(0, FILE);
    STD_CTN *p_stdc = __VALUE(STD_CTN *);
    fwrite(p_stdc->f_sid, sizeof(char), SID_LEN, fp);
    fwrite(p_stdc->s_sid, sizeof(char), SID_LEN, fp);
    return __CRETURN__;
}

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
    fwrite(&p_stdb->type, sizeof(unsigned int), 1, fp);
    fwrite(&blocks_num, sizeof(unsigned long), 1, fp);
    fwrite(p_stdb->buff, sizeof(char), p_stdb->blocks_num, fp);
    return __CRETURN__;
}

STD_DATA *listToSTD(List *p_list){
    Node *p_node = p_list->head;
    STD_DATA *p_std = NULL;
    if (p_list->s_id != NULL){
        p_std = initStandardData(LIST,p_list->s_id);
    }
    else p_std = initStandardData(LIST, NULL);
    while (p_node != NULL) {
        if(p_node->type == HOLE) continue;
        unsigned long long data_size = 0;
        if(p_node->type == INT) data_size = sizeof(int);
        else if (p_node->type == DOUBLE) data_size = sizeof(double);
        else if (p_node->type == STRING) data_size = strlen((char *)p_node->value) + 1;
        else data_size = sizeof(void *);
        standardDataAddBlock(p_std, p_node->s_id, p_node->type, p_node->value, data_size);
        p_node = p_node->next;
    }
    return p_std;
}

int dataFileReadOut(D_FILE *p_dfile){
    if(!readDataFileInfo(p_dfile)){
        listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(dataFileReadOut), __SEND_ARG("%p", p_dfile));
        
    }
    showError(pushError(DATA_FILE, STANDARD, initInfo("dataFileReadOut()", "Datafile not complete.")));
    return -1;
}

__CALLBACK_DEFINE(dataFileReadOut){
    D_FILE *p_dfile = __ARGS_P(0, D_FILE);
    readStandardData(p_dfile, __VALUE(STD_DATA *));
    return __CRETURN__;
}

int releaseSTDConnection(STD_CTN *p_stdc){
    free(p_stdc->f_sid);
    free(p_stdc->s_sid);
    free(p_stdc);
    return 0;
}

int releaseSTDBlocks(STD_BLOCKS *p_stdb){
    free(p_stdb->buff);
    free(p_stdb->sid);
    free(p_stdb);
    return 0;
}

int releaseStandardData(STD_DATA *p_std){
    releaseListForCustom(p_std->pd_blocklst, (int (*)(void *))releaseSTDBlocks);
    releaseListForCustom(p_std->pd_ctnlst, (int (*)(void *))releaseSTDConnection);
    freeS_id(p_std->s_id);
    free(p_std);
    return 0;
}

int releaseDFile(D_FILE *p_dfile){
    releaseListForCustom(p_dfile->pf_stdlst, (int (*)(void *))releaseStandardData);
    fclose(p_dfile->fp);
    free(p_dfile->pf_head);
    free(p_dfile);
    return 0;
}

List *standardDataToList(STD_DATA *p_std){
    List *p_list = initList(0);
    listThrough(p_std->pd_blocklst, __CALLBACK_CALL(StandardDataToList), __SEND_ARG("%p", p_list));
    return p_list;
}

__CALLBACK_DEFINE(StandardDataToList){
    List *p_list = __ARGS_P(0, List);
    STD_BLOCKS *p_stdb = __VALUE(STD_BLOCKS *);
    Node *p_node = initNode(0);
    p_node->s_id = setS_idWithString(p_stdb->sid);
    p_node->type = p_stdb->type;
    p_node->value = malloc(sizeof(p_stdb->blocks_num));
    memcpy(p_node->value, p_stdb->buff, sizeof(p_stdb->blocks_num));
    insertInTail(p_list, p_node);
    return __CRETURN__;
}

unsigned long long calStandardData(STD_DATA *p_std){
    List *rtn_lst = NULL;
    unsigned long long size = 4 + sizeof(unsigned long long) * 2;
    if(p_std->s_id != NULL) size += SID_LEN * sizeof(char);
    rtn_lst = listThrough(p_std->pd_ctnlst, __CALLBACK_CALL(calStandardDataCTN), __SEND_ARG("%d", size));
    if(rtn_lst != NULL){
        size = __RTN_ARGS(rtn_lst, 0, unsigned long long);
        releaseList(rtn_lst);
    }
    rtn_lst = listThrough(p_std->pd_blocklst, __CALLBACK_CALL(calStandardDataBLK), __SEND_ARG("%d", size));
    if(rtn_lst != NULL){
        size = __RTN_ARGS(rtn_lst, 0, unsigned long long);
        releaseList(rtn_lst);
    }
    return size;
}

__CALLBACK_DEFINE(calStandardDataCTN){
    unsigned long long size = __ARGS(0, unsigned long long);
    size += 64;
    //unsigned long long temp = __NOW_INDEX;
    if(__NOW_INDEX == __LIST_LEN - 1){
        __RETURN("%ull", size);
    }
    return __CRETURN__;
}

__CALLBACK_DEFINE(calStandardDataBLK){
    unsigned long long size = __ARGS(0, unsigned long long);
    STD_BLOCKS *p_stdb = __VALUE(STD_BLOCKS *);
    if(p_stdb->sid != NULL) size += SID_LEN + sizeof(int);
    else size += sizeof(int);
    size += p_stdb->blocks_num + sizeof(unsigned int) + sizeof(unsigned long);
    //unsigned long long temp = __NOW_INDEX;
    if(__NOW_INDEX == __LIST_LEN - 1){
        return __RETURN("%ull", size);
    }
    return __CRETURN__;
}

MSG *createMessage(char *title, void *data, unsigned long data_size){
    MSG *p_msg = malloc(sizeof(MSG) + data_size);
    p_msg->p_sid = getS_id(MESSAGE, 1);
    p_msg->time = time(NULL);
    return p_msg;
}

/*int sendMessageIPv4(MSG *p_msg, char *ip, unsigned int port){
    int client_sockfd;
    struct sockaddr_in remote_addr;
    char buf[BUFSIZ];
    memcpy(buf, "ZEMSG", 5);
    memset(&remote_addr,0,sizeof(remote_addr));
    remote_addr.sin_family=AF_INET;
    remote_addr.sin_addr.s_addr=inet_addr(ip);
    remote_addr.sin_port=htons(port);
    client_sockfd=socket(PF_INET,SOCK_STREAM,0);
    connect(client_sockfd,(struct sockaddr *)&remote_addr,sizeof(struct sockaddr));
    send(client_sockfd,buf,strlen(buf),0);
    unsigned long bkmsg_len = 0;
    bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
    buf[bkmsg_len] = '\0';
    if(!strcmp(buf, "TITLE_REV_READY")){
        memcpy(buf, p_msg->titile, strlen(p_msg->titile));
        bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
        buf[bkmsg_len] = '\0';
        if(!strcmp(buf, "CONTENT_LEN_REV_READY")){
            memcpy(buf, (char *)p_msg->size, sizeof(unsigned int));
            send(client_sockfd,buf,sizeof(unsigned int),0);
            bkmsg_len = recv(client_sockfd, buf, BUFSIZ, 0);
            buf[bkmsg_len] = '\0';
            if(!strcmp(buf, "CONTENT_REV_READY")){
                memcpy(buf, p_msg->content, p_msg->size);
                send(client_sockfd,buf,p_msg->size,0);
                close(client_sockfd);
                return 0;
            }
        }
    }
    close(client_sockfd);
    return -1;
}*/

int readDataFileInfo(D_FILE *p_dfile){
    if(checkIfDataFile(p_dfile)){
        unsigned long long std_num = 0,std_size;
        unsigned int std_type = VOID;
        char info_begin[INFO_TEST_LEN], s_id[SID_LEN];
        unsigned long long location = 0;
        fread(&std_num, sizeof(unsigned long long), 1, p_dfile->fp);
        fread(info_begin, sizeof(char),INFO_TEST_LEN,p_dfile->fp);
        location += INFO_TEST_LEN + sizeof(unsigned long long) + FILE_TSET_LEN;
        if(!strcmp(info_begin, "STDINFO")){
            location += std_num * 45 + 7;
            for(int i = 0; i < std_num; i++){
                fread(s_id, sizeof(char), SID_LEN, p_dfile->fp);
                fread(&std_type, sizeof(unsigned int), 1, p_dfile->fp);
                fread(&std_size, sizeof(unsigned long long), 1, p_dfile->fp);
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

int readStandardData(D_FILE *p_dfile,STD_DATA *p_std){
    char s_id[SID_LEN],std_text[STD_TEXT_LEN];
    fseek(p_dfile->fp, p_std->location, SEEK_SET);
    fread(std_text, sizeof(char), STD_TEXT_LEN, p_dfile->fp);
    if(strcmp(std_text, "STD")) return -1;
    fread(s_id, sizeof(char), SID_LEN, p_dfile->fp);
    
    if(!strcmp(s_id, p_std->s_id->decrypt_str)){
        unsigned long long ctn_num = 0, blk_num = 0;
        fread(&ctn_num, sizeof(unsigned long long), 1, p_dfile->fp);
        fread(&blk_num, sizeof(unsigned long long), 1, p_dfile->fp);
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
            unsigned int type = VOID;
            unsigned long blk_size = 0;
            char t_sid[SID_LEN];
            fread(&if_sid, sizeof(int), 1, p_dfile->fp);
            if(if_sid){
                fread(t_sid, sizeof(char), SID_LEN, p_dfile->fp);
            }
            fread(&type, sizeof(int), 1, p_dfile->fp);
            fread(&blk_size, sizeof(unsigned long), 1, p_dfile->fp);
            char *buff = malloc(sizeof(char) * blk_size);
            fread(buff, sizeof(char), blk_size, p_dfile->fp);
            SID *sb_sid = NULL;
            if (if_sid) setS_idWithString(t_sid);
            standardDataAddBlock(p_std, sb_sid, type, buff, blk_size);
            free(buff);
            freeS_id(sb_sid);
        }
    }
    return 0;
}

int checkIfDataFile(D_FILE *p_dfile){
    char test_info[FILE_TSET_LEN];
    fread(test_info, sizeof(char), FILE_TSET_LEN, p_dfile->fp);
    strcpy(p_dfile->pf_head->head_test, test_info);
    if(!strcmp(test_info, "ZESTDLIB_STDDFILE"))return 1;
    return 0;
}

void printStandardData(void *value){
    STD_DATA *p_std = (STD_DATA *)value;
    printf("SID:%s\n",p_std->s_id->decrypt_str);
    printf("Loaction:%llu\n",p_std->location);
    printf("Size:%llu\n",p_std->size);
    printf("Ctn number:%llu\n",p_std->pd_ctnlst->length);
    printf("Blk number:%llu\n",p_std->pd_blocklst->length);
}

int readStandardDataBySid(D_FILE *p_dfile, SID *p_sid){
    List *rtn = listThrough(p_dfile->pf_stdlst, __CALLBACK_CALL(findStandardDataBySid), __SEND_ARG("%p", p_sid));
    //STD_DATA *p_std = __RTN_ARGS_P(rtn, 0, STD_DATA);
    releaseList(rtn);
    //if(p_std != NULL) readStandardData(p_dfile, p_std);
    return 0;
}

__CALLBACK_DEFINE(findStandardDataBySid){
    SID *t_sid = __ARGS_P(0, SID);
    STD_DATA *p_std = __VALUE(STD_DATA *);
    if(simFitS_id(p_std->s_id, t_sid)){
        return __RETURN("%p", p_std);
    }
    return __CRETURN__;
}
