#include <stdio.h>
#include "bot.h"
#include "config.h"
#include "db.h"

int main() {
  bot_init_global_struct();
  FILE* config = config_open_file();
  config_serialize(config);

  db_connect();

  bot_init_client();
  PQfinish(bot_global->db_conn);
  free(bot_global->config);
  free(bot_global);
}
