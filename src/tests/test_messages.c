
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <signal.h>

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../config/config.h"
#include "../db/db.h"
#include "../db/messages_db.h"

int main() {

  setlocale(LC_ALL, "en_US.utf8");

  //================
  init_config();
  t_config *config = get_config();
  if (config == NULL) {
    fprintf(stdout, "Empty config r\n");
    return 1;
  }
  db_init(config);

  message_init();

  struct message_item *msg = malloc(sizeof(struct message_item));
  msg->create_date = 1231231;

  wchar_t *pm;
  pm = calloc(22, sizeof *pm);
  msg->msg = calloc(22, sizeof *msg->msg);
  wcscpy(msg->msg, L"тестовые данные");

  // fprintf(stdout, "INSERT DATA %ls, %d \r\n", msg->msg,
  // (int)wcslen(msg->msg));

  message_add(msg);

  free(msg->msg);
  free(msg);

  Slice *list = message_list(2, 6);

  for (int i = 0; i < Slice_Size(list); i++) {
    struct message_item *item = Slice_Get(list, i);
    fprintf(stdout, "%d msg = %ls \r\n", item->id, item->msg);
  }

  message_free_slice(list);

  db_close();
  fprintf(stdout, "TEST MSMS");
  return 0;
}
