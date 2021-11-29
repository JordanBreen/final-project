#include <locale.h>
//#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>

//#include "gui.h"
//#include "icon.h"
//#include "sqlite_loader.h"
#include "utility.h"

int main()
{
  //const char
  //  db_file_name[]  = "project.db",
  //  db_table_name[] = "icon";

  const int END = 4;
  
  int       iA = 1, iB = 2, iC = 4;
  char      cA = 1, cB = 2, cC = 4;
  short int sA = 1, sB = 2, sC = 4;
  long int  lA = 1, lB = 2, lC = 4;

  for(int i = 0; i < END; i++) printf("Index %d of iA = %d is \'%d\'\n", i, iA, get_bit_state(i, INT, &iA));
  for(int i = 0; i < END; i++) printf("Index %d of iB = %d is \'%d\'\n", i, iA, get_bit_state(i, INT, &iB));
  for(int i = 0; i < END; i++) printf("Index %d of iC = %d is \'%d\'\n", i, iA, get_bit_state(i, INT, &iC));

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
