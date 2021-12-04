#ifndef SQL_LOADER_H
#define SQL_LOADER_H
#include <sqlite3.h>
#include "str_def.h"

extern void  db_init         (sqlite3**, const str, sqlite3_stmt*); 
extern int   count_rows      (void*, int, str*, str*);
extern void* load_table      (const str, const str,  int(*)(void*, int, str*, str*), size_t, int*);
extern int   peek_table_size (const str, const str);
extern int   get_table_size  (sqlite3*, const str, const str);
extern void  close_loader    (str,  sqlite3*);

#endif
