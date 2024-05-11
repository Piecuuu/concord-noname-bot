#include "event.h"
#include <concord/discord.h>

#include "events/ready.h"
#include "events/interaction_create.h"

static const struct Event event_events[] = {
  { .name = "readyEvent", .reg = &event_ready_register },
  { .name = "interactionCreateEvent", .reg = &event_interaction_create_register },
};

void event_register_event(const struct Event* event, struct discord* client) {
  log_debug("[%s] Registering", event->name);
  event->reg(client);
  log_debug("[%s] Up", event->name);
}

void event_register_from_list(struct discord* client) {
  size_t events_length = sizeof(event_events) / sizeof(event_events[0]);
  for(int i = 0; i < events_length; i++) {
    event_register_event(&event_events[i], client);
  }
}
