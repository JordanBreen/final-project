#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <time.h>
#include "spell.h"
#include "thread.h"
#include "bit_def.h"

const byte NUM_THREADS = 4;

int main()
{
  init_resources(NUM_THREADS);

  //print_classes();

  
  
  spell *test;
  for(int i = 1; i <= 1; i++) {
   test = load_spell(i);
   free(test);
  }
  /* time_unit testing
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
  */
  
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
  free_resources(NUM_THREADS);
  return 0;
}
