#include "interaction_create.h"
#include <concord/log.h>
#include <inttypes.h>
#include <string.h>
#include "../command.h"

static void event_interaction_command_handler(struct discord *client, const struct discord_interaction *event) {
  command_handle(client, event);
}

static void event_interaction_create_execute(struct discord *client, const struct discord_interaction *event) {
  log_trace("Interaction created.");
  switch(event->type) {
    case DISCORD_INTERACTION_APPLICATION_COMMAND: return event_interaction_command_handler(client, event);
  }
}

void event_interaction_create_register(struct discord* client) {
  discord_set_on_interaction_create(client, &event_interaction_create_execute);
}


