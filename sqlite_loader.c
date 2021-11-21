#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "icon.h"

void *load_table (char     *db_file_name,
	          char     *db_table_name,
	          datatype  storage_datatype,
	          int       size) {
  void *storage;
  sqlite3 *db;
  sqlite3_stmt *res;
  char *err_msg, sql[BUFSIZ];
  int rc, (*callback)(void *, int, char **, char **) = NULL;
  ////////////////////////////////////////////////////////////////////////////
  rc = sqlite3_open(db_file_name, &db);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  ////////////////////////////////////////////////////////////////////////////
  rc = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &res, 0);      
  if (rc != SQLITE_OK) {      
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    exit(1);
  }
  ///////////////////////////////////////////////////////////////////////////
  strcpy(sql, "SELECT * FROM ");
  strcat(sql, db_table_name);

  alloc_storage(&storage, storage_datatype, size, &callback);
  ///////////////////////////////////////////////////////////////////////////
  rc = sqlite3_exec(db, sql, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data\n");
    fprintf(stderr, "SQL error: %s\n", err_msg);
    sqlite3_free(err_msg);
    sqlite3_close(db);     
    exit(1);
  }
  ///////////////////////////////////////////////////////////////////////////
  sqlite3_finalize(res);
  sqlite3_close(db);
  return storage;
}

void alloc_storage (void   **storage,
                    datatype storage_datatype,
                    int      size,
                    int   (**callback)(void *, int, char **, char **)) {
  switch(storage_datatype) {
    case(TYPE_ICON):
      size *= sizeof(icon);
      *storage = (icon*)malloc(size);
      *callback = &init_icons;
      break;
    default:
      fprintf(stderr, "Fatal: unknown datatype, passed datatype ordinal = %d\n", storage_datatype);
      exit(1);
  }
  if (*storage == NULL) {
    fprintf(stderr, "Fatal: failed to allocate %u bytes.\n", size);
    exit(1);
  }
}

int init_icons(void  *ext,
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
