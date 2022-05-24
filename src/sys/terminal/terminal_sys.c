#ifndef TERMINAL_SYS_C
#define TERMINAL_SYS_C

#include "./terminal_sys.h"

// static Slice *terminal_data;

static int is_teminal_init = 0;

void teminal_init() {}

void terminal_show_view(Slice *terminal_data) {
  int size = Slice_Size(terminal_data);
  for (int i = 0; i < size; i++) {
    t_trm_str *line = (t_trm_str *)Slice_Get(terminal_data, i);
    fprintf(stdout, "%ls", line->data);
  }
}

t_trm_str *terminal_create_str(wchar_t *data) {
  t_trm_str *out = (t_trm_str *)malloc(sizeof(t_trm_str *));
  out->len = sizeof(wchar_t *) * wcslen(data);
  out->data = malloc(out->len);
  wcscpy(out->data, data);
  return out;
}

void *terminal_show_menu(Slice *data) {
  int size = Slice_Size(data);
  for (int i = 0; i < size; i++) {
    t_menu *line = (t_menu *)Slice_Get(data, i);
    fprintf(stdout, "%ls   ", line->label);
  }
  fprintf(stdout, "\r\n ");
  return NULL;
}

void terminal_free_menu(Slice *menu_data) {
  int size = Slice_Size(menu_data);
  for (int i = 0; i < size; i++) {
    fprintf(stderr, "free menu ");
    t_menu *line = (t_menu *)Slice_Get(menu_data, i);
    free(line->label);
    free(line->command);
  }
  Slice_Free(menu_data);
}

void terminal_free_data(Slice *terminal_data) {
  int size = Slice_Size(terminal_data);
  for (int i = 0; i < size; i++) {
    t_trm_str *line = (t_trm_str *)Slice_Get(terminal_data, i);
    free(line->data);
    free(line);
  }
  Slice_Free(terminal_data);
}

#endif
