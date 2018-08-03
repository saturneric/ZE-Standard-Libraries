#ifndef id_h
#define id_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"

typedef struct s_id{
    unsigned int type;
    unsigned int (*value)[DEEPC_LEN];//4
    unsigned int (*value_deeper)[DEEPB_LEN];//8
    unsigned int (*value_deepest)[DEEPA_LEN];//32
    unsigned int deep;
}SID;

void init_rand(void);
unsigned long long getId(void);

SID *getS_id(unsigned int type ,unsigned int deep_level);

int fitS_id(const SID *fs_id, const SID *ss_id);
int simFitS_id(const SID *fs_id, const SID *ss_id);

char *s_idToASCIIString(const SID *s_id);
SID *asciiStringToS_id(const char *string);

SID *initS_id(unsigned int deep_level);
int freeS_id(SID *s_id);

#endif /* id_h */