#ifndef SQL_LOADER_H
#define SQL_LOADER_H

typedef enum datatype {
  TYPE_ICON
} datatype;

void  alloc_storage (void **, datatype, int, int(**)(void *, int, char **, char **));
int   init_icons    (void *,  int, char **, char **);
void *load_table    (char *,  char *, datatype, int);

#endif
