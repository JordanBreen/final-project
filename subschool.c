#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "subschool.h"

static bit_8      num_subschools = 0;
static subschool *subschools     = NULL;

//////////////////////////////////////////////

struct subschool {
  bit_8  id : 4;        // exp: 16 
  str    name;          // varied
  bit_8  school_id : 4; // exp: 10
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
  ptr->id = index + 1;
  // name:
  ptr->name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(ptr->name, argv[arg_name]);
  // school_id:
  ptr->school_id = atoi(argv[arg_school_id]);
  // done:
  return 0;
}

////////////////////////////////////////////////

void init_subschools () {
  subschools = (subschool*) load_table ("Pathfinder.db", "subschool", parse_subschool, sizeof(subschool), (int*) &num_subschools);
}

void free_subschools () {
  free(subschools);
}

/////////////////////////////////////////////////

void print_subschools () {
  for(int i=0; i < num_subschools; i++)
    printf ("- subschool [%d] %s\n", subschools[i].id, subschools[i].name);
}
