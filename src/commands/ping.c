#include "ping.h"

void command_ping_register(struct discord* client, u64snowflake application_id) {
  struct discord_create_global_application_command params = {
    .name = "ping",
    .description = "Ping command!"
  };
  discord_create_global_application_command(client, application_id, &params, NULL);
}
void command_ping_execute(struct discord *client, const struct discord_interaction *event) {
  discord_create_interaction_response(client, event->id,
                                      event->token, &(struct discord_interaction_response){
                                        .type = DISCORD_INTERACTION_DEFERRED_CHANNEL_MESSAGE_WITH_SOURCE,
                                      }, NULL);

  discord_edit_original_interaction_response(client, event->application_id, event->token, &(struct discord_edit_original_interaction_response){
                                              .content = "Pong!",
                                            }, NULL);
}
