//
//  id.c
//  ZE-Standard-Libraries
//
//  Created by 胡一兵 on 2018/7/25.
//  Copyright © 2018年 ZE. All rights reserved.
//

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

char *getS_id(void){
    
    return NULL;
}

