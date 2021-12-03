#ifndef  TIME_UNIT_H
#define  TIME_UNIT_H
#define  TB_COEF_BIT 4
#include "logx.h"
#include "bit_def.h"
#include "str_def.h"
typedef        unsigned int second, sec;
typedef enum   time_unit    time_unit, tu;
typedef struct time_block   time_block, tb;
extern sec tu_to_sec ( tu  );
extern str tu_to_str ( tu  );
extern str tb_to_str ( tb  );
extern int str_to_tu ( str );
extern tu *new_tb    ( int, tu );
#endif
