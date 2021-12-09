#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spell.h"
#include "buf_def.h"
struct spell {
//type - identifier ------------ storage
  bit_16   id;               // max 65,535 spells, expecting ~2,900 spells
  str      name;
  bit_8    school_id;
  id_group *subschool_id_group;
  id_group *descriptor_id_group;
  str _spell_level_text;      // ptr array to 'classes'
  str _casting_time;          // struct
  str _components_text;       // text
  bit_8  range_id;            // struct, enclosing enum CLOSE, MEDIUM, LONG
  str _area;                  // struct
  str _effect;                // struct
  str _targets;               // struct
  str _duration;              // struct
  str _saving_throw;          // struct
  str _description_full;      // string
  str _description_short;     // string
  str _description_formatted; // string
  str _source;                // enum
  str _full_text;             // string

  spell_component_flags _components;
  spell_attribute_flags _attributes;
  //spell_level_by_class  _level_by_class;

  str _SLA_level;             // possible part of another flag structure
  str _domain_text;           // string
  str _bloodline_text;        // string
  str _patron_text;           // string
  str _mythic_text;           // string
  str _mythic_augment_text;   // string
  //spell_descriptor_flags _descriptors;       // bool flag,  expecting 28 descriptors, 28 bits == >3 bytes, unsigned int, assert 4-byte int
  unsigned short _material_cost;     // possible NULL value;
};

bit_8* process_school_id(str arg_str);
int parse_spell (void *ext, int argc, str *argv, str *col) {
  const int
    POS_ID            = 0,
    POS_NAME          = 1,
    POS_SCHOOL_ID     = 2,
    POS_SUBSCHOOL_ID  = 3,
    POS_DESCRIPTOR_ID = 4;
  buf buffer;
  // setup:
  int index = atoi(argv[POS_ID]) - 1;
  spell *ptr = (spell*)ext;
  ptr += index;
  // id:
  ptr->id = index + 1;
  // name:
  ptr->name = malloc(strlen(argv[POS_NAME]) + 1);
  strcpy(ptr->name, argv[POS_NAME]);
  // school_id:
  ptr->school_id = (bit_8)atoi(argv[POS_SCHOOL_ID]);
  // subschool_ids:
  int ret_id =  atoi(argv[POS_SUBSCHOOL_ID]);
  if(ret_id <= get_num_subschools()) { // we have a normal subschool group with a single id
    ptr->subschool_id_group = new_id_group(1);
    add_ref_id_group(ptr->subschool_id_group, ret_id);
  } else { // we have a group with multiple ids
    ptr->subschool_id_group = get_subschool_id_group(ret_id - get_num_subschools());
  }
  // done:
  return 0;
}

void print_spell (spell *spell_ptr) {

}

id_group* process_subschool_ids(str arg_str) {
  //const char DELIM[2] = "";
  return NULL;
}
