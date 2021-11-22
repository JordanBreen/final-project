#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "icon.h"

int init_icon (void  *ext,
               int    argc,
               char **argv,
               char **col) {
  const int
    index_id   = 0,
    index_icon = 1,
    index_name = 2;
  int
    index;
  icon
    *icons = (icon *)ext;

  index             = atoi(argv[index_id]) - 1;
  icons[index].id   = index + 1;
  icons[index].icon = argv[index_icon][0];
  icons[index].name = (char*) malloc(strlen(argv[index_name])+1);
  strcpy(icons[index].name, argv[index_name]);

  return 0;
}

void print_icon (const icon *icon_ptr,
		 const char *header_str) {
  printf("icon::print_icon()  %s\n", header_str ? header_str:"");
  printf("  id:   %d\n", icon_ptr->id);
  printf("  icon: \'%c\'\n", icon_ptr->icon);
  printf("  name: \"%s\"\n", icon_ptr->name);
}
