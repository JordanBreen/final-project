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
  char * spell_level_text;     // ptr array to 'classes'
  char * casting_time;         // struct
  char * components_text;      // text
  //char   costly_component;   // will be determined elsewhere, skip
  char * range;                // struct, enclosing enum CLOSE, MEDIUM, LONG
  char * area;                 // struct
  char * effect;               // struct
  char * targets;              // struct
  char * duration;             // struct
  //char   dismissible;          // bool 2
  //char   shapeable;            // bool 3
  char * saving_throw;         // struct
  //char * spell_resistance;     // bool 4
  char * description_full;     // string
  char * description_short;    // string
  char * description_formated; // string
  char * source;               // enum
  char * full_text;            // string
  // Components
  unsigned char components;    // bool flag (5), max 8 (unsigned char)
  // verbal;          // bool 01
  // somatic;         // bool 02
  // material;        // bool 03
  // focus;           // bool 04
  // divine_focus;    // bool 05
  // Qualities
  // spell_resistance // bool 06 (1)
  // shapeable,       // bool 07 (2)
  // dimissable       // bool 08 (3)
  // mythic           // bool 09 (4)
  // ruse             // bool 10 (5)
  // draconic         // bool 11 (6)
  // meditative       // bool 12 (7)
  char * spell_level_by_class;
  // flag,range0-9 4 bits ea, expecting max 16 classes, 4*16 = 64 bits == 8 bytes, unsigned long
  // correction: expecting more classes, could possibly exclude additional classes (+10)
  char * SLA_level;            // possible part of another flag structure
  char * domain_text;          // string
  char * bloodline_text;       // string
  char * patron_text;          // string
  char * mythic_text;          // string
  char * mythic_augment_text;  // string
  // char * haunt_stats_text;  // string possibly ignore
  char * descriptors;          // bool flag,  expecting 25 descriptors, 25 bits == >3 bytes, unsigned int, assert 4-byte int
  // char * link_text;         // string, possibly skip, same as name member
  unsigned short id;           // max 65,535 spells, expecting ~1,600 spells
  unsigned short *material_cost; // possible NULL value;








} Spell;

/*
typedef enum school {
  PLACE_HOLDER
} School;
*/
#endif
