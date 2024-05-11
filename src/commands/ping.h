#ifndef PING_H
#define PING_H

#include <concord/discord.h>

void command_ping_register(struct discord* client, u64snowflake application_id);
void command_ping_execute(struct discord *client, const struct discord_interaction *event);

#endif // PING_H
