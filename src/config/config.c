#include "config.h"
#include "../libs/ini.h"
#include <stdio.h>
#include <stdlib.h> //strlen
#include <string.h>

static t_config *config;
static int is_config_init = 0;

static int handler(void *data, const char *section, const char *name,
                   const char *value) {
  t_config *pconfig = (t_config *)data;

  if (MATCH_CONF_VARS("server", "host")) {
    config->address = strdup(value);
  }
  if (MATCH_CONF_VARS("server", "port")) {
    config->port = atoi(value);
    fprintf(stdout, "port: %d \r\n", config->port);
  }
  if (MATCH_CONF_VARS("store", "db_file")) {
    config->db_file = strdup(value);
  }
  return 1;
}

int init_config() {
  if (is_config_init == 1) {
    return 1;
  }
  config = (t_config *)malloc(sizeof(t_config));
  config->port = SERVER_DEFAULT_PORT_NUM;
  config->address = "0.0.0.0";
  config->db_file = "data.db";

  if (ini_parse("config.ini", handler, &config) < 0) {
    fprintf(stderr, "init_config done \r\n");
    return 0;
  }

  is_config_init = 1;
  return 1;
}

t_config *get_config() {
  if (is_config_init == 0) {
    return NULL;
  }
  return config;
}
