#include "command.h"

#include "commands/ping.h"
#include "string.h"
#include <concord/log.h>

static const struct Command commands[] = {
  { .name = "ping", .reg = &command_ping_register, .exec = &command_ping_execute },
};
#define COMMANDS_LENGTH sizeof(commands) / sizeof(commands[0])

void command_register(const struct Command* command, struct discord* client, u64snowflake application_id) {
  log_debug("[/%s] Registering", command->name);
  command->reg(client, application_id);
  log_debug("[/%s] Up", command->name);
}
void command_register_from_list(struct discord* client, u64snowflake application_id) {
  for(int i = 0; i < COMMANDS_LENGTH; i++) {
    command_register(&commands[i], client, application_id);
  }
}

void command_handle(struct discord *client, const struct discord_interaction *event) {
  for(int i = 0; i < COMMANDS_LENGTH; i++) {
    struct Command command = commands[i];
    if(strncmp(command.name, event->data->name, strlen(event->data->name)) == 0) {
      command.exec(client, event);
      break;
    }
  }
}
