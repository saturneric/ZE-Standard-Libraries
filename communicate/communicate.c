#include "communicate.h"

STD_BLOCKS *initStandardDBlocks(SID *p_sid, unsigned int type, unsigned long long data_size){
    STD_BLOCKS *p_stdb = (STD_BLOCKS *)malloc(sizeof(STD_BLOCKS));
    p_stdb->sid = s_idToASCIIString(p_sid);
    p_stdb->if_data = 0;
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
    return p_stdc;
}

STD_DATA *initStandardData(unsigned int type){
    STD_DATA *p_std = (STD_DATA *)malloc(sizeof(STD_DATA));
    p_std->pd_blocklst = initList();
    p_std->pd_ctnlst = initList();
    p_std->lock = 0;
    p_std->type = type;
    p_std->s_id = getS_id(STANDARD_DATA, 1);
    return p_std;
}

int standardDataAddBlock(STD_DATA *p_std, SID *p_sid ,unsigned int type, void *data, unsigned long long data_size){
    if (p_std->lock) return -1;
    STD_BLOCKS *p_stdb = initStandardDBlocks(p_sid, type,data_size);
    dataForStandardDBlock(p_stdb, data);
    insertInTail(p_std->pd_blocklst, nodeWithPointer(p_stdb));
    return 0;
}

int standardDataAddConnection(STD_DATA *p_std, SID *f_sid, SID *s_sid){
    if (p_std->lock) return -1;
    STD_CTN *p_stdb = initStandardDConnection(f_sid, s_sid);
    insertInTail(p_std->pd_ctnlst, nodeWithPointer(p_stdb));
    return 0;
}

D_FILE *initDataFileForWrite(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "wb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    strcpy(p_dfile->pf_head->head_test,"ZESTDLIB_STDDFILE");
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList();
    return p_dfile;
}

D_FILE *initDataFileForRead(char *route){
    D_FILE *p_dfile = (D_FILE *)malloc(sizeof(D_FILE));
    p_dfile->fp = fopen(route, "rb");
    p_dfile->pf_head = (F_HEAD *)malloc(sizeof(F_HEAD));
    p_dfile->pf_head->data_num = 0;
    p_dfile->pf_stdlst = initList();
    return p_dfile;
}

int dataFileAddStandardData(D_FILE *p_dfile, STD_DATA *p_std){
    insertInTail(p_dfile->pf_stdlst, nodeWithPointer(p_std));
    p_dfile->pf_head->data_num = p_dfile->pf_stdlst->length;
    return 0;
}

int dataFileWriteIn(D_FILE *p_dfile){
    fwrite(p_dfile->pf_head->head_test, sizeof(char), 18, p_dfile->fp);
    fwrite(&p_dfile->pf_head->data_num, sizeof(unsigned long long), 1, p_dfile->fp);
    fwrite("HEAD_END", sizeof(char), 9, p_dfile->fp);
    List *er_list = initList();
    insertInTail(er_list, nodeWithPointer(p_dfile->fp));
    /*fwrite("STDINFO", sizeof(char), 8, p_dfile->fp);
    listThrough(p_dfile->pf_stdlst, _doStandardDataInfoWrite, er_list);*/
    /*fwrite("STDLST", sizeof(char), 7, p_dfile->fp);*/
    listThrough(p_dfile->pf_stdlst, _doStandardDataWrite, er_list);
    releaseList(er_list);
    return 0;
}
List *_doStandardDataInfoWrite(unsigned int type, void *value, List *er_list){
    List *p_rtnlst = initList();
    FILE *fp = getByPointerForNode(findByIndexForNode(er_list, 0));
    STD_DATA *p_std = value;
    insertInTail(p_rtnlst, nodeWithInt(0));
    char *string_sid = s_idToASCIIString(p_std->s_id);
    fwrite(string_sid, sizeof(char), DEEPER_LEN, fp);
    free(string_sid);
    fwrite(&p_std->type, sizeof(unsigned long), 1, fp);
    fwrite(&p_std->pd_ctnlst->length, sizeof(unsigned long long), 1, fp);
    fwrite(&p_std->pd_blocklst->length, sizeof(unsigned long long), 1, fp);
    return p_rtnlst;
}

List *_doStandardDataWrite(unsigned int type, void *value, List *er_list){
    List *p_rtnlst = initList();
    FILE *fp = getByPointerForNode(findByIndexForNode(er_list, 0));
    insertInTail(p_rtnlst, nodeWithInt(0));
    STD_DATA *p_std = value;
    List *erc_list = initList();
    insertInTail(erc_list, nodeWithPointer(fp));
    fwrite("STD", sizeof(char), 4, fp);
    char *string_sid = s_idToASCIIString(p_std->s_id);
    unsigned long sid_len = strlen(string_sid) + 1;
    fwrite(&sid_len, sizeof(unsigned long), 1, fp);
    char *sid_w = s_idToASCIIString(p_std->s_id);
    fwrite(sid_w, sizeof(char), sid_len, fp);
    fwrite(&p_std->type, sizeof(unsigned int), 1, fp);
    fwrite(&p_std->pd_ctnlst->length, sizeof(unsigned long long), 1, fp);
    fwrite(&p_std->pd_blocklst->length, sizeof(unsigned long long), 1, fp);
    listThrough(p_std->pd_ctnlst, _doStandardDConnectionWrite, erc_list);
    listThrough(p_std->pd_blocklst, _doStandardDBlockWrite, erc_list);
    releaseList(erc_list);
    free(sid_w);
    free(string_sid);
    return p_rtnlst;
}

List *_doStandardDConnectionWrite(unsigned int type, void *value, List *er_list){
    List *p_rtnlst = initList();
    insertInTail(p_rtnlst, nodeWithInt(0));
    FILE *fp = getByPointerForNode(findByIndexForNode(er_list, 0));
    STD_CTN *p_stdc = value;
    unsigned long fsid_len = strlen(p_stdc->f_sid) + 1, ssid_len = strlen(p_stdc->s_sid)+1;
    fwrite(&fsid_len, sizeof(unsigned long), 1, fp);
    fwrite(p_stdc->f_sid, sizeof(char), fsid_len, fp);
    fwrite(&ssid_len, sizeof(unsigned long), 1, fp);
    fwrite(p_stdc->s_sid, sizeof(char), ssid_len, fp);
    return p_rtnlst;
}

List *_doStandardDBlockWrite(unsigned int type, void *value, List *er_list){
    List *p_rtnlst = initList();
    insertInTail(p_rtnlst, nodeWithInt(0));
    STD_BLOCKS *p_stdb = value;
    FILE *fp = getByPointerForNode(findByIndexForNode(er_list, 0));
    unsigned long sid_len = strlen(p_stdb->sid)+1, blocks_num = p_stdb->blocks_num;
    fwrite(&sid_len, sizeof(unsigned long), 1, fp);
    fwrite(p_stdb->sid, sizeof(char), sid_len, fp);
    fwrite(&p_stdb->type, sizeof(unsigned int), 1, fp);
    fwrite(&blocks_num, sizeof(unsigned long), 1, fp);
    fwrite(p_stdb->buff, sizeof(char), p_stdb->blocks_num, fp);
    return p_rtnlst;
}

STD_DATA *listToSTD(List *p_list){
    STD_DATA *p_std = initStandardData(LIST);
    Node *p_node = p_list->head;
    while (p_node != NULL) {
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
    char test_info[FILE_TSET_LEN],head_test_info[HEAD_TEST_LEN];
    fread(test_info, sizeof(char), FILE_TSET_LEN, p_dfile->fp);
    strcpy(p_dfile->pf_head->head_test, test_info);
    if(!strcmp(test_info, "ZESTDLIB_STDDFILE")){
        unsigned long long std_num = 0;
        fread(&std_num, sizeof(unsigned long long), 1, p_dfile->fp);
        p_dfile->pf_head->data_num = std_num;
        fread(head_test_info, sizeof(char), 9, p_dfile->fp);
        if (!strcmp(head_test_info, "HEAD_END")) {
            for(int i = 0; i < std_num; i++){
                char std_test_info[4];
                fread(std_test_info, sizeof(char), 4, p_dfile->fp);
                if(!strcmp(std_test_info, "STD")){
                    unsigned long long sid_len = 0, ctn_num = 0, blk_num = 0;
                    unsigned int type = 0;
                    fread(&sid_len, sizeof(unsigned long), 1, p_dfile->fp);
                    char *string_sid = (char *)malloc(sizeof(char) * sid_len);
                    fread(string_sid, sizeof(char), sid_len, p_dfile->fp);
                    fread(&type, sizeof(unsigned int), 1, p_dfile->fp);
                    STD_DATA *p_std = initStandardData(type);
                    freeS_id(p_std->s_id);
                    p_std->s_id = asciiStringToS_id(string_sid);
                    dataFileAddStandardData(p_dfile, p_std);
                    free(string_sid);
                    fread(&ctn_num, sizeof(unsigned long long), 1, p_dfile->fp);
                    fread(&blk_num, sizeof(unsigned long long), 1, p_dfile->fp);
                    for(int j = 0; j < ctn_num; j++){
                        fread(&sid_len, sizeof(unsigned long), 1, p_dfile->fp);
                        char *fstring_sid = (char *)malloc(sizeof(char) * sid_len);
                        fread(fstring_sid, sizeof(char), sid_len, p_dfile->fp);
                        fread(&sid_len, sizeof(unsigned long), 1, p_dfile->fp);
                        char *sstring_sid = (char *)malloc(sizeof(char) * sid_len);
                        fread(sstring_sid, sizeof(char), sid_len, p_dfile->fp);
                        SID *fs_id = asciiStringToS_id(fstring_sid), *ss_id = asciiStringToS_id(sstring_sid);
                        standardDataAddConnection(p_std, fs_id,ss_id);
                        freeS_id(fs_id);
                        freeS_id(ss_id);
                        free(fstring_sid);
                        free(sstring_sid);
                    }
                    for(int k = 0; k < blk_num; k++){
                        fread(&sid_len, sizeof(unsigned long), 1, p_dfile->fp);
                        char *string_sid = (char *)malloc(sizeof(char) * sid_len);
                        fread(string_sid, sizeof(char), sid_len, p_dfile->fp);
                        unsigned long blk_len = 0;
                        fread(&blk_len, sizeof(unsigned long), 1, p_dfile->fp);
                        char *content = (char *)malloc(sizeof(char) * blk_len);
                        fread(content, sizeof(char), blk_len, p_dfile->fp);
                        SID *s_id = asciiStringToS_id(string_sid);
                        unsigned int type = VOID;
                        fread(&type, sizeof(unsigned int), 1, p_dfile->fp);
                        standardDataAddBlock(p_std, s_id, type, content, blk_len);
                        freeS_id(s_id);
                        free(string_sid);
                        free(content);
                    }
                    return  0;
                }
                else break;
            }
        }
        else{
            
        }
    }
    showError(pushError(DATA_FILE, STANDARD, initInfo("dataFileReadOut()", "Datafile not complete.")));
    return -1;
}

int releaseSTDConnection(STD_CTN *p_stdc){
    free(p_stdc->f_sid);
    free(p_stdc->s_sid);
    free(p_stdc);
    return 0;
}

int releaseSTDBlocks(STD_BLOCKS *p_stdb){
    free(p_stdb->sid);
    free(p_stdb->buff);
    free(p_stdb);
    return 0;
}

int releaseStandardData(STD_DATA *p_std){
    freeS_id(p_std->s_id);
    releaseListForCustom(p_std->pd_blocklst, (int (*)(void *))releaseSTDBlocks);
    releaseListForCustom(p_std->pd_ctnlst, (int (*)(void *))releaseSTDConnection);
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
    List *p_list = initList();
    List *er_list = initList();
    insertInTail(er_list, nodeWithPointer(er_list));
    listThrough(p_std->pd_blocklst, _doStandardDataToList, er_list);
    return p_list;
}

List *_doStandardDataToList(unsigned int type, void *value, List *er_list){
    List *rtn_list = initList();
    insertInTail(rtn_list, nodeWithInt(0));
    List *p_list = getByPointerForNode(findByIndexForNode(er_list, 0));
    STD_BLOCKS *p_stdb = value;
    Node *p_node = initNode();
    p_node->s_id = asciiStringToS_id(p_stdb->sid);
    p_node->type = p_stdb->type;
    p_node->value = malloc(sizeof(p_stdb->blocks_num));
    memcpy(p_node->value, p_stdb->buff, sizeof(p_stdb->blocks_num));
    insertInTail(p_list, p_node);
    return rtn_list;
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
