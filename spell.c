#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "spell.h"
#include "buf_def.h"
struct spell {
//type - identifier ------------ storage
  spell_id     _id           : SPELL_ID_BIT;               // max 65,535 spells, expecting ~2,900 spells
  str          _name;
  school_id    _school_id    : SCHOOL_ID_BIT;
  subschool_id _subschool_id : SUBSCHOOL_ID_BIT;
  byte         _is_multi_subschool : 1;
  id_group    *_descriptor_id;
  str _spell_level_text;      // ptr array to 'classes'
  str _casting_time;          // struct
  str _components_text;       // text
  bit_8  _range_id;            // struct, enclosing enum CLOSE, MEDIUM, LONG
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

void process_descriptor_ids (spell *ptr, str *argv, str *col, int length);
void process_subschool_ids  (spell *ptr, str arg_str);
int parse_spell (void *ext, int argc, str *argv, str *col) {
  const int
    POS_ID            = 0,
    POS_NAME          = 1,
    POS_SCHOOL_ID     = 2,
    POS_SUBSCHOOL_ID  = 3,
    POS_DESCRIPTOR_START = 56,
    POS_DESCRIPTOR_END   = 83;
  
    //POS_DESCRIPTOR_ID = 4;
  // buf buffer;
  // setup:
  int index = atoi(argv[POS_ID]) - 1;
  spell *ptr = (spell*)ext;
  ptr += index;
  // id:
  ptr->_id = index + 1;
  // name:
  ptr->_name = malloc(strlen(argv[POS_NAME]) + 1);
  strcpy(ptr->_name, argv[POS_NAME]);
  // school_id:
  ptr->_school_id = (school_id)atoi(argv[POS_SCHOOL_ID]);
  // subschool_ids:
  process_subschool_ids(ptr, argv[POS_SUBSCHOOL_ID]);
  // descriptor_ids:
  process_descriptor_ids(ptr, &argv[POS_DESCRIPTOR_START], &col[POS_DESCRIPTOR_START], POS_DESCRIPTOR_END - POS_DESCRIPTOR_START);
  // done:
  return 0;
}

spell *load_spell(spell_id id) {
  spell *out = (spell*) load_by_id ("Pathfinder.db", "spell", parse_spell, sizeof(spell), id);
  print_spell(out);
  return out;
}

void print_spell (spell *spell_ref) {
  printf("%s\n", spell_ref->_name);
  printf("School %s(%s)[%s]\n",
	 get_name_school(spell_ref->_school_id),
	 get_name_subschool(spell_ref->_subschool_id, spell_ref->_is_multi_subschool),
	 get_name_descriptor(get_ref_id_group(spell_ref->_descriptor_id, 0))); // just grabbing the first, temp solution for testing
}

void process_descriptor_ids(spell *ptr, str *argv, str *col, int length) {
  descriptor_id
    ids[get_num_descriptors()],
    id_count = 0;
  for(int i = 0; i < length; i++)
    if(atoi(argv[i]) == 1)
      ids[id_count++] = get_id_descriptor(col[i]);
  ptr->_descriptor_id = new_id_group(id_count);
  for(int i = 0; i < id_count; i++)
    add_ref_id_group(ptr->_descriptor_id, ids[i]);
}

void process_subschool_ids(spell *ptr, str arg_str) {
  subschool_id ret_id = (subschool_id) atoi(arg_str);
  if(ret_id <= get_num_subschools())
  { // we have a normal subschool group with a single id
    ptr->_subschool_id = ret_id;
    ptr->_is_multi_subschool = 0;
  } else
  { // we have a group with multiple ids
    ptr->_subschool_id = ret_id - get_num_subschools();
    ptr->_is_multi_subschool = 1;
  }
}

