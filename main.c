#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "icon.h"
#include "sqlite_loader.h"

int main (int argc, char *argv[]) {
  const int NUM_ICONS = 4;
  char
    db_table_name[]  = "icon",
    db_file_name[] = "project.db";
  icon
    *icons = NULL;

  icons = (icon*) load_table(db_file_name, db_table_name, TYPE_ICON, NUM_ICONS);
  
  printf("main:main(): loaded icons from %s -> %s\n", db_file_name, db_table_name);
  for(int i = 0; i < NUM_ICONS; i++)
    printf("\ticons[%d]: id=%d icon=%c name=%s\n", i, icons[i].id, icons[i].icon, icons[i].name);
  
  return 0;
}
