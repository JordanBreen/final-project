#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "buf_def.h" // includes <stdio.h>
#include "sqlite_loader.h"
#include "spell.h"

void* load_table (const str db_file_name, const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int* out_table_size) {
  void *storage;
  sqlite3 *db = NULL;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query = "SELECT * FROM ";
  int rc;

  db_init(&db, db_file_name, res);
  strcat(sql_query, db_table_name);
  *out_table_size = get_table_size(db, db_file_name, db_table_name);
  storage = malloc((obj_size)*(*out_table_size));
  
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);     
    exit(1);
  }
  
  sqlite3_finalize(res);
  sqlite3_close(db);
  return storage;
}

void* load_by_id (const str db_file_name, const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int id) {
  void *storage;
  sqlite3 *db = NULL;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query;
  int rc;

  db_init(&db, db_file_name, res);
  sprintf(sql_query, "SELECT * FROM %s WHERE id = %d", db_table_name, id);
  storage = malloc(obj_size);

  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);
    exit(1);
  }

  sqlite3_finalize(res);
  sqlite3_close(db);
  return storage;
}


int count_rows (void *ext, int argc, str *argv, str *col) {
  int *size = (int*)ext;
  *size = atoi(*argv);
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
  str err_msg  = NULL;
  int out_size = 0;
  int ret_val;
  buf sql_stmt_count = "SELECT COUNT (*) FROM ";
  strcat(sql_stmt_count,  db_table_name);
  ret_val = sqlite3_exec(db, sql_stmt_count, count_rows, &out_size, &err_msg);
  if (ret_val != SQLITE_OK ) {
    fprintf(stderr, "Failed to get count from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    close_loader(err_msg, db);
    exit(1);
  }
  return out_size;
}
