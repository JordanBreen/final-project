#ifndef  DESCRIPTOR_H
#define  DESCRIPTOR_H

#include "bit_def.h"
#include "str_def.h"

typedef struct descriptor descriptor;

extern void init_descriptors();
extern void free_descriptors();
extern void print_descriptors();

#endif
