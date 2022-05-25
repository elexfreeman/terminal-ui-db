
#ifndef DB_C
#define DB_C

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../config/config.h"
#include "../libs/datastd/slice.h"
#include "./db.h"
#include "./messages_db.h"

t_message_item *message_get(int id) {
  t_message_item *out = NULL;

  return out;
}

int message_add(char *msg) {
  int rc = 0;
  int ret = 0;

  sqlite3_stmt *p_stmt;
  const char *p_oz;

  if (!db_is_ok()) {
    fprintf(stderr, "ERROR: store is not init\n");
    return 0;
  }
  const char *istmt = "INSERT INTO messages (msg, create_date) VALUES(?,?);";

  ret = sqlite3_prepare_v2(db_get(), istmt, strlen(istmt), &p_stmt, &p_oz);

  if (ret != SQLITE_OK) {
    fprintf(stderr, "ERROR SQL set: %s\n", sqlite3_errmsg(db_get()));
    return 0;
  }

  size_t len_p_dst = strlen(msg) * sizeof(char *);

  fprintf(stdout, "%d \r\n", (int)len_p_dst);

  sqlite3_bind_text(p_stmt, 1, msg, len_p_dst, SQLITE_TRANSIENT);

  time_t t = time(NULL);
  sqlite3_bind_int(p_stmt, 2, t);

  ret = sqlite3_step(p_stmt);
  sqlite3_finalize(p_stmt);

  if (ret != SQLITE_DONE) {
    fprintf(stderr, "ERROR SQL set: %s\n", sqlite3_errmsg(db_get()));
    return 0;
  }

  return 1;
}

Slice *message_list(int offset, int limit) {
  Slice *out = Slice_Create();
  int rc;

  if (!db_is_ok()) {
    return 0;
  }

  const unsigned char *blob = NULL;
  void *val = NULL;
  sqlite3_stmt *p_stmt;

  char *err_msg = 0;
  int row = 0;
  const unsigned char *text;

  char *sql = "SELECT * FROM ("
              "SELECT id, msg, create_date FROM messages ORDER BY id DESC "
              "LIMIT ?, ?) a ORDER BY id ASC;";

  sqlite3_prepare_v2(db_get(), sql, -1, &p_stmt, NULL);

  sqlite3_bind_int(p_stmt, 1, offset);
  sqlite3_bind_int(p_stmt, 2, limit);

  while (sqlite3_step(p_stmt) != SQLITE_DONE) {
    int num_cols = sqlite3_column_count(p_stmt);

    t_message_item *item = malloc(sizeof(t_message_item *));

    // id
    item->id = sqlite3_column_int(p_stmt, 0);

    // msg
    blob = sqlite3_column_text(p_stmt, 1);
    size_t blob_bytes = sqlite3_column_bytes(p_stmt, 1);
    item->msg = (wchar_t *)malloc(blob_bytes);
    mbstowcs(item->msg, (char *)blob, blob_bytes);

    // id
    item->create_date = sqlite3_column_int(p_stmt, 2);

    Slice_Append(out, item);

    //    for (i = 0; i < num_cols; i++) {
    //      switch (sqlite3_column_type(stmt, i)) {
    //
    //      case (SQLITE3_TEXT):
    //        blob = sqlite3_column_text(stmt, i);
    //
    //        fprintf(stdout, "== %s ==\r\n", (char *)blob);
    //
    //        size_t blob_bytes = sqlite3_column_bytes(stmt, i);
    //
    //        wchar_t *wstr = (wchar_t *)malloc(blob_bytes);
    //        mbstowcs(wstr, (char *)blob, blob_bytes);
    //
    //        fprintf(stdout, "len %d \r\n ", (int)blob_bytes);
    //        fprintf(stdout, "data %ls \r\n ", wstr);
    //        free(wstr);
    //        // memcpy(input_data, blob, blob_bytes);
    //        break;
    //
    //      case (SQLITE_INTEGER):
    //        printf("%d, ", sqlite3_column_int(stmt, i));
    //        break;
    //      case (SQLITE_FLOAT):
    //        printf("%g, ", sqlite3_column_double(stmt, i));
    //        break;
    //      default:
    //        break;
    //      }
    //    }
  }

  sqlite3_finalize(p_stmt);
  return out;
}

int message_init() {

  char *err_msg = NULL;
  int rc = 0;

  if (!db_is_ok())
    return 0;

  if (db_is_ok()) {

    char *sql = "CREATE TABLE IF NOT EXISTS messages ( "
                "id	INTEGER UNIQUE, "
                "msg	TEXT, "
                "create_date	INTEGER, "
                "PRIMARY KEY(id AUTOINCREMENT) "
                " ); ";

    rc = sqlite3_exec(db_get(), sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
      fprintf(stderr, "ERROR SQL: %s\n", sqlite3_errmsg(db_get()));
      sqlite3_free(err_msg);
      sqlite3_close(db_get());
      return 0;
    }
  }

  return 1;
}

void message_free(t_message_item *item) {
  if (item) {
    if (item->msg)
      free(item->msg);
    free(item);
  }
}

void message_free_slice(Slice *slice) {
  if (!slice)
    return;
  // TODO: check mem leak

  //  Slice_FreeAllElements(slice);
  t_message_item *item;
  for (int i = 0; i < Slice_Size(slice); i++) {
    item = Slice_Get(slice, i);
    message_free(item);
  }
  Slice_Free(slice);
}

#endif
