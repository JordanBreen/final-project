#include <sqlite3.h>
#include <stdlib.h>
#include <string.h>
#include "buf_def.h"
#include "sqlite_loader.h"
#include "spell.h"

sqlite3 *db = NULL;
sqlite3_stmt *open_res = NULL;
sqlite3_mutex *mutex = NULL;
str db_file_name;

void* load_table (const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int* out_table_size) {
  void *storage;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query = "SELECT * FROM ";
  int rc;

  strcat(sql_query, db_table_name);
  *out_table_size = get_table_size(db_table_name);
  storage = malloc((obj_size)*(*out_table_size));
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {      
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);     
    exit(1);
  }
  
  sqlite3_finalize(res);
  return storage;
}

void* load_by_id (const str db_table_name, int(*callback)(void*, int, str*, str*), size_t obj_size, int id) {
  void *storage;
  sqlite3_stmt *res = NULL;
  str err_msg = NULL;
  buf sql_query;
  int rc, table_size; 

  table_size = get_table_size(db_table_name);
  if (id < 1 || id > table_size) {
    fprintf(stderr, "%s:%s() ERROR, id %d is outside the range of possible id values [1,%d]\n", __FILE__, __func__, id, table_size);
    db_close(err_msg);
    exit(1);
  }
  
  sprintf(sql_query, "SELECT * FROM %s WHERE id = %d", db_table_name, id);
  storage = malloc(obj_size);
  
  rc = sqlite3_exec(db, sql_query, callback, storage, &err_msg);
  if (rc != SQLITE_OK ) {
    fprintf(stderr, "Failed to select data from db_file: %s table: %s\n", db_file_name, db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);
    exit(1);
  }

  sqlite3_finalize(res);
  return storage;
}

int count_rows (void *ext, int argc, str *argv, str *col) {
  int *size = (int*)ext;
  *size = atoi(*argv);
  return 0;
}

void db_close (str err_msg) {
  if(err_msg)
    sqlite3_free(err_msg);
  sqlite3_mutex_free(mutex);
  free(db_file_name);
  sqlite3_close(db);
}

void db_open (const str arg_db_file_name) {
  int ret_val = SQLITE_OK;
  str err_msg = NULL;
  db_file_name = str_clone(arg_db_file_name);
  mutex = sqlite3_mutex_alloc(SQLITE_MUTEX_FAST);
  ret_val = sqlite3_open(db_file_name, &db);
  if(ret_val != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    db_close(err_msg);
    exit(1);
  }
  ret_val = sqlite3_prepare_v2(db, "SELECT SQLITE_VERSION()", -1, &open_res, 0);
  if (ret_val != SQLITE_OK) {
    fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    db_close(err_msg);
    exit(1);
  }
}

int get_table_size (const str db_table_name) {
  str err_msg  = NULL;
  int out_size = 0;
  int ret_val;
  buf sql_stmt_count = "SELECT COUNT (*) FROM ";
  strcat(sql_stmt_count,  db_table_name);
  ret_val = sqlite3_exec(db, sql_stmt_count, count_rows, &out_size, &err_msg);
  if (ret_val != SQLITE_OK ) {
    fprintf(stderr, "Failed to get count from db_table: %s\n", db_table_name);
    fprintf(stderr, "SQL error: %s\n", err_msg);
    db_close(err_msg);
    exit(1);
  }
  return out_size;
}

str str_clone(str arg_str) {
  if(!arg_str)
    return NULL;
  str ret_str = malloc(strlen(arg_str) + 1);
  strcpy(ret_str, arg_str);
  return ret_str;
}
