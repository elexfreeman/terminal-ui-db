#ifndef DB_H
#define DB_H

#include "../config/config.h"
#include "sqlite3.h"

int db_is_ok();

int db_init(t_config *config);
void db_close();

sqlite3 *db_get();

#endif
