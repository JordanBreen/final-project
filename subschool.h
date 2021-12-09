#ifndef  SUBSCHOOL_H
#define  SUBSCHOOL_H
#include "id_group.h"
#include "bit_def.h"
#include "str_def.h"

typedef struct subschool subschool;
extern void  init_subschools ();
extern void  free_subschools ();
extern bit_8 get_num_subschools ();
extern id_group* get_subschool_id_group(bit_8); 
extern void  print_subschool (bit_8);
extern void  print_subschools ();
extern void  print_subschool_id_group (bit_8);
extern void  print_subschool_id_groups ();
#endif
