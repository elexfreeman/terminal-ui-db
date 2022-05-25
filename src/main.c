#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED 1
#endif

#include <signal.h>

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "./config/config.h"
#include "./db/db.h"
#include "./db/messages_db.h"

#include "./modules/screens/main_menu_scr.h"

void app_finish() {
  t_config *config = get_config();
  free(config);
  db_close();
  fprintf(stdout, "App exit...\n");
  abort();
}

void sig_handler(int sig) {
  switch (sig) {
  case SIGSEGV:
    app_finish();
  case SIGTERM:
    app_finish();
  default:
    app_finish();
  }
}

int main() {
  setlocale(LC_ALL, "en_US.utf8");

  if (signal(SIGINT, sig_handler) == SIG_ERR)
    printf("\ncan't catch SIGINT\n");

  //================
  //  CONFIG
  //================
  init_config();
  t_config *config = get_config();
  if (config == NULL) {
    fprintf(stdout, "Empty config r\n");
    return 1;
  }

  db_init(config);

  message_init();

  main_menu_scr();

  db_close();

  return 0;
}
