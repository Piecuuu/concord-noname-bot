#ifndef EVENT_H
#define EVENT_H

#include <concord/discord.h>

struct Event {
  char* name;
  void (*reg)(struct discord* client);
};

void event_register_event(const struct Event* event, struct discord* client);
void event_register_from_list(struct discord* client);

#endif // EVENT_H
