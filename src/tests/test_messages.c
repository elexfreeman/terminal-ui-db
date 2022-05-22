
#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <signal.h>

#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../config/config.h"
#include "../db/db.h"
#include "../db/messages_db.h"

int main() {

  setlocale(LC_ALL, "en_US.utf8");
  const char *mbstr = u8"z\u00df\u6c34\U0001F34C"; // or u8"zß水🍌"
  wchar_t wstr[5];
  mbstowcs(wstr, mbstr, 5);
  // wprintf(L"MB string: %s\n", mbstr);
  // wprintf(L"Wide string: %ls\n", wstr);

  // 4 wide characters
  const wchar_t src[] = L"Привет мрррр";
  // they occupy 10 bytes in UTF-8
  size_t len_p_dst = wcslen(src) * sizeof(wchar_t);
  char *p_dst = (char *)malloc(len_p_dst);
  //  char dst[wcslen(src) * sizeof(wchar_t)];

  printf("wide-character string: '%ls'\n", src);

  int rtn_val = wcstombs(p_dst, src, len_p_dst);
  if (rtn_val > 0)
    printf("multibyte string:  '%s'\n", p_dst);

  //================
  init_config();
  struct stru_config *config = get_config();
  if (config == NULL) {
    fprintf(stdout, "Empty config r\n");
    return 1;
  }
  db_init(config);

  message_init();

  struct message_item *msg = malloc(sizeof(struct message_item));
  msg->create_date = 1231231;

  wchar_t *pm;
  pm = calloc(22, sizeof *pm);
  msg->msg = calloc(22, sizeof *msg->msg);
  wcscpy(msg->msg, L"тестовые данные");

  // fprintf(stdout, "INSERT DATA %ls, %d \r\n", msg->msg,
  // (int)wcslen(msg->msg));

  message_add(msg);

  free(msg->msg);
  free(msg);

  message_list(0, 0);

  db_close();
  fprintf(stdout, "TEST MSMS");
  return 0;
}
