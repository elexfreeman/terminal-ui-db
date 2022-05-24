#ifndef TERMINAL_SYS_H
#define TERMINAL_SYS_H

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include "../../libs/datastd/slice.h"
#include <ncurses.h>
#include <stdlib.h>
#include <wchar.h>

#define main_menu_fnc 1
#define list_fnc 2
#define add_fnc 3

typedef Slice *t_command_fnc();

struct input_cmd {
  wchar_t *label;
  wchar_t *command;
  int cmd;
};

typedef struct input_cmd t_menu;

struct trm_str {
  wchar_t *data;
  int len;
};

typedef struct trm_str t_trm_str;

void terminal_free_data(Slice *terminal_data);

void terminal_show_view(Slice *terminal_data);

void *terminal_show_menu(Slice *data);

void terminal_free_menu(Slice *data);

void teminal_init();

void teminal_add_screen(Slice *data);

t_trm_str *terminal_create_str(wchar_t *data);
#endif
