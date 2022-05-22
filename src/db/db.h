#ifndef DB_H
#define DB_H

#include "sqlite3.h"
#include "../config/config.h"

int db_is_ok();

int db_init(struct stru_config *config);
void db_close();

sqlite3 * db_get();


#endif
