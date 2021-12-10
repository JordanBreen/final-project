#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "class.h"
#include "index.h"
static byte        num_class_types = 0;
static byte        num_classes     = 0;
static class_type *class_types     = NULL;
static class      *classes         = NULL;

//////////////////////////////////////////////

struct class_type {
  class_type_id _id : CLASS_TYPE_ID_BIT; // exp: 7 class types
  str           _name;                   // varies
};

struct class {
  class_id      _id : CLASS_ID_BIT;
  str           _name;
  str           _abrv;                              // exp: 3 characters
  class_type_id _class_type_id : CLASS_TYPE_ID_BIT; // exp: 7 class types
  bit_8         _skill_ranks   : SKILL_RANK_BIT;    // exp: max value of 8 (rogue)
  bit_8         _source_id;
};

///////////////////////////////////////////////

int parse_class_type (void  *ext, int argc, str *argv, str *col) {
  const int
    POS_ID   = 0,
    POS_NAME = 1;
  // setup:
  int index = atoi(argv[POS_ID]) - 1;
  class_type *ptr = (class_type*)ext;
  ptr += index;
  // id:
  ptr->_id = index + 1;
  // name:
  ptr->_name = malloc(strlen(argv[POS_NAME]) + 1);
  strcpy(ptr->_name, argv[POS_NAME]);
  // done:
  return 0;
}

int parse_class (void  *ext, int argc, str *argv, str *col) {
  const int
    POS_ID            = 0,
    POS_NAME          = 1,
    POS_ABRV          = 2,
    POS_CLASS_TYPE_ID = 3,
    POS_SKILL_RANKS   = 4,
    POS_SOURCE_ID     = 5;
  
  int index = atoi(argv[POS_ID]) - 1;
  class *ptr = (class*)ext;
  ptr += index;

  ptr->_id = index + 1;
  ptr->_name = malloc(strlen(argv[POS_NAME]) + 1);
  strcpy(ptr->_name, argv[POS_NAME]);

  ptr->_abrv = malloc(strlen(argv[POS_ABRV]) + 1);
  strcpy(ptr->_abrv, argv[POS_ABRV]);

  ptr->_class_type_id = atoi(argv[POS_CLASS_TYPE_ID]);
  ptr->_skill_ranks = atoi(argv[POS_SKILL_RANKS]);
  ptr->_source_id = atoi(argv[POS_SOURCE_ID]);

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

byte get_num_classes () {
  return num_classes;
}

str to_str_class_type (class_type_id _class_type_id) {
  return class_types[id_to_index(_class_type_id)]._name;
}

str to_str_class(class_id _class_id) {
  return classes[id_to_index(_class_id)]._name;
}

class_id get_id_class (str _str){
  for(int i = 0; i < num_classes; i++)
    if(_str[0] == classes[i]._name[0] && strcmp(_str, classes[i]._name) == 0)
      return classes[i]._id;
  fprintf(stderr, "%s:%s() ERROR, %s not found as a name in classes\n", __FILE__, __func__, _str);
  return -1;
}

