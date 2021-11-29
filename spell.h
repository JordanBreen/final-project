#ifndef SPELL_H
#define SPELL_H

// Notes: byte storage by datatype
// short int: 2 bytes, 16 bits
// char: 1 byte, 8 bits
#define NUM_SPELL_LEVELS 10; // range 0-9
typedef struct spell {
//type - identifier ------------- storage
  char * name;                 // string
  char * school;               // enum
  char * subschool;            // enum
  char * descriptor;           // enum
  char * spell_level;          // ptr array to 'classes'
  char * casting_time;         // struct
  char * components_text;      // text
  //char   costly_component;   // will be determined elsewhere, skip
  char * range;                // struct
  char * area;                 // struct
  char * effect;               // struct
  char * targets;              // struct
  char * duration;             // struct
  char   dismissible;          // bool 2
  char   shapeable;            // bool 3
  char * saving_throw;         // struct
  char * spell_resistance;     // bool 4
  char * description_full;     // string
  char * description_short;    // string
  char * description_formated; // string
  char * source;               // enum
  char * full_text;            // string
  unsigned char components;    // bool flag (5), max 8 (unsigned char)
  //char verbal;               // bool 1
  //char somatic;              // bool 2
  //char material;             // bool 3
  //char focus;                // bool 4
  //char divine_focus;         // bool 5
  char * spell_level_by_class; // flag, range 0-9 (16) 4 bits ea, expecting max 16 classes, 4*16 = 64 bits == 8 bytes, unsigned long
  char * SLA_level;            // possible part of another flag structure
  char * domain_text;          // string
  char * descriptors;          // bool flag,  expecting 25 descriptors, 25 bits == >3 bytes, unsigned int, assert 4-byte int
  char * link_text;            // string
  unsigned short id;           // max 65,535 spells, expecting ~1,600 spells








} Spell;

/*
typedef enum school {
  PLACE_HOLDER
} School;
*/
#endif
