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

#include "../modules/screens/main_menu_scr.h"

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

  main_menu_scr();

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
