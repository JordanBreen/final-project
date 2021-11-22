#ifndef ICON_H
#define ICON_H

typedef struct icon {
  int   id;
  char  icon;
  char *name;
} icon;

/*  Macros  */
#define DOWN  1
#define UP    2
#define LEFT  3
#define RIGHT 4

int  init_icon  (void  *ext, int argc, char **argv, char **col);
void print_icon (const icon *icon_ptr, const char *header_str);

#endif
