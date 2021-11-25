#include <stdio.h>
#include <stdlib.h>
#include "gui.h"

UI *create_UI() { 
  UI *ui = (UI *) malloc(sizeof(UI));
  ui->min_y = 0;
  ui->min_x = 0;
  ui->max_y = LINES;
  ui->max_x = COLS;
  
  int main_height = ui->max_y - UI_PAD;
  int main_width  = ui->max_x;
  int main_y      = ui->min_y;
  int main_x      = ui->min_x;

  int inner_width = main_width - UI_PAD * 2;
  int inner_y     = main_y + UI_PAD;
  int inner_x     = main_x + UI_PAD;
    
  int view_height = ui->max_y / 2 - UI_PAD * 2 + 10;
  int view_width  = inner_width;
  int view_y      = main_y + UI_PAD * 2;
  int view_x      = inner_x;

  int head_height = UI_PAD;
  int head_width  = inner_width;
  int head_y      = inner_y;
  int head_x      = inner_x;

  int log_height = main_height - view_height - 4;
  int log_width  = inner_width;
  int log_y      = view_y + view_height;
  int log_x      = inner_x;

  int cmd_height = UI_PAD;
  int cmd_width  = inner_width;
  int cmd_y      = log_y + log_height;
  int cmd_x      = inner_x;

  ui->main_window = newwin (main_height, main_width, main_y, main_x);
  ui->view_window = newwin (view_height, view_width, view_y, view_x);
  ui->head_window = newwin (head_height, head_width, head_y, head_x);
  ui->log_window  = newwin (log_height,  log_width,  log_y,  log_x );
  ui->cmd_window  = newwin (cmd_height,  cmd_width,  cmd_y,  cmd_x );
  
  box ( ui->main_window, 0, 0);
  box ( ui->view_window, 0, 0);
  box ( ui->log_window,  0, 0);

  view_print (ui, "View Window: Offset 0\n", 0 );
  //view_print (ui, "View Window: Offset 1", 1 );
  head_print (ui, "Header Window"            );
  log_print  (ui, "Log Window: Offset 0\n", 0  );
  //log_print  (ui, "Log Window: Offset 1", 1  );
  cmd_print  (ui, ": "                       );
  
  ui_refresh(ui);

  view_print (ui, "View Window: Offset 1\n", 1 );
  log_print  (ui, "Log Window: Offset 1\n",  1 );

  ui_refresh(ui);
  
  return ui;
}

void view_cursor_start (UI *ui, int *y, int *x) { getyx(ui->view_window, *y, *x); *x+=1; *y+=1; }
void head_cursor_start (UI *ui, int *y, int *x) { getyx(ui->head_window, *y, *x); *x+=1;        }
void log_cursor_start  (UI *ui, int *y, int *x) { getyx(ui->log_window,  *y, *x); *x+=1; *y+=1; }
void cmd_cursor_start  (UI *ui, int *y, int *x) { getyx(ui->cmd_window,  *y, *x);               }

void view_print (UI *ui, char *str, int row_offset) {
  int x, y;
  view_cursor_start(ui, &y, &x);
  mvwaddstr(ui->view_window, y+row_offset, x, str);
}

void head_print (UI *ui, char *str) {
  int x, y;
  head_cursor_start(ui, &y, &x);
  mvwaddstr(ui->head_window, y, x, str);
}

void log_print (UI *ui, char *str, int row_offset) {
  int x, y;
  log_cursor_start(ui, &y, &x);
  mvwaddstr(ui->log_window, y+row_offset, x, str);
}

void cmd_print (UI *ui, char *str) {
  int x, y;
  cmd_cursor_start(ui, &y, &x);
  mvwaddstr(ui->cmd_window, y, x, str);
}

void ui_refresh (UI *ui) {
  wrefresh(ui->main_window);
  wrefresh(ui->view_window);
  wrefresh(ui->head_window);
  wrefresh(ui->log_window);
  wrefresh(ui->cmd_window);
}
