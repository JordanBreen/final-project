#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "class.h"

static const str   class_table_name      = "class";
static const str   class_type_table_name = "class_type";
static byte_1      num_class_types       = 0;
static class_type *class_types           = NULL;
static class      *classes               = NULL;

//////////////////////////////////////////////

struct class_type {
  bit_8 id;
  str   name;
};

struct class {
  bit_8 id;
  str   name;
};

///////////////////////////////////////////////

int parse_class_type (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  class_type *ptr = (class_type*)ext;
  ptr += index;
  // id:
  ptr->id = index + 1;
  // name:
  ptr->name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(ptr->name, argv[arg_name]);
  // done:
  return 0;
}

////////////////////////////////////////////////

void init_class_types() {
  class_types = (class_type*) load_table ("Pathfinder.db", class_type_table_name, parse_class_type, sizeof(class_type), (int*) &num_class_types);
}

void free_class_types() {
  free(class_types);
}

/////////////////////////////////////////////////

void print_class_types() {
  for(int i=0; i < num_class_types; i++) {
    printf ("- class_types[%d] -\n", i);
    printf ("  id   = %d\n", class_types[i].id);
    printf ("  name = %s\n", class_types[i].name);
  }
}

byte_1 get_num_class_types() {
  return num_class_types;
}
