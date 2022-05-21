#ifndef DB_C
#define DB_C

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/config.h"

static int is_ok = 1;

static sqlite3 *db = NULL;

int db_is_ok() { return is_ok; }

int db_init(struct stru_config *config) {

  char *err_msg = 0;
  sqlite3_stmt *statement;
  int rc = 0;

  if (config->db_file == NULL) {
    int rc = sqlite3_open(":memory:", &db);

  } else {
    int rc = sqlite3_open(config->db_file, &db);
  }

  if (rc != SQLITE_OK) {
    fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
    sqlite3_close(db);
    db = NULL;
    is_ok = 0;
  }

  is_ok = 1;

  return is_ok;
}

sqlite3 *db_get() { return db; }

#endif
