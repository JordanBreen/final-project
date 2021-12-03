#ifndef  TIME_UNIT_H
#define  TIME_UNIT_H
#include "bit_def.h"
#include "str_def.h"
typedef unsigned int second, sec;
typedef struct time_unit time_unit;
typedef struct time_block time_block;

extern void free_time_block  ();
extern void free_time_units  ();
extern void init_time_units  ();
extern void print_time_block (time_block*);
extern void print_time_unit  (int);
extern void print_time_units ();

//extern time_block *new_time_block (int, time_unit*);
#endif
