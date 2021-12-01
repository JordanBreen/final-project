#ifndef  SPELL_H
#define  SPELL_H
#define  NUM_SPELL_LEVELS 10 // range 0-9
#include <math.h>

typedef struct spell_component_flags {
  unsigned char       // v/8
    verbal       : 1, // 1
    somatic      : 1, // 2
    material     : 1, // 3
    focus        : 1, // 4
    divine_focus : 1; // 5
} spell_component_flags;

typedef struct spell_attribute_flags {
  unsigned char           // v/8
    spell_resistance : 2, // 2
    shapeable        : 1, // 3
    dismissable      : 1, // 4
    mythic           : 1; // 5
} spell_attribute_flags;

typedef struct spell_level_by_class {
  unsigned char
  level : (int)ceil(log(NUM_SPELL_LEVELS)/log(2));
} spell_level_by_class;

typedef enum answer {
  NO       = 0,
  YES      = 1,
  SEE_TEXT = 2
} answer;

typedef enum save {
  FORT,
  REF,
  WILL
} save;

typedef struct spell {
//type - identifier ------------- storage
  unsigned short  id;           // max 65,535 spells, expecting ~2,900 spells
  char * name;                 // string
  char * school;               // enum
  char * subschool;            // enum
  char * descriptor;           // enum
  char * spell_level_text;     // ptr array to 'classes'
  char * casting_time;         // struct
  char * components_text;      // text
  //char costly_component;     // will be determined elsewhere, skip
  char * range;                // struct, enclosing enum CLOSE, MEDIUM, LONG
  char * area;                 // struct
  char * effect;               // struct
  char * targets;              // struct
  char * duration;             // struct
  char * saving_throw;         // struct
  char * description_full;     // string
  char * description_short;    // string
  char * description_formatted;// string
  char * source;               // enum
  char * full_text;            // string
  // Components
  spell_component_flags components;
  spell_attribute_flags attributes;
  unsigned char * spell_level_by_class;
  char * SLA_level;            // possible part of another flag structure
  char * domain_text;          // string
  unsigned char * bloodline_text;       // string
  unsigned char * patron_text;          // string
  unsigned char * mythic_text;          // string
  unsigned char  * mythic_augment_text;  // string
  unsigned int   * descriptors;          // bool flag,  expecting 28 descriptors, 28 bits == >3 bytes, unsigned int, assert 4-byte int
  unsigned short * material_cost; // possible NULL value;

  // SKIPPED COLUMNS: //
  // costly_component
  // haunt_stats_text
  // link_text
} spell;

int  parse_spell (void *, int, char **, char **);
void print_spell (spell *);

#endif
