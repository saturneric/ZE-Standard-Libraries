#ifndef id_h
#define id_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"
#include "md5.h"

void init_rand(void);
unsigned long long getId(void);

SID *getS_id(unsigned int type, unsigned int deep_level);

int fitS_id(SID * const fs_id, SID * const ss_id);
int simFitS_id(SID * fs_id, SID * ss_id);

char *s_idToASCIIString(SID * const s_id);
SID *asciiStringToS_id(char * const string);

void s_idToMD5(SID *s_id);
char hexToChar(unsigned char);
SID *copyS_id(SID *f_sid);
void getRawS_id(SID *s_id, unsigned int type, unsigned int deep_level);

SID *initS_id(unsigned int deep_level);
int freeSidRaw(SID *s_id);
int freeS_id(SID *s_id);

static _Bool if_rand;
#endif /* id_h */
