#ifndef _DB_H
#define _DB_H

#include <stdlib.h>
#include <wchar.h>

#include "../libs/datastd/slice.h"

struct message {
  int id;
  wchar_t *msg;
  time_t create_date;
};

struct message *message_get(int id);
void message_add(struct message *msg);
Slice *message_list(int offset, int limit);

#endif
