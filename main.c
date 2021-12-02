#include <locale.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include "spell.h"

int main()
{
  time_block *tb = NULL;
  time_unit   tu = ROUND;
  str tu_str = tu_to_str(tu);
  int tu_ord = tu;
  sec tu_sec = tu_to_sec(tu);
  printf("tu     = ROUND\n");
  printf("tu_str = %s\n", tu_str);
  printf("tu_ord = %d\n", tu_ord);
  printf("tu_sec = %d\n", tu_sec);

  tb = new_tb(5, tu);
  str tb_str = tb_to_str(*tb);
  printf("tb_str = %s\n", tb_str);

  //str
  //  db_file_name[]  = "Pathfinder.db",
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
