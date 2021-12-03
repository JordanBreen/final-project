#include <sqlite3.h>
// #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buf_def.h" // includes <stdio.h>
#include "sqlite_loader.h"
#include "spell.h"

enum object {
  SPELL
};

void *load_table (const str db_file_name, const str db_table_name, int(*callback)(void*, int, str*, str*)/*object object_type, int* out_size*/) {
  //void *storage;
  sqlite3 *db = NULL;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query = "SELECT * FROM ";
  int rc;
  //int (*callback)(void *, int, char **, char **) = NULL;

  db_init(&db, db_file_name, res);
  strcat(sql_query, db_table_name);
  //*out_size = get_table_size(db, db_file_name, db_table_name);
  //alloc_storage(&storage, object_type, *out_size, &callback);
  ///////////////////////////////////////////////////////////////////////////
  rc = sqlite3_exec(db, sql_query, callback, /*storage*/ NULL, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);     
    exit(1);
  }
  ///////////////////////////////////////////////////////////////////////////
  sqlite3_finalize(res);
  sqlite3_close(db);
  return /*storage*/ NULL;
}

void alloc_storage (void **storage, object object_type, int size, int(**callback)(void*, int, str*, str*)) {
  switch(object_type) {
    case(SPELL):
      size     *= sizeof(spell);
      *storage  = (spell*)malloc(size);
      *callback = &parse_spell;
      break;
    default:
      fprintf(stderr, "Fatal: unknown object type, passed object of ordinal %02d\n", object_type);
      exit(1);
  }
  if (*storage == NULL) {
    fprintf(stderr, "Fatal: failed to allocate %u bytes.\n", size);
    exit(1);
  }
}

int count_rows (void *ext, int argc, str *argv, str *col) {
  int *size = (int*)ext;
  *size = atoi(*argv);
  printf("sql_loader::get_size(): size = %d\n", *size);
  return 0;
}

void close_loader (str err_msg, sqlite3 *db) {
  sqlite3_free(err_msg);
  sqlite3_close(db);
}

void db_init (sqlite3 **db_ptr, const str db_file_name, sqlite3_stmt *res) {
  int ret_val = SQLITE_OK;
  str err_msg = NULL;
  ret_val = sqlite3_open(db_file_name, db_ptr);
  if(ret_val != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(*db_ptr));
    close_loader(err_msg, *db_ptr);
    exit(1);
  }
  ret_val = sqlite3_prepare_v2(*db_ptr, "SELECT SQLITE_VERSION()", -1, &res, 0);
  if (ret_val != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(*db_ptr));
    close_loader(err_msg, *db_ptr);
    exit(1);
  }
}

int peek_table_size (const str db_file_name, const str db_table_name) {
  sqlite3      *db         = NULL;
  sqlite3_stmt *res        = NULL;
  int           out_size   = 0;
  db_init(&db, db_file_name, res);
  out_size = get_table_size(db, db_file_name, db_table_name);
  sqlite3_finalize(res);
  sqlite3_close(db);
  return out_size;
}

int get_table_size (sqlite3 *db, const str db_file_name, const str db_table_name) {
  //printf("sqlite_loader:get_table_size: entry\n");
  str err_msg  = NULL;
  int out_size = 0;
  int ret_val;
  buf sql_stmt_count = "SELECT COUNT (*) FROM ";
  strcat(sql_stmt_count,  db_table_name);
  //printf("sqlite_loader:get_table_size: sql_stmt_count = %s\n", sql_stmt_count);
  ret_val = sqlite3_exec(db, sql_stmt_count, count_rows, &out_size, &err_msg);
  if (ret_val != SQLITE_OK ) {
    fprintf(stderr, "Failed to get count from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);
    exit(1);
  }
  //printf("sqlite_loader:get_table_size: success! out_size = %d\n", out_size);
  return out_size;
}
