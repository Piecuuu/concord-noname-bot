#ifndef BOT2_H
#define BOT2_H

#include <concord/discord.h>
#include <concord/logconf.h>
#include <stdlib.h>

struct Bot {
  struct discord* client;
  struct Config* config;
};

extern struct Bot* bot_global;

//void _discord_init(struct discord *new_client);
//struct discord* bot_create_client();
struct discord* bot_init_client();
void bot_init_global_struct();

#endif // BOT_H
