#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spell.h"

int parse_spell (void  *ext,
                 int    argc,
                 char **argv,
                 char **col) {
  const int
    index_id   = 0,
    index_icon = 1,
    index_name = 2;
  int index;
  spell *spells = (spell *) ext;
  //index             = atoi(argv[index_id]) - 1;
  //icons[index].id   = index + 1;
  //icons[index].icon = (wchar_t)atol(argv[index_icon]);
  //icons[index].name = (char*) malloc(strlen(argv[index_name])+1);
  //strcpy(icons[index].name, argv[index_name]);
  return 0;
}

void print_spell (spell *spell_ptr) {

}
