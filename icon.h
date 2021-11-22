#ifndef ICON_H
#define ICON_H

typedef struct icon
{
  int  id;
  char icon;
  char *name;
} icon;

/*  Macros  */
#define DOWN  1
#define UP    2
#define LEFT  3
#define RIGHT 4

//#define CHARACTER '@'
//#define MONSTER   'M'
//#define MONEY     '$'
//#define EMPTY     ' '
//#define FOLIAGE   '`'
//#define LIQUID    '~'
//#define ROCK      '.'
//#define WALL      '#'

/*  Function prototypes  */
//void InitIcons(void);
//void Draw(void);
//void FreeIcon(void);

int init_icon(void  *ext, int argc, char **argv, char **col);
void print_icon(const icon ICON, const char *header);
#endif /* ICON_H */
