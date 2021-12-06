#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "school.h"

static bit_8   num_schools = 0;
static school *schools     = NULL;

//////////////////////////////////////////////

struct school {
  bit_8 id : 4; // exp: 10 
  str   name;   // varied
};

///////////////////////////////////////////////

int parse_school (void  *ext, int argc, str *argv, str *col) {
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
  print_schools();
}

void free_schools () {
  free(schools);
}

/////////////////////////////////////////////////

void print_schools () {
  for(int i=0; i < num_schools; i++)
    printf ("- school [%d] %s\n", schools[i].id, schools[i].name);
}
