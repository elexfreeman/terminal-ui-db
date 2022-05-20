#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "./wigets/input_wiget.h"

int main() {
  initscr();

  setlocale(LC_ALL, "ru_RU.UTF-8");

  mvaddwstr(5, 5, L"Английское слово: "); // задаем вопрос

  wchar_t *input_data;
  wchar_t word[8];

  wchar_t *pm;

  pm = calloc(123, sizeof *pm);
  wcscpy(pm, L"bye");
  move(0, 0);
  printw("pm %ls", pm);
  mvaddwstr(3, 4, pm); // задаем вопрос

  //  input_data = (wchar_t *)malloc(20);

  // mvinwstr(0, 0, input_data);
  getn_wstr((wint_t *)word, 8);
  mvaddwstr(6, 24, word); // задаем вопрос
  printw("len %d", wcslen(word));
  refresh();

  wchar_t *dd = input_field(L"Введите данные 5 ", 5);
  mvaddwstr(6, 24, dd); // задаем вопрос

  free(pm);
  free(dd);
  getch();
  endwin();
  return 0;
  return 0;
}
