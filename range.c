#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "range.h"

static bit_8  num_ranges = 0;
static range *ranges     = NULL;

//////////////////////////////////////////////

struct range {
  bit_8  id    : 3; // exp: 6 
  str    name;      // varied
  bit_8  fixed : 1; // is the range fixed?
  // scalar data //////////////////
  bit_16 base  : 9; // exp: max 400
  bit_8  plus  : 6; // exp: max 40
  bit_8  rate  : 2; // exp: max 4
};

///////////////////////////////////////////////

int parse_range (void  *ext, int argc, str *argv, str *col) {
  const int
    arg_id   = 0,
    arg_name = 1,
    arg_base = 2,
    arg_plus = 3,
    arg_rate = 4;
  // setup:
  int index = atoi(argv[arg_id]) - 1;
  range *ptr = (range*)ext;
  ptr += index;
  // id:
  ptr->id = index + 1;
  // name:
  ptr->name = malloc(strlen(argv[arg_name]) + 1);
  strcpy(ptr->name, argv[arg_name]);
  // testing base column:
  if(argv[arg_base] == NULL) { // fixed range
    ptr->fixed = 1;
    ptr->base =
      ptr->plus =
        ptr->rate = 0;
  }
  else { // scalar range
    ptr->fixed = 0;
    ptr->base = atoi(argv[arg_base]);
    ptr->plus = atoi(argv[arg_plus]);
    ptr->rate = atoi(argv[arg_rate]);
  }
  // done:
  return 0;
}

////////////////////////////////////////////////

void init_ranges () {
  ranges = (range*) load_table ("Pathfinder.db", "range", parse_range, sizeof(range), (int*) &num_ranges);
}

void free_ranges () {
  free(ranges);
}

/////////////////////////////////////////////////

void print_ranges () {
  for(int i=0; i < num_ranges; i++) {
    printf ("- range [%d] %s", ranges[i].id, ranges[i].name);
    if(!ranges[i].fixed)
      printf (" (%d ft. + %d ft./%d level%s)", ranges[i].base, ranges[i].plus, ranges[i].rate, (ranges[i].rate > 1) ? "s" : "");
    printf ("\n");
  }
}
