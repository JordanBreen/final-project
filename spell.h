#ifndef  SPELL_H
#define  SPELL_H
#define  NUM_SPELL_LEVELS 10 // range 0-9
#include "class.h"
#include "time_unit.h"
#include "logx.h"
#include "bit_def.h"
#include "str_def.h"

typedef unsigned short spell_id;

typedef struct spell_component_flags {
  bit_8
    verbal       : 1,
    somatic      : 1,
    material     : 1,
    focus        : 1,
    divine_focus : 1;
} spell_component_flags;

typedef struct spell_attribute_flags {
  bit_8
    spell_resistance : 2,
    shapeable        : 1,
    dismissable      : 1,
    mythic           : 1;
} spell_attribute_flags;

/*
typedef struct spell_level_by_class spell_level_by_class;
#ifdef CLASS_H
const int NUM_CLASS_TYPES = get_num_class_types();
#endif
struct spell_level_by_class {
  bit_16
    _level      : log2_ceil(NUM_SPELL_LEVELS), // 4 bits [0 - 15] for spell level [0 - 9]
    _class_type : log2_ceil(NUM_CLASS_TYPES),  // 3 bits [0 -  8] for class type  [0 - 6] 
    _class_id   : 4;
};
//#endif
*/

typedef enum answer {
  NO       = 0,
  YES      = 1,
  SEE_TEXT = 2,
  NUM_ANSWERS
} answer;

typedef enum saving_throw_type {
  FORT = 0,
  REF  = 1,
  WILL = 2,
  ALL  = 3,
  NUM_SAVING_THROW_TYPES
} saving_throw_type;

typedef enum range_type {
  STATIC_RANGE    = 0,
  PERSONAL_RANGE  = 1,
  TOUCH_RANGE     = 2,
  CLOSE_RANGE     = 3,
  MEDIUM_RANGE    = 4,
  LONG_RANGE      = 5,
  UNLIMITED_RANGE = 6,
  NUM_RANGE_TYPES
} range_type;

static const short range_type_bases[] = {
  0,   // STATIC
  0,   // PERSONAL 
  0,   // TOUCH
  25,  // CLOSE
  100, // MEDIUM
  400  // LONG
};

typedef enum growth_type {
  STATIC = 0,
  SCALES = 1
} growth_type;

typedef struct duration //{
  //bit_8
  //  _growth_type : 1,                          // +1 bit
  //  _time_unit   : log2_ceil(NUM_TIME_UNITS);  // 3 bits [0 -  8] for time_units [0 - 7]
/*}*/ duration;

typedef struct spell spell;

//extern int  parse_spell (void*, int, char**, char**);
extern void print_spell (spell*);

#endif
