#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "spell.h"

struct spell {
//type - identifier ------------ storage
  spell_id _id;               // max 65,535 spells, expecting ~2,900 spells
  str _name;                  // string
  str _school;                // enum
  str _subschool;             // enum
  str _descriptor;            // enum
  str _spell_level_text;      // ptr array to 'classes'
  str _casting_time;          // struct
  str _components_text;       // text
  str _range;                 // struct, enclosing enum CLOSE, MEDIUM, LONG
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

void print_spell (spell *spell_ptr) {

}
