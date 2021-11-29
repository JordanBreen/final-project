#include "utility.h"
int get_byte_size (datatype_t datatype) { return datatype_byte_sizes [datatype]; }
int get_bit_size  (datatype_t datatype) { return datatype_bit_sizes  [datatype]; }
int get_bit_state (int index, datatype_t datatype, void* bit_data) {
  if(index > get_bit_size(datatype) || index < 0)
    return OUT_OF_RANGE;
  else
    return (*((long int*)bit_data)>>index)&1;
}

