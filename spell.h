#ifndef SPELL_H
#define SPELL_H

// Notes: byte storage by datatype
// short int: 2 bytes, 16 bits
// char: 1 byte, 8 bits
#define NUM_SPELL_LEVELS 10; // range 0-9
typedef enum spell_component {
  VERBAL,
  SOMATIC,
  MATERIAL,
  FOCUS,
  DIVINE_FOCUS
} spell_component;
typedef enum spell_feature {
  SPELL_RESISTANCE,
  SHAPEABLE,
  DISMISSABLE,
  MYTHIC
} spell_feature;
typedef enum save {
  FORT,
  REF,
  WILL
} save;
typedef struct spell {
//type - identifier ------------- storage
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
  unsigned char components; // 5/8 bit flags
  // verbal, somatic, material, focus, divine_focus;
  unsigned char features; // 5/8 bit flags
  // spell_resistance, shapeable, dimissable, mythic
  unsigned char * spell_level_by_class;
  char * SLA_level;            // possible part of another flag structure
  char * domain_text;          // string
  char * bloodline_text;       // string
  char * patron_text;          // string
  char * mythic_text;          // string
  char * mythic_augment_text;  // string
  // char * haunt_stats_text;  // string possibly ignore
  
  char * descriptors;          // bool flag,  expecting 28 descriptors, 28 bits == >3 bytes, unsigned int, assert 4-byte int
  // char * link_text;         // string, possibly skip, same as name member
  unsigned short id;           // max 65,535 spells, expecting ~2,900 spells
  unsigned short *material_cost; // possible NULL value;
} Spell;

/*
typedef enum school {
  PLACE_HOLDER
} School;
*/
#endif
