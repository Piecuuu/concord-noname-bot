#ifndef COMMAND_H
#define COMMAND_H

#include <concord/discord.h>

struct Command {
  char* name;
  void (*reg)(struct discord* client, u64snowflake application_id);
  void (*exec)(struct discord *client, const struct discord_interaction *event);
};

void command_register(const struct Command* command, struct discord* client, u64snowflake application_id);
void command_register_from_list(struct discord* client, u64snowflake application_id);
void command_handle(struct discord *client, const struct discord_interaction *event);

#endif // COMMAND_H
