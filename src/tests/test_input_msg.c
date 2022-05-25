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

#include "../modules/messages/messages_mod.h"

void do_resize(int dummy) {
  mvaddwstr(0, 0, L"====resize: ======"); // задаем вопрос
  refresh();
}
int main() {

  setlocale(LC_ALL, "en_US.utf8");

  char *msg = messages_input_data();

  if (msg)
    fprintf(stdout, "%s", msg);

  return 0;
}
