#ifndef MAIN_MENU_SCR_C
#define MAIN_MENU_SCR_C

#include "main_menu_scr.h"

static void print_main_menu() {
  fprintf(stdout, "%ls", L"\r\n");
  fprintf(stdout, "%ls", L"(1) Добавить запись, (2) Список записей\r\n");
  fprintf(stdout, "%ls", L"----------------------\r\n");
}

void main_menu_scr() {

  char *input_command = (char *)malloc(sizeof(char *) * 1000);

  int is_exit = 0;
  while (!is_exit) {
    print_main_menu();
    printf("Главное меню:>");
    fgets(input_command, sizeof(input_command), stdin); // read string

    switch (atoi(input_command)) {
    case 1:
      messages_input();
      break;
    case 2:
      list_scr();
      break;

    default:
      break;
    }
    fprintf(stdout, "%ls", L"\r\n_______________________________\r\n");
  }
  free(input_command);
};

#endif
