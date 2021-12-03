#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sqlite_loader.h"
#include "time_unit.h"

static const str table_name  = "time_unit"; 
static byte_1 num_time_units = 0;
static time_unit *time_units = NULL;

// Struct Definitions: ////////////////////////////////////////////////
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

// Constructors and Parsers : //////////////////////////////////////////
void init_time_units() {
  num_time_units = peek_table_size("Pathfinder.db", table_name);
  time_units = (time_unit*) malloc(sizeof(time_unit) * num_time_units);
  load_table ("Pathfinder.db", table_name, parse_time_unit);
}

time_block *new_time_block (int arg_factor, int arg_time_unit_id) {
  time_block *ret_time_block = (time_block *) malloc(sizeof(time_block));
  ret_time_block -> factor  = arg_factor;
  ret_time_block -> time_unit_id = arg_time_unit_id;
  return ret_time_block;
}

int parse_time_unit (void  *NA, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1,
    arg_abrv = 2,
    arg_secs = 3;
  int index = atoi(argv[arg_id]) - 1;
  time_units[index].id = index + 1;
  time_units[index].name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(time_units[index].name, argv[arg_name]);
  time_units[index].abrv = malloc(strlen(argv[arg_abrv]) + 1);
  strcpy(time_units[index].abrv, argv[arg_abrv]);
  time_units[index].secs = atoi(argv[arg_secs]);
  return 0;
}
// Destructors: ////////////////////////////////////////////////////////
void free_time_units() {
  free(time_units);
}

void free_time_block (time_block *arg_time_block_ref) {
  free(arg_time_block_ref);
}

// Prints: /////////////////////////////////////////////////////////////
void print_time_block (time_block *arg_time_block_ref) {
  printf ("- time_block -\n");
  printf ("  factor        = %d\n", arg_time_block_ref -> factor);
  printf ("  time_unit_id  = %s\n", arg_time_block_ref -> time_unit_id);
  print_time_unit(time_unit_id));
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
