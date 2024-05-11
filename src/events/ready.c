#include "ready.h"
#include <concord/log.h>
#include <inttypes.h>
#include <string.h>
#include "../command.h"

static void event_ready_execute(struct discord *client, const struct discord_ready *event) {
  log_debug("Ready!");

  command_register_from_list(client, event->application->id);

  if(strcmp(event->user->discriminator, "0") == 0) {
    // If bots don't have discriminators anymore
    log_info("Logged in as %s (%"PRIu64")", event->user->username, event->user->id);
  } else {
    log_info("Logged in as %s#%s (%"PRIu64")", event->user->username, event->user->discriminator, event->user->id);
  }
}
void event_ready_register(struct discord* client) {
  discord_set_on_ready(client, &event_ready_execute);
}

