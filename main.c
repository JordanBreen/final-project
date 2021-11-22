#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include <form.h>
#include <menu.h>
#include <panel.h>

#include "icon.h"
#include "sqlite_loader.h"

int main()
{
  const char
    db_file_name[]  = "project.db",
    db_table_name[] = "icon",
   *header = NULL;
  icon
    *icons;

  icons = (icon *)load_table(db_file_name, db_table_name, TYPE_ICON);

  //for(int i = 0; i < sizeof(icons) / sizeof(icons[0]); i++)
  for(int i = 0; i < 5; i++)
    print_icon(&icons[i], header);
}
