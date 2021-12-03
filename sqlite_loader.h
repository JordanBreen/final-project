#ifndef SQL_LOADER_H
#define SQL_LOADER_H
#include <sqlite3.h>
#include "str_def.h"

typedef enum object object, obj;

void  db_init         (sqlite3**, const str, sqlite3_stmt*); 
void  alloc_storage   (void**, object, int, int(**)(void*, int, str*, str*));
int   count_rows      (void*, int, str*, str*);
void* load_table      (const str, const str, object, int*);
int   peek_table_size (const str, const str);
int   get_table_size  (sqlite3*, const str);
void  close_loader    (str,  sqlite3*);

#endif
