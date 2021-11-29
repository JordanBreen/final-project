#include <stdlib.h>
#ifndef UTILITY_H
#define UTILITY_H

#define OUT_OF_RANGE -1
#define UNKNOWN_TYPE -2
#define BITS_IN_BYTE  8

typedef enum datatype_t {
  CHAR,  // 1 byte
  SHORT, // 2 bytes
  INT,   // 2 or 4 bytes, assume 4
  LONG   // 8 (64 bit OS), 4 (32 bit OS), assume 8
} datatype_t;

static const size_t datatype_byte_sizes[] = {
  sizeof(char),
  sizeof(short int),
  sizeof(int),
  sizeof(long int)
};

static const size_t datatype_bit_sizes[] = {
  datatype_byte_sizes[0] * BITS_IN_BYTE,
  datatype_byte_sizes[1] * BITS_IN_BYTE,
  datatype_byte_sizes[2] * BITS_IN_BYTE,
  datatype_byte_sizes[3] * BITS_IN_BYTE
};

int get_byte_size (datatype_t);
int get_bit_size  (datatype_t);
int get_bit_state (int, datatype_t, void*);

#endif
