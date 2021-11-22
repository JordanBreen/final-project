#ifndef SQL_LOADER_H
#define SQL_LOADER_H

typedef enum datatype {
  TYPE_ICON
} datatype;

void  db_init        (sqlite3 **, const char *, sqlite3_stmt *, char *); 
void  alloc_storage  (void **, datatype, int, int(**)(void *, int, char **, char **));
int   get_table_size (void *,  int, char **, char **);
void *load_table     (const char *, const char *, datatype, int *);
void  close_loader   (char *,  sqlite3 *);
#endif
