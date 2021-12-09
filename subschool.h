#ifndef  SUBSCHOOL_H
#define  SUBSCHOOL_H
#include "id_group.h"
#include "bit_def.h"
#include "str_def.h"

typedef struct subschool subschool;
typedef id_group subschool_id_group;
extern void init_subschools();
extern void free_subschools();
extern void print_subschools();
#endif
