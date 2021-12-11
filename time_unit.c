#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sqlite_loader.h"
#include "time_unit.h"

static byte_1 num_time_units = 0;
static time_unit *time_units = NULL;

// Struct Definitions: /////////////////////////////////////////

struct time_unit {
  bit_8 id;
  str   name;
  str   abrv;
  sec   secs;
};

struct time_block {
  bit_8 factor;
  bit_8 time_unit_id;
};

// Sqlite data parser: /////////////////////////////////////////

int parse_time_unit (void *ext, int argc, str *argv, str *col) {
  const int
    POS_ID   = 0,
    POS_NAME = 1,
    POS_ABRV = 2,
    POS_SECS = 3;

  int index = atoi(argv[POS_ID]) - 1;
  time_unit *ptr = (time_unit*)ext;
  ptr += index;

  ptr->id = index + 1;
  ptr->name = str_clone(argv[POS_NAME]);
  ptr->abrv = str_clone(argv[POS_ABRV]);
  ptr->secs = atoi(argv[POS_SECS]);

  return 0;
}

// Constructors: ////////////////////////////////////////////////////////

void init_time_units() {
  time_units = (time_unit*) load_table ("Pathfinder.db", "time_unit", parse_time_unit, sizeof(time_unit), (int*) &num_time_units);
}

time_block *new_time_block (int arg_factor, int arg_time_unit_id) {
  time_block *ret_time_block = (time_block *) malloc(sizeof(time_block));
  ret_time_block -> factor  = arg_factor;
  ret_time_block -> time_unit_id = arg_time_unit_id;
  return ret_time_block;
}

// Destructors: ////////////////////////////////////////////////////////

void free_time_units() {
  free(time_units);
}

void free_time_block (time_block *time_block_ref) {
  free(time_block_ref);
}

// Prints: /////////////////////////////////////////////////////////////

void print_time_block (time_block *time_block_ref) {  
  printf ("- time_block -\n");
  printf ("  factor        = %d\n", time_block_ref->factor);
  printf ("  time_unit_id  = %d\n", time_block_ref->time_unit_id);
  print_time_unit(time_block_ref->time_unit_id);
}

void print_time_unit(int id) {
  int index = id - 1;
  printf ("- time_units[%d] -\n", index);
  printf ("  id   = %d\n", time_units[index].id);
  printf ("  name = %s\n", time_units[index].name);
  printf ("  abrv = %s\n", time_units[index].abrv);
  printf ("  secs = %d\n", time_units[index].secs);
}

void print_time_units() {
  for(int i=0; i < num_time_units; i++)
    print_time_unit(i+1);
}
