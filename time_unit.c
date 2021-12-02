#include <stdlib.h>
#include <string.h>
#include "time_unit.h"

sec time_unit_to_seconds (time_unit _time_unit) {
  return time_unit_seconds[_time_unit];
}
  
char* time_unit_to_string (time_unit _time_unit) {
  return time_unit_strings[_time_unit];
}

char* time_block_to_string (time_block _time_block, char **_string_ref) {
  char _string = *_string_ref;
  if(_string == NULL)
    return NULL;
  else
    clear(_string);
  time_unit
    cur_time = _time_block._time_unit;
  char
    *cur_str = time_unit_strings[tar_tu];
  const int
    CUR_COEF = (int)_time_block._coefficient,
    PRODUCT  = (int)(cur_time == MIN_10) ? CUR_COEF * 10 : CUR_COEF;
    NULL_PAD = 1,                                                                      // space for null
    CHAR_PAD = NULL_PAD + 1,                                                           // single character + space for null
    PROD_PAD = 2 + (int)(log(PRODUCT)/log(10)),                                        // single space + number of decimal positions in the product
    FULL_PAD = PROD_PAD + (CUR_COEF <= 1 || cur_time == MIN_10) ? NULL_PAD : CHAR_PAD; // result of PROD_PAD + room for pluralization (time_unit_strings[MIN_10] already plural)
  
  _string = (char*) malloc(strlen(target) * sizeof(char) + FULL_PAD);
  sprintf(_string, "%d%c%s%c", PRODUCT, ' ', cur_str, '\0');

  return _string;
}

string_to_time_unit_ordinal (const char* _string) {
  for(int i = 0; i < NUM_TIME_UNITS; i++)
    if(!strcmp(_string, time_unit_strings[i]))
      return i;
  return -1;
}
#endif
