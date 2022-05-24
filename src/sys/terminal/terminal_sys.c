#ifndef TERMINAL_SYS_C
#define TERMINAL_SYS_C

#include "./terminal_sys.h"

// static Slice *terminal_data;

static int is_teminal_init = 0;

void teminal_init() {}

void terminal_show_view(Slice *terminal_data) {
  int size = Slice_Size(terminal_data);
  for (int i = 0; i < size; i++) {
    t_trm_str *line = Slice_Get(terminal_data, i);
    fprintf(stdout, "%ls", line->data);
  }
}

void *terminal_show_menu(Slice *data) { return NULL; }

#endif
