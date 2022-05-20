#ifndef _INPUT_WIGET_C
#define _INPUT_WIGET_C

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <ncursesw/ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

wchar_t *input_field(wchar_t *label, int length) {
  int x, y;
  wchar_t *input_data;

  if (length < 1) {
    return NULL;
  }

  input_data = calloc(length, sizeof *input_data);
  getmaxyx(stdscr, y, x);

  mvaddwstr(y - 1, 0, label);
  getn_wstr((wint_t *)input_data, length);

  return input_data;
}
#endif
