#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "sqlite_loader.h"
#include "time_unit.h"

static byte_1 num_class_types = 0;
static time_unit *class_types = NULL;

struct class_type {
  bit_8 id;
  str   name;
};

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

void init_time_units() {
  num_time_units = peek_table_size("Pathfinder.db", "Time_Unit");
  time_units = (time_unit*) malloc(sizeof(time_unit) * num_time_units);
  load_table ("Pathfinder.db", "Time_Unit", parse_time_unit);
  //print_time_units();
}

void print_time_units() {
  for(int i=0; i < num_time_units; i++) {
    printf ("- time_units[%d] -\n", i);
    printf ("  id   = %d\n", time_units[i].id);
    printf ("  name = %s\n", time_units[i].name);
    printf ("  abrv = %s\n", time_units[i].abrv);
    printf ("  secs = %d\n", time_units[i].secs);
  }
}

void free_time_units() {
  free(time_units);
}
/*
time_block *new_time_block (int coef, time_unit arg_tu) {
  if(!in_bit_range(coef, TB_COEF_BIT))
     return NULL;
  time_block *ret_tb = (time_block *) malloc(sizeof(time_block));
  ret_tb -> _coefficient = coef;
  ret_tb -> _time_unit   = arg_tu;
  return ret_tb;
}
*/
