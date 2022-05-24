#ifndef TERMINAL_SYS_H
#define TERMINAL_SYS_H

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include "../../libs/datastd/slice.h"
#include <ncurses.h>
#include <wchar.h>

typedef int t_command_fnc();

struct input_cmd {
  wchar_t *label;
  wchar_t command;
  t_command_fnc *cmd;
};

struct trm_str {
  wchar_t *data;
  int len;
};

typedef struct trm_str t_trm_str;
void terminal_show_view(Slice *terminal_data);

void *terminal_show_menu(Slice *data);

void teminal_init();

void teminal_add_screen(Slice *data);

#endif
