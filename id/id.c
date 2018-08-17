#include "id.h"

static _Bool if_rand = 0;

void init_rand(void) {
    srand((unsigned)time(NULL));
}

unsigned long long getId(void) {
    int i;
    unsigned long long id = 0;
    id = ((rand() % 9) + 1);
    for (i = 0; i < 15; i++) {
        id *= 10;
        id += rand() % 10;
    }
    return id;
}

SID *initS_id(unsigned int deep_level){
    if (!if_rand) init_rand();
    SID *p_sid = (SID *) malloc(sizeof(SID));
    if(p_sid == NULL){
        printf("\ninitS_id(): Error in getting the memory of sid.\n");
    }
    p_sid->sr = malloc(sizeof(struct sid_raw));
    p_sid->sr->type = VOID;
    p_sid->deep = deep_level;
    p_sid->sr->value = NULL;
    p_sid->sr->value_deeper = NULL;
    p_sid->sr->value_deepest = NULL;
    p_sid->md5 = NULL;
    return p_sid;
}

void getRawS_id(SID *p_sid, unsigned int type, unsigned int deep_level){
    if (deep_level > 0) {
        p_sid->sr->value = (unsigned int *)malloc(sizeof(unsigned int)*DEEPC_LEN);
        if(p_sid->sr->value == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value.\n");
        }
    }
    if (deep_level > 1){
        p_sid->sr->value_deeper = (unsigned int *)malloc(sizeof(unsigned int)*DEEPB_LEN);
        if(p_sid->sr->value_deeper == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value_deeper.\n");
        }
    }
    if (deep_level > 2){
        p_sid->sr->value_deepest = (unsigned int *)malloc(sizeof(unsigned int)*DEEPA_LEN);
        if(p_sid->sr->value_deepest == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value_deepest.\n");
        }
    }
    p_sid->sr->type = type;
    if(deep_level > 0){
        for(register int i = 0; i < DEEPC_LEN; i++) p_sid->sr->value[i] = rand()%65535;
        if(deep_level > 1) for(register int i = 0; i < DEEPB_LEN; i++) p_sid->sr->value_deeper[i] = rand()%65535;
        if (deep_level > 2) for(register int i = 0; i < DEEPA_LEN; i++) p_sid->sr->value_deepest[i] = rand()%65535;
    }
}

SID *getS_id(unsigned int type, unsigned int deep_level){
    SID *p_sid = initS_id(deep_level);
    getRawS_id(p_sid, type, deep_level);
    s_idToMD5(p_sid);
    return p_sid;
}

int fitS_id(SID * const fs_id, SID * const ss_id){
    if(fs_id->decrypt_str == NULL) s_idToASCIIString(fs_id);
    if(ss_id->decrypt_str == NULL) s_idToASCIIString(ss_id);
    return strcmp(fs_id->decrypt_str, ss_id->decrypt_str);
}

int simFitS_id(SID * fs_id, SID * ss_id){
    return !fitS_id(fs_id, ss_id);
}

char *s_idToASCIIString(SID * const s_id){
    if(s_id->decrypt_str == NULL){
        s_id->decrypt_str = malloc(sizeof(char) * 33);
        s_id->decrypt_str[32] = '\0';
        for(register int i = 0; i < 16; i++){
            unsigned char temp_dyt = s_id->decrypt_hex[i];
            unsigned char k = 0;
            for (k = 0; temp_dyt - k * 0x10 > 0; k++);
            s_id->decrypt_str[i * 2] = hexToChar(k);
            s_id->decrypt_str[i * 2 + 1] = hexToChar(temp_dyt - k * 0x10);
        }
        free(s_id->md5);
        s_id->md5 = NULL;
    }
    char *rtn_str = malloc(sizeof(char) * 33);
    strcpy(rtn_str, s_id->decrypt_str);
    return rtn_str;
}

char *s_idToASCIIRawString(SID * const s_id){
    char *string = NULL;
    int deep_len = 0, temp, buff_count, string_count;
    unsigned int buff[DATA_BIT];
    if(s_id->deep > 0){
        if (s_id->deep == DEEPC){
            string = (char *) malloc(sizeof(char) * (DEEPC_LEN + 1) * DATA_BIT);
            deep_len = DEEPC_LEN + 1;
            deep_len *= DATA_BIT;
        }
        else if (s_id->deep == DEEPB){
            string = (char *) malloc(sizeof(char) * (DEEPC_LEN + DEEPB_LEN + 1) * DATA_BIT);
            deep_len = DEEPC_LEN + DEEPB_LEN + 1;
            deep_len *= DATA_BIT;
        }
        else{
            string = (char *)malloc(sizeof(char) * (DEEPC_LEN + DEEPB_LEN + DEEPA_LEN + 1) * DATA_BIT);
            deep_len = DEEPC_LEN + DEEPB_LEN + DEEPA_LEN + 1;
            deep_len *= DATA_BIT;
        }
        if(string == NULL){
            printf("\ns_idToASCIIString(): Error in getting the memory of string.\n");
        }
        string[deep_len] = '\0';
        temp = s_id->sr->type;
        buff_count = DATA_BIT - 1;
        for (int i = 0; i < DATA_BIT; i++) buff[i] = 0;
        while(buff_count >= 0){
            buff[buff_count] = temp % 10;
            string[buff_count] = buff[buff_count] + 48;
            temp /= 10;
            buff_count--;
        }
        deep_len -= DATA_BIT;
        for(int i = 0; i < DEEPC_LEN; i++){
            temp = s_id->sr->value[i];
            for (int i = 0; i < DATA_BIT; i++) buff[i] = 0;
            string_count = TYPE_LEN + (i) * 5;
            buff_count = DATA_BIT - 1;
            while (buff_count >= 0) {
                buff[buff_count] = temp % 10;
                temp /= 10;
                buff_count--;
            }
            for(int i = DATA_BIT - 1; i >= 0; i--) string[string_count + i] = buff[i] + 48;
        }
        deep_len -= DEEPC_LEN * DATA_BIT;
        if(deep_len > 0)
            for(int i = 0; i < DEEPB_LEN; i++){
                temp = s_id->sr->value_deeper[i];
                for (int i = 0; i < DATA_BIT; i++) buff[i] = 0;
                string_count = TYPE_LEN + DEEPC_LEN * DATA_BIT + (i) * DATA_BIT;
                buff_count = DATA_BIT - 1;
                while (buff_count >= 0) {
                    buff[buff_count] = temp % 10;
                    temp /= 10;
                    buff_count--;
                }
                for(int i = DATA_BIT - 1; i >= 0; i--) string[string_count + i] = buff[i] + 48;
            }
        
        deep_len -= DEEPB_LEN * DATA_BIT;
        if(deep_len > 0)
            for(int i = 0; i < DEEPA_LEN; i++){
                temp = s_id->sr->value_deepest[i];
                for (int i = 0; i < DATA_BIT; i++) buff[i] = 0;
                string_count = TYPE_LEN + (DEEPC_LEN + DEEPB_LEN) * DATA_BIT + (i) * DATA_BIT;
                buff_count = DATA_BIT - 1;
                while (buff_count >= 0) {
                    buff[buff_count] = temp % 10;
                    string[string_count] = buff[buff_count] + 48;
                    temp /= 10;
                    buff_count--;
                }
                for(int i = DATA_BIT - 1; i >= 0; i--) string[string_count + i] = buff[i] + 48;
            }
        return string;
    }
    else{
        return NULL;
    }
    
}
SID *asciiStringToS_id(char * const string){
    SID *s_id = NULL;
    unsigned long long string_len = strlen(string);
    
    if (string_len == 25) s_id = initS_id(1);
    else if (string_len == 65) s_id = initS_id(2);
    else if (string_len == 225) s_id = initS_id(3);
    else return NULL;
    
    unsigned int *buff = (unsigned int *) malloc(sizeof(unsigned int) * (string_len));
    if(buff == NULL){
        printf("\ns_idToASCIIString(): Error in getting the memory of string.\n");
    }
    for(int i = 0; i < string_len; i++){
        buff[i] = (unsigned int)string[i] - 48;
    }
    
    s_id->sr->type = 0;
    for (int i = 0; i < 5; i++){
        s_id->sr->type += buff[i] ;
        s_id->sr->type *= 10u;
    }
    s_id->sr->type /= 10u;
    
    if (string_len >= 25){
        for(int i = 0; i < DEEPC_LEN; i++){
            s_id->sr->value[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->sr->value[i] += (unsigned int)buff[5 + i * 5 + j];
                if(j < 4) s_id->sr->value[i] *= 10;
            }
        }
    }
    
    if (string_len >= 65){
        for(int i = 0; i < DEEPB_LEN; i++){
            s_id->sr->value_deeper[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->sr->value_deeper[i] += buff[25 + i * 5  + j];
                if(j < 4) s_id->sr->value_deeper[i] *= 10;
            }
        }
    }
    if (string_len >= 225){
        for(int i = 0; i < DEEPA_LEN; i++){
            s_id->sr->value_deepest[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->sr->value_deepest[i] += buff[65 + i * 5 + j];
                if(j < 4) s_id->sr->value_deepest[i] *= 10;
            }
        }
    }
    free(buff);
    return s_id;
}

int freeS_id(SID *s_id){
    freeSidRaw(s_id);
    if (s_id->md5 != NULL) free(s_id->md5);
    free(s_id);
    return 0;
}

int freeSidRaw(SID *s_id){
    if (s_id->sr != NULL){
        if(s_id->sr->value != NULL){
            free(s_id->sr->value);
            s_id->sr->value = NULL;
        }
        if(s_id->sr->value_deeper != NULL){
            free(s_id->sr->value_deeper);
            s_id->sr->value_deeper = NULL;
        }
        if(s_id->sr->value_deepest != NULL){
            free(s_id->sr->value_deepest);
            s_id->sr->value_deepest = NULL;
        }
    }
    free(s_id->sr);
    return 0;
}

void s_idToMD5(SID *s_id){
    if(s_id->md5 == NULL) s_id->md5 = malloc(sizeof(MD5_CTX));
    char *sid_string = s_idToASCIIRawString(s_id);
    MD5Init(s_id->md5);
    MD5Update(s_id->md5, (unsigned char *) sid_string, strlen(sid_string));
    MD5Final(s_id->md5, s_id->decrypt_hex);
    freeSidRaw(s_id);
    s_id->sr = NULL;
}

char hexToChar(unsigned char n){
    switch (n) {
        case 1:return '1';
        case 2:return '2';
        case 3:return '3';
        case 4:return '4';
        case 5:return '5';
        case 6:return '6';
        case 7:return '7';
        case 8:return '8';
        case 9:return '9';
        case 10:return 'a';
        case 11:return 'b';
        case 12:return 'c';
        case 13:return 'd';
        case 14:return 'e';
        case 15:return 'f';
        default:
            break;
    }
    return '0';
}

SID *copyS_id(SID *f_sid){
    SID *s_sid = initS_id(f_sid->deep);
    for(int i = 0; i < 16; i++)
        s_sid->decrypt_hex[i] = f_sid->decrypt_hex[i];
    return 0;
}
