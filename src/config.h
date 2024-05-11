#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <concord/log.h>

#define CONFIG_FILE "config.toml"

struct Config {
  char* token;
  char* db_conn_str;
};

FILE* config_open_file();
FILE* config_try_create_new_config();
void config_get_from_file();
char* config_read_from_file(FILE* file);
void config_serialize(FILE* file);

#endif // CONFIG_H
