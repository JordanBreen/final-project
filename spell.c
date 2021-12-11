#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "spell.h"
#include "buf_def.h"

struct spell_attributes {
  byte
    _spell_resistance : 2,
    _shapeable        : 1,
    _dismissable      : 1,
    _mythic           : 1;
};

struct spell_components {
  byte
    _verbal       : 1,
    _somatic      : 1,
    _material     : 1,
    _focus        : 1,
    _divine_focus : 1,
    _is_costly    : 1;
  bit_16
    _cost;
  str
    _name;
};

struct spell {
//type - identifier ------------ storage
  spell_id   _id           : SPELL_ID_BIT;               // max 65,535 spells, expecting ~2,900 spells
  str        _name;
  school_id  _school_id    : SCHOOL_ID_BIT;
  id_group * _subschool_id;
  id_group * _descriptor_id;
  SL_group * _spell_levels;
  SL       * _SLA_level;

  id_group * _casting_time_id; // TO-DO
  str        _components_text;
  id_group * _range_id;            // struct, enclosing enum CLOSE, MEDIUM, LONG
  str _area_text;                  // struct
  str _effect_text;                // struct
  str _targets_text;          // struct
  str _duration_text;         // struct
  str _saving_throw_text;     // struct
  str _source_text;

  // text: /////////////////////
  str _description_brief;
  str _description_full;
  str _description_format;
  str _full_text;
  str _link_text;

  spell_components _components;
  spell_attributes _attributes;

  str _domain_text;           // string
  str _bloodline_text;        // string
  str _patron_text;           // string
  str _mythic_text;           // string
  str _mythic_augment_text;   // string
  bit_16 _material_cost;     // possible NULL value;
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
    POS_CASTING_TIME_ID   = 4,
    // Components: ///////////
    POS_COMPONENTS_TEXT   = 5,
    POS_VERBAL            = 6,
    POS_SOMATIC           = 7,
    POS_MATERIAL          = 8,
    POS_MATERIAL_COST     = 9,
    POS_MATERIAL_COSTLY   = 10,
    POS_FOCUS             = 11,
    POS_DIVINE_FOCUS      = 12,
    // Text: //////////////////
    POS_RANGE_TEXT        = 13,
    POS_AREA_TEXT         = 14,
    POS_EFFECT_TEXT       = 15,
    POS_TARGETS_TEXT      = 16,
    POS_DURATION_TEXT     = 17,
    POS_DISMISSABLE       = 18,
    POS_SHAPEABLE         = 19,
    POS_SAVING_THROW_TEXT = 20,
    POS_SPELL_RESIST_TEXT = 21,
    POS_SOURCE_TEXT       = 22,
    POS_DESCRIPTION_BRIEF = 23,
    POS_DESCRIPTION_FULL  = 24,
    POS_DESCRIPTION_FORM  = 25,
    POS_FULL_TEXT         = 26,
    POS_LINK_TEXT         = 27,
    // Spell Levels: //////////
    POS_SPELL_LEVEL_START = 28,
    POS_SPELL_LEVEL_END   = 53,
    POS_DEITY_LEVEL       = 54,
    POS_SLA_LEVEL         = 55,
    // Descriptors: ///////////
    POS_DESCRIPTOR_START  = 56,
    POS_DESCRIPTOR_END    = 83,
    // Etc: ///////////////////
    POS_BLOODLINE_TEXT    = 84,
    POS_DOMAIN_TEXT       = 85,
    POS_PATRON_TEXT       = 86,
    POS_MYTHIC            = 87,
    POS_MYTHIC_TEXT       = 88,
    POS_AUGMENTED_TEXT    = 89,
    POS_HAUNT_STAT_TEXT   = 90;
  // setup:
  int index = atoi(argv[POS_ID]) - 1;
  spell *ptr = (spell*)ext;

  ptr->_id = index + 1;
  ptr->_name = str_clone(argv[POS_NAME]);
  ptr->_school_id = atoi(argv[POS_SCHOOL_ID]);
  process_subschool_ids(ptr, argv[POS_SUBSCHOOL_ID]);
  process_descriptor_ids(ptr, &argv[POS_DESCRIPTOR_START], &col[POS_DESCRIPTOR_START], POS_DESCRIPTOR_END - POS_DESCRIPTOR_START);
  process_spell_levels(ptr, &argv[POS_SPELL_LEVEL_START], &col[POS_SPELL_LEVEL_START], POS_SPELL_LEVEL_END - POS_SPELL_LEVEL_START);

  // components:
  ptr->_components_text       = str_clone(argv[POS_COMPONENTS_TEXT]);
  ptr->_components._verbal    = atoi(argv[POS_VERBAL]);
  ptr->_components._somatic   = atoi(argv[POS_SOMATIC]);
  ptr->_components._material  = atoi(argv[POS_MATERIAL]);
  ptr->_components._focus     = atoi(argv[POS_FOCUS]);
  ptr->_components._is_costly = atoi(argv[POS_MATERIAL_COSTLY]);
  ptr->_components._cost      = (argv[POS_MATERIAL_COST]) ? atoi(argv[POS_MATERIAL_COST]) : 0;
  ptr->_components._name      = NULL;

  // attributes:
  ptr->_attributes._spell_resistance = 0;
  ptr->_attributes._dismissable = atoi(argv[POS_DISMISSABLE]);
  ptr->_attributes._shapeable   = atoi(argv[POS_SHAPEABLE]);
  ptr->_attributes._mythic      = atoi(argv[POS_MYTHIC]);
  
  ptr->_area_text = str_clone(argv[POS_AREA_TEXT]);
  ptr->_effect_text = str_clone(argv[POS_EFFECT_TEXT]);
  ptr->_targets_text = str_clone(argv[POS_TARGETS_TEXT]);
  ptr->_duration_text = str_clone(argv[POS_DURATION_TEXT]);
  ptr->_saving_throw_text = str_clone(argv[POS_SAVING_THROW_TEXT]);

  // description text:
  ptr->_description_brief  = str_clone(argv[POS_DESCRIPTION_BRIEF]);
  ptr->_description_full   = str_clone(argv[POS_DESCRIPTION_FULL]);
  ptr->_description_format = str_clone(argv[POS_DESCRIPTION_FORM]);

  // other text:
  ptr->_full_text = str_clone(argv[POS_FULL_TEXT]);
  ptr->_link_text = str_clone(argv[POS_LINK_TEXT]);

  ptr->_source_text = str_clone(argv[POS_SOURCE_TEXT]);
  ptr->_domain_text = str_clone(argv[POS_DOMAIN_TEXT]);
  ptr->_bloodline_text = str_clone(argv[POS_BLOODLINE_TEXT]);
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
  if(spell_ref->_spell_levels) {
    str spell_levels_str = to_str_spell_level_group(spell_ref->_spell_levels);
    printf("Level %s;\n", spell_levels_str);
    free(spell_levels_str);
  }
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
  if(sl_count > 0) {
    ptr->_spell_levels = new_spell_level_group(sl_count);
    for(int i = 0; i < sl_count; i++)
      add_spell_level_group(ptr->_spell_levels, new_spell_level(levels[i], class_ids[i]));
  }
  else
    ptr->_spell_levels = NULL;
}

void process_subschool_ids(spell *ptr, str arg_str) {
  if(arg_str) {
    subschool_id ret_id = (subschool_id) atoi(arg_str);
    if(ret_id <= get_num_subschools()) { // we have a normal subschool group with a single id
      ptr->_subschool_id = new_id_group(1);
      add_ref_id_group(ptr->_subschool_id, ret_id);
    }
    else // we have a group with multiple ids
      ptr->_subschool_id = get_subschool_id_group(ret_id - get_num_subschools());
  }
  else
    ptr->_subschool_id = NULL;
}
