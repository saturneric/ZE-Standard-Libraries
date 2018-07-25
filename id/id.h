//
//  id.h
//  ZE-Standard-Libraries
//
//  Created by 胡一兵 on 2018/7/25.
//  Copyright © 2018年 ZE. All rights reserved.
//

#ifndef id_h
#define id_h

#include <stdlib.h>
#include <time.h>

/*有关id的函数*/
void init_rand(void);
unsigned long long getId(void);

/*有关s_id函数*/
char *getS_id(void);

#endif /* id_h */
