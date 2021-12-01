#include <locale.h>
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

//#include "gui.h"
//#include "sqlite_loader.h"

int main()
{
  //const char
  //  db_file_name[]  = "project.db",
  //  db_table_name[] = "icon";

  /* Icon testing
  icon *icons;
  int num_icons;
  icons = (icon *)load_table(db_file_name, db_table_name, TYPE_ICON, &num_icons);
  */
  
  /* ncurses initialization
  fwide(stdout, 1);
  setlocale(LC_ALL, "");
  initscr();
  UI *ui = create_UI(stdscr);
  wgetch(ui->cmd_window);
  endwin();
  */
  return 0;
}
