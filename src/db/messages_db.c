
#ifndef DB_C
#define DB_C

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/config.h"
#include "../libs/datastd/slice.h"
#include "./db.h"

struct message *message_get(int id) {
  struct message *out = NULL;

  return out;
}

void message_add(struct message *msg) {}

Slice *message_list(int offset, int limit) {
  Slice *out = Slice_Create();

  return out;
}

int message_init() {

  char *err_msg = NULL;
  int rc = 0;

  if (!db_is_ok())
    return 0;

  if (db_is_ok()) {

    char *sql = "CREATE TABLE messages ( "
                "id	INTEGER UNIQUE, "
                "msg	TEXT, "
                "create_date	INTEGER, "
                "PRIMARY KEY(id AUTOINCREMENT) "
                " )";

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

#endif
