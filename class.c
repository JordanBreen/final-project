#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "class.h"

static byte_1 num_class_types  = 0;
static class_type *class_types = NULL;

struct class_type {
  bit_8 id;
  str   name;
};

int parse_class_type (void  *NA, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;
  int index = atoi(argv[arg_id]) - 1;
  class_types[index].id = index + 1;
  class_types[index].name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(class_types[index].name, argv[arg_name]);
  return 0;
}

void init_class_types() {
  num_class_types = peek_table_size("Pathfinder.db", "class_type");
  class_types = (class_type*) malloc(sizeof(class_type) * num_class_types);
  load_table ("Pathfinder.db", "class_type", parse_class_type);
  print_class_types();
}

void print_class_types() {
  for(int i=0; i < num_class_types; i++) {
    printf ("- class_types[%d] -\n", i);
    printf ("  id   = %d\n", class_types[i].id);
    printf ("  name = %s\n", class_types[i].name);
  }
}

void free_class_types() {
  free(class_types);
}

byte_1 get_num_class_types() {
  return num_class_types;
}
