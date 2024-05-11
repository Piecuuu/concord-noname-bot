#include "config.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <toml.h>
#include <string.h>
#include "bot.h"
#include <errno.h>

#define DEFAULT_CONFIG "[bot]\n" \
                       "token = \"YOUR-TOKEN-HERE\"\n"

FILE* config_try_create_new_config() {
  FILE* new_config = fopen(CONFIG_FILE, "w");
  if(new_config == NULL) {
    log_fatal("Unable to create default config.\n");
    exit(1);
  }

  fputs(DEFAULT_CONFIG, new_config);
  return new_config;
}

FILE* config_open_file() {
  FILE* file = fopen(CONFIG_FILE, "r");
  if(file == NULL) {
    if(!errno == ENOENT) {
      log_fatal("I can't seem to be able to open `%s`! Please check the file permissions and try again.\n", CONFIG_FILE);
      exit(1);
    } else { // The config isn't here. Create it.
      FILE* new_config = config_try_create_new_config();
      fclose(new_config);

      file = fopen(CONFIG_FILE, "r");
    }
  }
  return file;
}

void config_serialize(FILE* file) {
  struct Config* config = malloc(sizeof (struct Config));

  char errbuf[200];
  toml_table_t* conf = toml_parse_file(file, errbuf, sizeof(errbuf));
  fclose(file);

  if(!conf) {
    log_fatal("Cannot parse the config - %s\n", errbuf);
    exit(1);
  }

  toml_table_t* bot = toml_table_in(conf, "bot");
  if(!bot) {
    log_fatal("Cannot parse [bot]\n");
    exit(1);
  }

  toml_datum_t token = toml_string_in(bot, "token");
  if(!token.ok) {
    log_fatal("Cannot get `token` from config\n");
    exit(1);
  }

  config->token = token.u.s;

  bot_global->config = config;
}
