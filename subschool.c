#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "subschool.h"
#include "index.h"
static bit_8
  num_subschools       = 0,
  num_subschool_groups = 0;
static subschool
  *subschools = NULL;
static subschool_id_group
  *subschool_id_groups = NULL;
//////////////////////////////////////////////

struct subschool {
  bit_8     id;            // for possible id(s) 
  str       name;          // varied
  bit_8     school_id : 4; // exp: 16
};

///////////////////////////////////////////////

int parse_subschool (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id        = 0,
    arg_name      = 1,
    arg_school_id = 2;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  subschool *ptr = (subschool*)ext;
  ptr += index;
  // id:
  ptr->id = index_to_id(index);
  // name:
  ptr->name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(ptr->name, argv[arg_name]);
  // school_id: danger possible NULL
  int ret = atoi(argv[arg_school_id]);
  if (!ret) // tried to parse null, found a subschool group
    num_subschool_groups++;
  else // parse as normal, found a normal subschool
    ptr->school_id = ret;
  // done:
  return 0;

int parse_subschool_group (void  *ext, int argc, str *argv, str *col) {
  const int
    pos_id             = 0,
    pos_group_size     = 1,
    pos_subschool_id_1 = 2,
    pos_subschool_id_2 = 3,
    pos_relation       = 4;
  // setup:
  int index = atoi(argv[pos_id]) - 1;
  subschool_id_group *ptr = (subschool_id_group*)ext;
  ptr += index;
  // id:
  ptr->id = index_to_id(index);
  // name:
  const int
    group_size     = atoi(argv[pos_group_size]),
    subschool_id_1 = atoi(argv[pos_sub_school_id_1]),
    subschool_id_2 = atoi(argv[pos_sub_school_id_2]),
    relation       = atoi(argv[pos_relation])-1;

  ptr = new_id_group(group_size);
  add_id_to_id_group(ptr, subschool_id_1);
  add_id_to_id_group(ptr, subschool_id_2);
  add_relation_to_id_group(ptr, relation);

  // done:
  return 0;
}


////////////////////////////////////////////////

void init_subschools () {
  subschools = (subschool*) load_table
    ("Pathfinder.db", "subschool",
     parse_subschool, sizeof(subschool),
     (int*) &num_subschools);

  num_subschools -= num_subschool_groups;
  realloc(subschools, sizeof(subschool) * num_subschools);

  subschools = (subschool_group*) load_table
    ("Pathfinder.db", "subschool_group",
     parse_subschool_group, sizeof(subschool_group),
     (int*) &num_subschool_groups);
}

void free_subschools () {
  free(subschools);
}

void free_subschool_groups () {
  free(subschool_groups);
}

/////////////////////////////////////////////////
 
void print_subschool (int id) {
  printf("[%d]%s\n",
	 subschools[id_to_index(id)].id,
	 subschools[id_to_index(id)].name);
}

void print_subschools () {
  for(int id=1; id <= num_subschools; id++)
    print_subschool(id);
}


void print_subschool_group
