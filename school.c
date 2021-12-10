#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "school.h"
#include "index.h"

static bit_8   num_schools = 0;
static school *schools     = NULL;

//////////////////////////////////////////////

struct school {
  school_id id : 4; // exp: 10 
  str name;         // varied
};

///////////////////////////////////////////////

int parse_school (void *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  school *ptr = (school*)ext;
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

void init_schools () {
  schools = (school*) load_table ("Pathfinder.db", "school", parse_school, sizeof(school), (int*) &num_schools);
}

void free_schools () {
  free(schools);
}

/////////////////////////////////////////////////

str get_name_school (school_id id) {
  return schools[id_to_index(id)].name;
}
void print_school ( bit_8 id ) {
  printf ("- school [%d] %s\n", schools[id_to_index(id)].id, schools[id_to_index(id)].name);
}

void print_schools () {
  for(int i=1; i <= num_schools; i++)
    print_school(i);
}
