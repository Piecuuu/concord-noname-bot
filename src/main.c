#include <stdio.h>
#include "bot.h"
#include "config.h"

int main() {
  bot_init_global_struct();
  FILE* config = config_open_file();
  config_serialize(config);

  bot_init_client();
  free(bot_global->config);
  free(bot_global);
}
