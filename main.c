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

static const byte NUM_THREADS = 4;
spell_id   spell_ids_to_load[] = {1, 5, 10, 15, 20};
size_t     num_spell_ids_to_load = sizeof(spell_ids_to_load) / sizeof(*spell_ids_to_load);
spell    **loaded_spells;
size_t     num_loaded_spells = sizeof(spell_ids_to_load) / sizeof(*spell_ids_to_load);
int main()
{
  init_resources(NUM_THREADS);

  //printf("number of classes = %d\n", get_num_classes());
  //print_classes();
  //printf("press any key to continue: ");
  //printf("%c\n", getc(stdin));

  load_spells(NUM_THREADS, spell_ids_to_load, num_spell_ids_to_load, &loaded_spells);
  print_spells(loaded_spells, num_loaded_spells);
  /*
  spell *test;
  for(int i = 1; i <= 2000; i++) {
   test = load_spell(i);
   free(test);
  }*/
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
