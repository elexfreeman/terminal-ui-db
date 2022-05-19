
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *input_field(char *label, int length) {
  int x, y;
  char *input_data;

  if (length < 1) {
    return NULL;
  }

  getmaxyx(stdscr, y, x);
  input_data = (char *)malloc(length);

  //  move(y - 1, 0); // move to begining of line
  //  clrtoeol();     // clear line
  //  refresh();
  mvprintw(y - 1, 0, label);
  refresh();
  getnstr(input_data, length);

  return input_data;
}

int main() {

  char name[46];
  char password[9];

  int x, y;

  initscr();

  getmaxyx(stdscr, y, x);

  char *data = input_field("Input 5 numbers: ", 5);

  mvprintw(y - 2, 0, data);
  free(data);
  //  refresh();

  getch(); /* wait here */
  endwin();
  return 0;
}
