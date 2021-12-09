#ifndef  SCHOOL_H
#define  SCHOOL_H

#include "bit_def.h"
#include "str_def.h"

typedef struct school school;

extern void init_schools  ();
extern void free_schools  ();
extern void print_school  (bit_8);
extern void print_schools ();

#endif
