#include "bot.h"
#include <string.h>
#include <concord/discord.h>
#include <concord/discord-internal.h>
#include "config.h"
#include "event.h"

struct Bot* bot_global;

struct discord* bot_init_client() {
  struct discord* client = discord_init(bot_global->config->token);
  event_register_from_list(client);
  discord_run(client);

  free(bot_global->config->token);
  memset(bot_global->config->token, 0, strlen(bot_global->config->token));

  return client;
}

void bot_init_global_struct() {
  struct Bot* bot = malloc(sizeof (struct Bot));

  bot_global = bot;
}
