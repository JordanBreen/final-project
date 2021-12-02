#ifndef BIT_DEF_H
#define BIT_DEF_H
#include <math.h>
#define in_bit_range(i, b) ((i) < (pow(2,b)) ? (1) : (0))

typedef unsigned char  bit08;
typedef unsigned short bit16;
typedef unsigned int   bit32;
typedef unsigned long  bit64;
#endif
