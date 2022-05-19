
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

int main() {
  int x, y;

  initscr();

  getmaxyx(stdscr, y, x);
  printw("Window size is % d rows, % d columns.\n", y, x);
  refresh();
  getch();

  endwin();
  return 0;
}
