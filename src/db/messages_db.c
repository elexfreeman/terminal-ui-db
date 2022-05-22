
#ifndef DB_C
#define DB_C

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/config.h"
#include "../libs/datastd/slice.h"
#include "./db.h"
#include "./messages_db.h"

struct message_item *message_get(int id) {
  struct message_item *out = NULL;

  return out;
}

int message_add(struct message_item *msg) {
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

  size_t len_p_dst = wcslen(msg->msg) * sizeof(wchar_t);
  char *p_dst = (char *)malloc(len_p_dst);
  wcstombs(p_dst, msg->msg, len_p_dst);

  sqlite3_bind_text(p_stmt, 1, p_dst, len_p_dst, SQLITE_TRANSIENT);

  free(p_dst);

  sqlite3_bind_int(p_stmt, 2, msg->create_date);

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

  void *val = NULL;
  sqlite3_stmt *stmt;

  char *err_msg = 0;
  int row = 0;
  const unsigned char *text;

  char *sql = "SELECT id, msg, create_date FROM messages";

  sqlite3_prepare_v2(db_get(), sql, -1, &stmt, NULL);

  fprintf(stdout, "Got results:\n");
  while (sqlite3_step(stmt) != SQLITE_DONE) {
    int i;
    int num_cols = sqlite3_column_count(stmt);

    const unsigned char *blob;

    for (i = 0; i < num_cols; i++) {
      switch (sqlite3_column_type(stmt, i)) {

      case (SQLITE3_TEXT):
        blob = sqlite3_column_text(stmt, i);

        fprintf(stdout, "== %s ==\r\n", (char *)blob);

        size_t blob_bytes = sqlite3_column_bytes(stmt, i);

        wchar_t *wstr = (wchar_t *)malloc(blob_bytes);
        mbstowcs(wstr, (char *)blob, blob_bytes);

        fprintf(stdout, "len %d \r\n ", (int)blob_bytes);
        fprintf(stdout, "data %ls \r\n ", wstr);
        free(wstr);
        // memcpy(input_data, blob, blob_bytes);
        break;

      case (SQLITE_INTEGER):
        printf("%d, ", sqlite3_column_int(stmt, i));
        break;
      case (SQLITE_FLOAT):
        printf("%g, ", sqlite3_column_double(stmt, i));
        break;
      default:
        break;
      }
    }
    printf("\n");
  }

  sqlite3_finalize(stmt);
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

void db_close() { sqlite3_close(db_get()); }
#endif
