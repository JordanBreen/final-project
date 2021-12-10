#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "spell.h"
#include "buf_def.h"
struct spell {
//type - identifier ------------ storage
  spell_id   _id           : SPELL_ID_BIT;               // max 65,535 spells, expecting ~2,900 spells
  str        _name;
  school_id  _school_id    : SCHOOL_ID_BIT;
  id_group * _subschool_id;
  id_group * _descriptor_id;
  sl_group * _spell_levels;
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
void process_spell_levels   (spell *ptr, str *argv, str *col, int length);
void process_subschool_ids  (spell *ptr, str arg_str);
int parse_spell (void *ext, int argc, str *argv, str *col) {
  const int
    POS_ID                = 0,
    POS_NAME              = 1,
    POS_SCHOOL_ID         = 2,
    POS_SUBSCHOOL_ID      = 3,
    POS_SPELL_LEVEL_START = 28,
    POS_SPELL_LEVEL_END   = 53,
    POS_DESCRIPTOR_START  = 56,
    POS_DESCRIPTOR_END    = 83;
  // setup:
  int index = atoi(argv[POS_ID]) - 1;
  spell *ptr = (spell*)ext;
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
  // spell_levels:
  process_spell_levels(ptr, &argv[POS_SPELL_LEVEL_START], &col[POS_SPELL_LEVEL_START], POS_SPELL_LEVEL_END - POS_SPELL_LEVEL_START);

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
  printf("School %s", get_name_school(spell_ref->_school_id));
  if(spell_ref->_subschool_id) {
    str subschool_str = to_string_id_group(spell_ref->_subschool_id, get_name_subschool);
    printf(" (%s)", subschool_str);
    free(subschool_str);
  }
  if(spell_ref->_descriptor_id) {
    str descriptor_str = to_string_id_group(spell_ref->_descriptor_id, get_name_descriptor);
    printf(" [%s]", descriptor_str);
    free(descriptor_str);
  }
  printf(";\n");
}

void process_descriptor_ids(spell *ptr, str *argv, str *col, int length) {
  byte
    ids[get_num_descriptors()],
    id_count = 0;
  for(int i = 0; i < length; i++)
    if(atoi(argv[i]) == 1)
      ids[id_count++] = get_id_descriptor(col[i]);
  if(id_count > 0) {
    ptr->_descriptor_id = new_id_group(id_count);
    for(int i = 0; i < id_count; i++)
      add_ref_id_group(ptr->_descriptor_id, ids[i]);
  }
  else
    ptr->_descriptor_id = NULL;
}

void process_spell_levels(spell *ptr, str *argv, str *col, int length) {
  byte
    class_ids [get_num_classes()],
    levels [get_num_classes()],
    sl_count = 0;
  for(int i = 0; i < length; i++) {
    if(argv[i]) {
      class_ids[sl_count] = get_id_class(col[i]);
      levels[sl_count ++] = atoi(argv[i]);
    }
  }
  if(sl_count > 0)
  {
    ptr->_spell_levels = new_spell_level_group(sl_count);
    for(int i = 0; i < sl_count; i++)
    {
      add_spell_level_group(ptr->_spell_levels, new_spell_level(levels[i], class_ids[i]));
    }
  }
  else
  {
    ptr->_spell_levels = NULL;
  }
}

void process_subschool_ids(spell *ptr, str arg_str) {
  if(arg_str)
  {
    subschool_id ret_id = (subschool_id) atoi(arg_str);
    if(ret_id <= get_num_subschools())
    { // we have a normal subschool group with a single id
      ptr->_subschool_id = new_id_group(1);
      add_ref_id_group(ptr->_subschool_id, ret_id);
    }
    else // we have a group with multiple ids
      ptr->_subschool_id = get_subschool_id_group(ret_id - get_num_subschools());
  }
  else
    ptr->_subschool_id = NULL;
}
