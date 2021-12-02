#ifndef  TIME_UNIT_H
#define  TIME_UNIT_H

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

const sec time_unit_seconds[] = {
  1,       // SECOND (1:1)
  6,       // ROUND
  60,      // MIN_01
  600,     // MIN_10
  3600,    // HOUR
  86400,   // DAY
  604800,  // WEEK
  31536000 // YEAR (365 days)
}

const char *time_unit_strings[] = {
  "second",
  "round",
  "minute",
  "minutes",
  "hour",
  "day",
  "week",
  "year"
};

typedef struct time_block {
  unsigned char // 8/8
  _coefficient : 4,                                     // +4 [0-15]
  _time_unit   : (int)ceil(log(NUM_TIME_UNITS)/log(2)), // +4
} time_block;

sec   time_unit_to_seconds        (time_unit);
char* time_unit_to_string         (time_unit);
char* time_block_to_string        (time_block);
int   string_to_time_unit_ordinal (char **);

#endif
