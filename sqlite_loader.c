#include <sqlite3.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite_loader.h"
#include "icon.h"

void *load_table (const char *db_file_name,
	          const char *db_table_name,
	          datatype    storage_datatype,
		  int        *out_size) {
  void         *storage;
  sqlite3      *db         = NULL;
  sqlite3_stmt *res        = NULL;
  char         *err_msg    = NULL,
                sql_query [BUFSIZ] = "SELECT * FROM ",
                sql_size  [BUFSIZ] = "SELECT COUNT (*) FROM ";
  
  int rc, (*callback)(void *, int, char **, char **) = NULL;
  *out_size = 0;
  db_init(&db, db_file_name, res, err_msg);
  ///////////////////////////////////////////////////////////////////////////
  strcat(sql_size,  db_table_name);
  strcat(sql_query, db_table_name);
  
  rc = sqlite3_exec(db, sql_size, get_table_size, out_size, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to get count from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);
    exit(1);
  }
  alloc_storage(&storage, storage_datatype, *out_size, &callback);
  ///////////////////////////////////////////////////////////////////////////
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);     
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
      *callback = &init_icon;
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

int get_table_size (void  *ext,
                    int    argc,
                    char **argv,
                    char **col) {
  int *size = (int *)ext;
  *size = atoi(*argv);
  printf("sql_loader::get_size(): size = %d\n", *size);
  return 0;
}

void close_loader (char *err_msg,
		   sqlite3 *db) {
  sqlite3_free(err_msg);
  sqlite3_close(db);
}

void db_init (sqlite3      **db_ptr,
              const char    *db_file_name,
	      sqlite3_stmt  *res,
              char          *err_msg) {
  int rc;
  rc = sqlite3_open(db_file_name, db_ptr);
  if(rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db_ptr));
    close_loader(err_msg, *db_ptr);
    exit(1);
  }
  rc = sqlite3_prepare_v2(*db_ptr, "SELECT SQLITE_VERSION()", -1, &res, 0);
  if (rc != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(*db_ptr));
    close_loader(err_msg, *db_ptr);
    exit(1);
  }
}
