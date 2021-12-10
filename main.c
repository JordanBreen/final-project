#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include "spell.h"
void init_resources();
void free_resources();
int main()
{
  printf("%s:%s() ENTRY\n", __FILE__, __func__);
  init_resources();
  printf("%s:%s() RESOURCES INITIALIZED\n", __FILE__, __func__);

  spell *test;
  for(int i = 1; i <= 5 ; i++) {
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
  free_resources();
  return 0;
}
void init_resources() {
  init_class_types();
  printf("%s:%s() CLASS TYPES INITIALIZED\n", __FILE__, __func__);
  init_classes();
  printf("%s:%s() CLASSES INITIALIZED\n", __FILE__, __func__);
  init_descriptors();
  printf("%s:%s() DESCRIPTORS INITIALIZED\n", __FILE__, __func__);
  init_ranges();
  init_schools();
  init_subschools();
  init_time_units();
}
void free_resources() {
  free_class_types();
  free_classes();
  free_descriptors();
  free_ranges();
  free_schools();
  free_subschools();
  free_time_units();
}
