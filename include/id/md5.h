#ifndef md5_h
#define md5_h

#include <type.h>

#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))

#define FF(a,b,c,d,x,s,ac) { \
a += F(b, c, d) + x + ac; \
a = ROTATE_LEFT(a, s); \
a += b; \
}

#define GG(a,b,c,d,x,s,ac) { \
a += G(b, c, d) + x + ac; \
a = ROTATE_LEFT(a, s); \
a += b; \
}

#define HH(a,b,c,d,x,s,ac) { \
a += H(b, c, d) + x + ac; \
a = ROTATE_LEFT(a, s); \
a += b; \
}
#define II(a,b,c,d,x,s,ac) { \
a += I(b, c, d) + x + ac; \
a = ROTATE_LEFT(a, s); \
a += b; \
}

/*
 *MD5的管理及操作的结构
 */
typedef struct md5_ctx{
    unsigned int count[2];
    unsigned int state[4];
    unsigned char buffer[64];
}MD5_CTX;


void MD5Init(MD5_CTX *context);
void MD5Update(MD5_CTX *context, unsigned char *input, unsigned long inputlen);
void MD5Final(MD5_CTX *context, unsigned char digest[16]);

void MD5Transform(unsigned int state[4], unsigned char block[64]);
void MD5Encode(unsigned char *output, unsigned int *input, unsigned long len);
void MD5Decode(unsigned int *output, unsigned char *input, unsigned long len);

#endif /* md5_h */
