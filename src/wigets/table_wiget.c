#ifndef _TABLE_WIGET_C
#define _TABLE_WIGET_C

#include <wchar.h>

void table_print();

struct table_item {
  wchar_t *data;
  int length; 
};

struct table_row {
  int column_count;
  struct table_item * column; 
};

#endif
