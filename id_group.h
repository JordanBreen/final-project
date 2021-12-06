#ifndef ID_GROUP_H
#define ID_GROUP_H

#include "bit_def.h"
#include "str_def.h"
#include "logx.h"

typedef enum   relation relation;
typedef struct id_group id_group;

id_group *new_id_group             (int);
void      free_id_group            (id_group **);
void      add_relation_to_id_group (id_group *, relation);
void      add_id_to_id_group       (id_group *, bit_8);
bit_8     get_id_from_id_group     (id_group *, bit_8);
bit_8     get_num_ids_in_id_group  (id_group *);
bit_8     get_capacity_of_id_group (id_group *);
int       index_in_id_group_range  (id_group *, bit_8);
int       id_group_is_full         (id_group *);
void      print_id_group           (id_group *);

#endif
