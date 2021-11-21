#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <sys/ioctl.h>
#include "icon.h"
#include "sqlite_loader.h"

void print_icon(WINDOW *win, char icon, int x, int y);

int main (int argc, char *argv[]) {
  const int
    NUM_ICONS = 4;
  char
    db_table_name[] = "icon",
    db_file_name[]  = "project.db",
    buffer[BUFSIZ];
  icon
    *icons = NULL;

  icons = (icon*) load_table(db_file_name, db_table_name, TYPE_ICON, NUM_ICONS);
  
  WINDOW *main_window, *sub_window;
  int ch;

  struct winsize ws;
  if ( ioctl(0, TIOCGWINSZ, &ws) < 0 ) {
    perror("couldn't get window size");
    exit(EXIT_FAILURE);
  }
  
  const int
    MAIN_WINDOW_WIDTH  = ws.ws_col,
    MAIN_WINDOW_HEIGHT = ws.ws_row,

    SUB_WINDOW_WIDTH  = MAIN_WINDOW_WIDTH  - 2,
    SUB_WINDOW_HEIGHT = MAIN_WINDOW_HEIGHT - 20,

    PAD = 1;
  int
    x_pos = PAD,
    y_pos = PAD*2;

  if ((main_window = initscr()) == NULL) {
    fprintf(stderr, "Error initialising ncurses.\n");
    exit(EXIT_FAILURE);
  }
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    exit(EXIT_FAILURE);
  }
  start_color();
  init_pair(1, COLOR_RED, COLOR_BLACK);

  attron(COLOR_PAIR(1));

  noecho();
  keypad(main_window, TRUE);
  curs_set(0);
  
  int i = 0;
  int
    x, y,
    x_min, y_min,
    x_max, y_max;
  getyx    (sub_window, y_min, x_min);
  getmaxyx (sub_window, y_max, x_max);

  //y+=5;
  //x+=5;
  //y = y_max - y_min*2;
  //y = 1;
  y = x = x_max - x_min*2;

  char my_icon = icons[i].icon;
  
  sub_window = subwin(main_window, SUB_WINDOW_HEIGHT, SUB_WINDOW_WIDTH, y_pos, x_pos);
  //wborder(main_window, '|', '|', '-', '-', '+', '+', '+', '+');
  wborder(sub_window,  '|', '|', '-', '-', '+', '+', '+', '+');
  /*
  mvwprintw(sub_window, 1, 1, "-- icons[%d] --", i);
  mvwprintw(sub_window, 2, 1, "id   = %d", icons[i].id);
  mvwprintw(sub_window, 3, 1, "icon = %c", icons[i].icon);
  mvwprintw(sub_window, 4, 1, "name = %s", icons[i].name);
  mvwprintw(sub_window, 5, 1, "Press 'q' to quit");
  */
  
  refresh();
  print_icon(sub_window, my_icon, x, y);
  while ((ch = getch()) != 'q') {
    switch(ch) {
    case KEY_LEFT:  --x; print_icon(sub_window, my_icon, x, y); break;
    case KEY_RIGHT: ++x; print_icon(sub_window, my_icon, x, y); break;
    case KEY_UP:    --y; print_icon(sub_window, my_icon, x, y); break;
    case KEY_DOWN:  ++y; print_icon(sub_window, my_icon, x, y); break;
	
    }
  }

  attroff(COLOR_PAIR(1));

  delwin(sub_window);
  delwin(main_window);
  endwin();
  refresh();
  
  return EXIT_SUCCESS;
}

void print_icon(WINDOW* win, char icon, int x, int y) {
  mvwaddch(stdscr, y, x, icon);
  mvwprintw(stdscr, 1, 1, "Pos=(%d,%d)", x, y);
  refresh();
}
