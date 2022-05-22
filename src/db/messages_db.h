#ifndef _DB_H
#define _DB_H

#include <stdlib.h>
#include <wchar.h>

#include "../libs/datastd/slice.h"

struct message_item {
  int id;
  wchar_t *msg;
  time_t create_date;
};

struct message_item *message_get(int id);
int message_add(struct message_item *msg);
Slice *message_list(int offset, int limit);

int message_init();

#endif
