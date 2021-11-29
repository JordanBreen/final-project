#include <locale.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>

#include "gui.h"
#include "icon.h"
#include "sqlite_loader.h"

int main()
{
  const char
    db_file_name[]  = "project.db",
    db_table_name[] = "icon";;
  icon
    *icons;

  fwide(stdout, 1);
  setlocale(LC_ALL, "");

  int num_icons;
  icons = (icon *)load_table(db_file_name, db_table_name, TYPE_ICON, &num_icons);

  initscr();

  UI *ui = create_UI(stdscr);
  //for(int i = 0; i < num_icons; i++)
  //{
  //  mvprintw(0, i*10, "%d", icons[i].id);
  //  mvprintw(1, i*10, "%lc", icons[i].icon);
  //  mvprintw(2, i*10, "%s", icons[i].name);
  //}
  // refresh();
  wgetch(ui->cmd_window);
  endwin();
  return 0;
}
