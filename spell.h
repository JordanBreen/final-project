#ifndef  SPELL_H
#define  SPELL_H
#define  SPELL_ID_BIT 12
#define  NUM_SPELL_LEVELS 10 // range 0-9
// structures:
#include "class.h"
#include "descriptor.h"
#include "range.h"
#include "school.h"
#include "spell.h"
#include "spell_level.h"
#include "subschool.h"
#include "time_unit.h"
// utilities:
#include "logx.h"
#include "bit_def.h"
#include "str_def.h"
#include "id_group.h"

typedef bit_16 spell_id;

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

typedef struct duration duration;

typedef struct spell spell;

extern spell *load_spell(spell_id);
extern void print_spell (spell*);

#endif
