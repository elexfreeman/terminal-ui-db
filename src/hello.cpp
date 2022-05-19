#include <iostream>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> /* for pid_t */
#include <unistd.h>    /* for fork */

#include "lib1.h"

int main() {
  int a = my_fn(2);

  int x, y;

  initscr();

  getmaxyx(stdscr, y, x);
  printw("Window size is % d rows, % d columns.\n", y, x);
  printw("%d \n", a);
  refresh();
  getch();

  endwin();

  char prg[5] = "nvim";
  char arg_file[9] = "test.txt";

  static char *argv[] = {prg, arg_file, NULL};
  execv("/bin/nvim", argv);
  return 0;
}
