#include "id.h"

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
    SID *p_sid = (SID *) malloc(sizeof(SID));
    if(p_sid == NULL){
        printf("\ninitS_id(): Error in getting the memory of sid.\n");
    }
    p_sid->type = VOID;
    p_sid->deep = deep_level;
    p_sid->value = NULL;
    p_sid->value_deeper = NULL;
    p_sid->value_deepest = NULL;
    if (deep_level > 0) {
        p_sid->value = (unsigned int *)malloc(sizeof(unsigned int)*DEEPC_LEN);
        if(p_sid->value == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value.\n");
        }
    }
    if (deep_level > 1){
        p_sid->value_deeper = (unsigned int *)malloc(sizeof(unsigned int)*DEEPB_LEN);
        if(p_sid->value_deeper == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value_deeper.\n");
        }
    }
    if (deep_level > 2){
        p_sid->value_deepest = (unsigned int *)malloc(sizeof(unsigned int)*DEEPA_LEN);
        if(p_sid->value_deepest == NULL){
            printf("\ninitS_id(): Error in getting the memory of sid.value_deepest.\n");
        }
    }
    return p_sid;
}

SID *getS_id(unsigned int type, unsigned int deep_level){
    SID *p_sid = initS_id(deep_level);
    p_sid->type = type;
    if(deep_level > 0){
        for(int i = 0; i < DEEPC_LEN; i++) p_sid->value[i] = rand()%65535;
        if(deep_level > 1) for(int i = 0; i < DEEPB_LEN; i++) p_sid->value_deeper[i] = rand()%65535;
        if (deep_level > 2) for(int i = 0; i < DEEPA_LEN; i++) p_sid->value_deepest[i] = rand()%65535;
    }
    
    return p_sid;
}

int fitS_id(const SID *fs_id, const SID *ss_id){
    if(fs_id->type == ss_id->type){
        if(fs_id->deep == ss_id->deep){
            if (fs_id->deep > 0)
                for(int i = 0; i < DEEPC_LEN; i++){
                    if(fs_id->value[i] == ss_id->value[i]) continue;
                    else if(fs_id->value[i] > ss_id->value[i]) return 1;
                    else return -1;
                }
            if (fs_id->deep > 1)
                for(int i = 0; i < DEEPB_LEN; i++){
                    if(fs_id->value_deeper[i] == ss_id->value_deeper[i]) continue;
                    else if(fs_id->value_deeper[i] > ss_id->value_deeper[i]) return 1;
                    else return -1;
                }
            if (fs_id->deep > 2)
                for(int i = 0; i < DEEPA_LEN; i++){
                    if(fs_id->value_deepest[i] == ss_id->value_deepest[i]) continue;
                    else if(fs_id->value_deepest[i] > ss_id->value_deepest[i]) return 1;
                    else return -1;
                }
        }
        else{
            if(fs_id->deep > ss_id->deep) return 1;
            else return -1;
        }
    }
    else{
        if (fs_id->type > ss_id->type) return 1;
        else return -1;
    }
    return 0;
}

int simFitS_id(const SID *fs_id, const SID *ss_id){
    return !fitS_id(fs_id, ss_id);
}

char *s_idToASCIIString(const SID *s_id){
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
        temp = s_id->type;
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
            temp = s_id->value[i];
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
                temp = s_id->value_deeper[i];
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
                temp = s_id->value_deepest[i];
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
SID *asciiStringToS_id(const char *string){
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
    
    s_id->type = 0;
    for (int i = 0; i < 5; i++){
        s_id->type += buff[i] ;
        s_id->type *= 10u;
    }
    s_id->type /= 10u;
    
    if (string_len >= 25){
        for(int i = 0; i < DEEPC_LEN; i++){
            s_id->value[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->value[i] += (unsigned int)buff[5 + i * 5 + j];
                if(j < 4) s_id->value[i] *= 10;
            }
        }
    }
    
    if (string_len >= 65){
        for(int i = 0; i < DEEPB_LEN; i++){
            s_id->value_deeper[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->value_deeper[i] += buff[25 + i * 5  + j];
                if(j < 4) s_id->value_deeper[i] *= 10;
            }
        }
    }
    if (string_len >= 225){
        for(int i = 0; i < DEEPA_LEN; i++){
            s_id->value_deepest[i] = 0;
            for (int j = 0; j < 5; j++){
                s_id->value_deepest[i] += buff[65 + i * 5 + j];
                if(j < 4) s_id->value_deepest[i] *= 10;
            }
        }
    }
    free(buff);
    return s_id;
}

int freeS_id(SID *s_id){
    if(s_id->value != NULL){
        free(s_id->value);
        s_id->value = NULL;
    }
    if(s_id->value_deeper != NULL){
        free(s_id->value_deeper);
        s_id->value_deeper = NULL;
    }
    if(s_id->value_deepest != NULL){
        free(s_id->value_deepest);
        s_id->value_deepest = NULL;
    }
    free(s_id);
    return 0;
}