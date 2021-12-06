#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "descriptor.h"

static bit_8       num_descriptors = 0;
static descriptor *descriptors     = NULL;

//////////////////////////////////////////////

struct descriptor {
  bit_8 id; 
  str   name;
};

///////////////////////////////////////////////

int parse_descriptor (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  descriptor *ptr = (descriptor*)ext;
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

void init_descriptors() {
  descriptors = (descriptor*) load_table ("Pathfinder.db", "descriptor", parse_descriptor, sizeof(descriptor), (int*) &num_descriptors);
}

void free_descriptors() {
  free(descriptors);
}

/////////////////////////////////////////////////

void print_descriptors() {
  for(int i=0; i < num_descriptors; i++) {
    printf ("- descriptors[%d] -\n", i);
    printf ("  id   = %d\n", descriptors[i].id);
    printf ("  name = %s\n", descriptors[i].name);
  }
}
