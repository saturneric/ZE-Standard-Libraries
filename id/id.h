#ifndef id_h
#define id_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../type/type.h"

void init_rand(void);
unsigned long long getId(void);

SID *getS_id(unsigned int type, unsigned int deep_level);

int fitS_id(const SID *fs_id, const SID *ss_id);
int simFitS_id(const SID *fs_id, const SID *ss_id);

char *s_idToASCIIString(const SID *s_id);
SID *asciiStringToS_id(const char *string);

SID *initS_id(unsigned int deep_level);
int freeS_id(SID *s_id);

#endif /* id_h */
