#ifndef LIST_SCR_C
#define LIST_SCR_C

#include "list_scr.h"

static void print_list() {
  fprintf(stdout, "%ls", L"\r\n");
  fprintf(stdout, "%ls", L"Запиь 1\r\n");
  fprintf(stdout, "%ls", L"Запиь 2\r\n");
  fprintf(stdout, "%ls", L"Запиь 3\r\n");
  fprintf(stdout, "%ls", L"Запиь 4\r\n");
  fprintf(stdout, "%ls", L"Запиь 5\r\n");
  fprintf(stdout, "%ls", L"\r\n");

  fprintf(stdout, "%ls", L"(1) Главное меню, (2) Добавить запись\r\n");
}

void list_scr() {

  char *input_command = (char *)malloc(sizeof(char *) * 1000);

  int is_exit = 0;
  while (!is_exit) {
    print_list();
    printf("Список:>");
    fgets(input_command, sizeof(input_command), stdin); // read string

    switch (atoi(input_command)) {
    case 1:
      is_exit = 1;
      break;
    case 2:
      printf("Добавить запись: ");
      break;

    default:
      break;
    }
  }
  free(input_command);
};

#endif
