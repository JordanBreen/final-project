#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "time_unit.h"

static const sec time_unit_seconds[] = {
  1,       // SECOND (1:1)
  6,       // ROUND
  60,      // MIN_01
  600,     // MIN_10
  3600,    // HOUR
  86400,   // DAY
  604800,  // WEEK
  31536000 // YEAR (365 days)
};

static const str time_unit_strings[] = {
  "second",
  "round",
  "minute",
  "minutes",
  "hour",
  "day",
  "week",
  "year"
};

sec tu_to_sec (time_unit arg_tu) { return time_unit_seconds[arg_tu]; } 
str tu_to_str (time_unit arg_tu) { return time_unit_strings[arg_tu]; }

str tb_to_str (time_block arg_tb) {
  time_unit
    cur_tu   = arg_tb._time_unit;
  str
    cur_str  = time_unit_strings[cur_tu],
    ret_str  = NULL;
  const int
    CUR_COEF = (int)arg_tb._coefficient,
    PRODUCT  = (int)(cur_tu == MIN_10) ? CUR_COEF * 10 : CUR_COEF,
    NULL_PAD = 1,
    CHAR_PAD = NULL_PAD + 1,
    PROD_PAD = 1 + log10_ceil(PRODUCT),
    FULL_PAD = PROD_PAD + ((CUR_COEF <= 1 && cur_tu != MIN_10) ? NULL_PAD : CHAR_PAD);

  printf("CUR_COEF = %d\n", CUR_COEF);
  printf("NULL_PAD = %d\n", NULL_PAD);
  printf("CHAR_PAD = %d\n", CHAR_PAD);
  printf("PROD_PAD = %d\n", PROD_PAD);
  printf("FULL_PAD = %d\n", FULL_PAD);

  ret_str = (str) malloc(strlen(cur_str) * sizeof(char) + FULL_PAD);
  sprintf(ret_str, "%d%c%s%s", PRODUCT, ' ', cur_str, ((FULL_PAD - PROD_PAD) != NULL_PAD) ? "s\0" : "\0");
  return ret_str;
}

int str_to_tu (str arg_str) {
  for(int i = 0; i < NUM_TIME_UNITS; i++)
    if(!strcmp(arg_str, time_unit_strings[i]))
      return i;
  return -1;
}

time_block *new_tb (int coef, time_unit arg_tu) {
  if(!in_bit_range(coef, TB_COEF_BIT))
     return NULL;
  time_block *ret_tb = (time_block *) malloc(sizeof(time_block));
  ret_tb -> _coefficient = coef;
  ret_tb -> _time_unit   = arg_tu;
  return ret_tb;
}
