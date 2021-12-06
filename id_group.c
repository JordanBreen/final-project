#include <stdio.h>
#include <stdlib.h>
#include "id_group.h"

enum relation {
  AND = 0,
  OR  = 1,
  NUM_RELATIONS
};

static const int MIN_CAP = 1;
static const int MAX_CAP = 8;

struct id_group {
  bit_8 *ids;
  bit_8 num_ids  : 3; // max 8 related ids
  bit_8 capacity : 3; // max 8 slots for related ids
  bit_8 relation : 1; // and their relation
  // total storage 7 bits + bits allocated to ids
};

id_group *new_id_group(int arg_num_ids) {
    if (arg_num_ids > MAX_CAP) {
    fprintf(stderr, "%s:%s(int arg_num_ids = %d), Error num_ids greater than MAX_CAP(%d)\n", __FILE__, __func__, arg_num_ids, MAX_CAP);
    //return NULL;
    exit(1);
  } else if (arg_num_ids < MIN_CAP) {
    fprintf(stderr, "%s:%s(int arg_num_ids = %d), Error num_ids less than MIN_CAP(%d)\n", __FILE__, __func__, arg_num_ids, MIN_CAP);
    //return NULL;
    exit(1);
  } else {
    id_group *out = (id_group*)malloc(sizeof(id_group));
    out->num_ids  = 0;
    out->capacity = arg_num_ids;
    out->ids = (bit_8*)malloc(sizeof(bit_8)*arg_num_ids);
    return out;
  }
}

void free_id_group (id_group **id_group_ref) {
  free((*id_group_ref)->ids);
  (*id_group_ref)->ids = NULL;
  free(*id_group_ref);
  *id_group_ref = NULL;
}

// adds: //
void add_relation_to_id_group (id_group *id_group_ref, relation arg_relation) {
  if(arg_relation >= NUM_RELATIONS || arg_relation < 0) {
    fprintf(stderr, "%s:%s(int arg_relation = %d), Error arg_relation outside of range [%d,%d]\n", __FILE__, __func__, arg_relation, 0, NUM_RELATIONS);
    exit(1);
  } else {
    id_group_ref->relation = arg_relation;
  }
}

void add_id_to_id_group (id_group *id_group_ref, bit_8 arg_id) {
  if(id_group_is_full(id_group_ref)) {
    fprintf(stderr, "%s:%s(bit_8 arg_id = %d), Error adding id to id_group_ref exceeds capacity of %d, add aborted\n", __FILE__, __func__, arg_id, id_group_ref->capacity);
    exit(1);
  } else {
    id_group_ref->ids[id_group_ref->num_ids++] = arg_id;
  }
}

// gets: //
bit_8 get_id_from_id_group (id_group *id_group_ref, bit_8 arg_index) {
  if(!index_in_id_group_range(id_group_ref, arg_index)) {
    fprintf(stderr, "%s:%s(bit_8 arg_index = %d), Error arg_index is outside of current id_group_ref range [%d,%d], get id aborted\n", __FILE__, __func__, arg_index, 0, id_group_ref->num_ids);
    exit(1);
  } else {
    return id_group_ref->ids[arg_index];
  }
}

bit_8 get_num_ids_in_id_group (id_group *id_group_ref) {
  return id_group_ref->num_ids;
}

bit_8 get_capacity_of_id_group (id_group *id_group_ref) {
  return id_group_ref->capacity;
}

// boolean tests: //
int index_in_id_group_range(id_group *id_group_ref, bit_8 arg_index) {
  return arg_index < id_group_ref->num_ids && arg_index >= 0;  
}

int id_group_is_full(id_group *id_group_ref) {
  return id_group_ref->num_ids >= id_group_ref->capacity;
}

// printing: //
void print_id_group(id_group *id_group_ref) {
  printf("ID Group <@:%p> [", id_group_ref);
  for(int i = 0; i < id_group_ref->capacity; i++)
    printf("%d,", id_group_ref->ids[i]);
  printf("\b]\n");
}
