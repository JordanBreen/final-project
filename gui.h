#include <ncursesw/ncurses.h>
#include <stdarg.h>

#define UI_PAD 1

typedef struct UI {
  WINDOW
    *main_window,
    *view_window,
    *head_window,
    *log_window,
    *cmd_window;
  int
    min_x, min_y,
    max_x, max_y;
} UI;

UI * create_UI         ();
void view_cursor_start (UI *ui, int *y, int *x);
void head_cursor_start (UI *ui, int *y, int *x);
void log_cursor_start  (UI *ui, int *y, int *x);
void cmd_cursor_start  (UI *ui, int *y, int *x);
void view_print        (UI *ui, char *str, int row_offset);
void log_print         (UI *ui, char *str, int row_offset);
void head_print        (UI *ui, char *str);
void cmd_print         (UI *ui, char *str);
void ui_refresh        (UI *ui);

