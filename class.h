#ifndef  CLASS_H
#define  CLASS_H
#include "bit_def.h"
#include "str_def.h"
typedef struct class_type class_type;
typedef struct class class;
extern void init_class_types();
extern void free_class_types();
extern void print_class_types();
extern byte_1 get_num_class_types();
#endif
