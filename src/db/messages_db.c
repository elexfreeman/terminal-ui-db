
#ifndef DB_C
#define DB_C

#include "sqlite3.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../config/config.h"
#include "../libs/datastd/slice.h"

struct message *message_get(int id) {
  struct message *out = NULL;

  return out;
}

void message_add(struct message *msg) {}

Slice *message_list(int offset, int limit) {
  Slice *out = Slice_Create();

  return out;
}

#endif
