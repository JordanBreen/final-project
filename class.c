#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "class.h"

static bit_8       num_class_types       = 0;
static bit_8       num_classes           = 0;
static class_type *class_types           = NULL;
static class      *classes               = NULL;

//////////////////////////////////////////////

struct class_type {
  bit_8 id : 3; // exp: 7 class types
  str   name;   // varies
};

struct class {
  bit_8 id;
  str   name;
  str   abrv;              // exp: 3 characters
  bit_8 class_type_id : 3; // exp: 7 class types
  bit_8 skill_ranks   : 4; // exp: max value of 8 (rogue)
  bit_8 source_id;
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

int parse_class (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id            = 0,
    arg_name          = 1,
    arg_abrv          = 2,
    arg_class_type_id = 3,
    arg_skill_ranks   = 4,
    arg_source_id     = 5;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  class *ptr = (class*)ext;
  ptr += index;
  // id:
  ptr->id = index + 1;
  // name:
  ptr->name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(ptr->name, argv[arg_name]);
  // abrv:
  ptr->abrv = malloc(strlen(argv[arg_abrv]) + 1);
  strcpy(ptr->abrv, argv[arg_abrv]);
  // class_type_id:
  ptr->class_type_id = (bit_8)atoi(argv[arg_class_type_id]);
  // skill_ranks:
  ptr->skill_ranks = (bit_8)atoi(argv[arg_skill_ranks]);
  // source_id:
  ptr->source_id = (bit_8)atoi(argv[arg_source_id]);
  // done:
  return 0;
}

////////////////////////////////////////////////

void init_class_types() {
  class_types = (class_type*) load_table ("Pathfinder.db", "class_type", parse_class_type, sizeof(class_type), (int*) &num_class_types);
}
void init_classes() {
  classes = (class*) load_table ("Pathfinder.db", "class", parse_class, sizeof(class), (int*) &num_classes);
}

void free_class_types() {
  free(class_types);
}

void free_classes() {
  free(classes);
}

/////////////////////////////////////////////////

void print_class_types() {
  for(int i=0; i < num_class_types; i++) {
    printf ("- class_types[%d] -\n", i);
    printf ("  id   = %d\n", class_types[i].id);
    printf ("  name = %s\n", class_types[i].name);
  }
}

void print_classes() {
  for(int i=0; i < num_classes; i++) {
    printf ("- classes[%d] -\n", i);
    printf ("  id = %d\n", classes[i].id);
    printf ("  name = %s\n", classes[i].name);
    printf ("  abrv = %s\n", classes[i].abrv);
    printf ("  class type id = %d\n", classes[i].class_type_id);
    printf ("  ranks/level = %d\n", classes[i].skill_ranks);
    printf ("  source id = %d\n", classes[i].source_id);
  }
}

