#ifndef  TIME_UNIT_H
#define  TIME_UNIT_H
#define  TB_COEF_BIT 4
#include "logx.h"
#include "bit_def.h"
#include "str_def.h"

typedef unsigned int sec;

typedef enum time_unit {
  SECOND = 0,
  ROUND  = 1,
  MIN_01 = 2,
  MIN_10 = 3,
  HOUR   = 4,
  DAY    = 5,
  WEEK   = 6,
  YEAR   = 7,
  NUM_TIME_UNITS
} time_unit;

typedef struct time_block {
  bit08
    _coefficient : TB_COEF_BIT,               // +4 [0-15]
    _time_unit   : log2_ceil(NUM_TIME_UNITS); // +4
} time_block;

extern sec tu_to_sec ( time_unit  );
extern str tu_to_str ( time_unit  );
extern str tb_to_str ( time_block );
extern int str_to_tu ( str        );
extern time_block *new_tb ( int, time_unit );

#endif
