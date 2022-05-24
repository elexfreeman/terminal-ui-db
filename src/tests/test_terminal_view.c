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
#include "../libs/datastd/slice.h"

#include "../sys/terminal/terminal_sys.h"

Slice *main_menu();
Slice *list_screen();

Slice *list_screen() {

  Slice *cmd_list = Slice_Create();
  Slice *screen_list = Slice_Create();

  t_menu *menu_main = malloc(sizeof(t_menu *));
  t_menu *menu_list = malloc(sizeof(t_menu *));

  menu_main->label = L"(1) Главное меню";
  menu_main->command = malloc(sizeof(wchar_t *) * 3);
  wcscpy(menu_main->command, L"1\r\n");
  menu_main->cmd = main_menu_fnc;
  Slice_Append(cmd_list, menu_main);

  menu_list->label = L"(2) Добавить запись";
  menu_list->command = malloc(sizeof(wchar_t *) * 3);
  wcscpy(menu_list->command, L"2\r\n");
  Slice_Append(cmd_list, menu_list);

  Slice_Append(screen_list, terminal_create_str(L"\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"Запиь 1\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"Запиь 2\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"Запиь 3\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"Запиь 4\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"Запиь 5\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"\r\n"));

  terminal_show_view(screen_list);
  terminal_free_data(screen_list);

  terminal_show_menu(cmd_list);

  return cmd_list;
}

Slice *main_menu() {

  Slice *cmd_list = Slice_Create();
  Slice *screen_list = Slice_Create();

  t_menu *menu_add = malloc(sizeof(t_menu *));
  t_menu *menu_list = malloc(sizeof(t_menu *));

  menu_add->label = L"(1) Добавить запись";
  menu_add->command = (wchar_t *)malloc(sizeof(wchar_t *) * 3);
  menu_add->cmd = add_fnc;
  wcscpy(menu_add->command, L"1\r\n");
  Slice_Append(cmd_list, menu_add);

  menu_list->label = L"(2) Список записей";
  menu_list->command = (wchar_t *)malloc(sizeof(wchar_t *) * 3);
  menu_list->cmd = list_fnc;
  wcscpy(menu_list->command, L"2\r\n");
  Slice_Append(cmd_list, menu_list);

  Slice_Append(screen_list, terminal_create_str(L"\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"======================\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"==== ГЛАВНОЕ МЕНЮ ====\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"======================\r\n"));
  Slice_Append(screen_list, terminal_create_str(L"\r\n"));

  terminal_show_view(screen_list);
  terminal_free_data(screen_list);

  return cmd_list;
};

void do_resize(int dummy) {
  mvaddwstr(0, 0, L"====resize: ======"); // задаем вопрос
  refresh();
}
int main() {

  //================
  //  CONFIG
  //================
  init_config();
  t_config *config = get_config();
  if (config == NULL) {
    fprintf(stdout, "Empty config r\n");
    return 1;
  }

  setlocale(LC_ALL, "en_US.utf8");
  char line11[50] = "Heeloo Привет всем ";
  size_t len_p_dst = strlen(line11) * sizeof(wchar_t);
  wchar_t *wstr = malloc(len_p_dst);
  mbstowcs(wstr, line11, len_p_dst);

  fprintf(stdout, ">> %d %ls", (int)len_p_dst, wstr);

  free(wstr);

  //  return 0;

  signal(SIGWINCH, do_resize);
  setlocale(LC_ALL, "en_US.utf8");
  // setlocale(LC_ALL, "ru_RU.UTF-8");

  Slice *view = Slice_Create();

  FILE *fp;
  char *line = NULL;
  size_t len = 0;
  ssize_t read;

  fp = fopen("./config.ini", "r");
  if (fp == NULL)
    exit(EXIT_FAILURE);

  int i = 1;

  int x = getmaxy(stdscr);
  printf("max x = %d", x);

  while ((read = getline(&line, &len, fp)) != -1) {
    size_t len_p_dst = len * sizeof(wchar_t);
    wchar_t *data = malloc(len_p_dst);
    mbstowcs(data, line, len_p_dst);
    Slice_Append(view, data);
    i++;
  }

  fclose(fp);
  if (line)
    free(line);

  char *input_command = (char *)malloc(sizeof(char *) * 1000);

  Slice *menu = main_menu();
  while (true) {
    terminal_show_menu(menu);
    printf("Введите команду: ");
    fgets(input_command, sizeof(input_command), stdin); // read string

    switch (atoi(input_command)) {
    case list_fnc:
      list_screen();
      break;
    case add_fnc:
      printf("Добавить: ");
      break;

    default:
      main_menu();
    }
  }

  free(input_command);
  //  initscr();
  //
  //  setlocale(LC_ALL, "en_US.utf8");
  //  wchar_t *input_data;
  //  input_data = calloc(5, sizeof *input_data);
  //
  //  getn_wstr((wint_t *)input_data, 5);
  //  getch();
  //  endwin();
  return 0;
}
