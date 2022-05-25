#ifndef LIST_SCR_C
#define LIST_SCR_C

#include "list_scr.h"

static void print_list() {

  Slice *list = message_list(0, 10);

  for (int i = 0; i < Slice_Size(list); i++) {
    struct message_item *item = Slice_Get(list, i);
    fprintf(stdout, "%d msg = %ls \r\n", item->id, item->msg);
  }

  message_free_slice(list);
}

void list_scr() {

  char *input_command = (char *)malloc(sizeof(char *) * 1000);

  int is_exit = 0;
  int limit = 10;
  int offset = 0;
  while (!is_exit) {
    messages_print_list(offset, limit);

    fprintf(stdout, "%d, %d", offset, limit);
    fprintf(stdout, "%ls",
            L"(1) Главное меню, (2) Добавить запись, (3) Далее, (4) Назад\r\n");
    printf("Список:>");
    fgets(input_command, sizeof(input_command), stdin); // read string
    fprintf(stdout, "%lu\n", (unsigned long)time(NULL));

    switch (atoi(input_command)) {
    case 1:
      is_exit = 1;
      break;
    case 2:
      messages_input();
      break;
    case 3:
      offset = offset + limit;
      break;
    case 4:
      offset = offset - limit;
      if (offset < 0)
        offset = 0;
      break;

    default:
      break;
    }
  }
  free(input_command);
};

#endif
