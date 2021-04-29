#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "orca/discord.h"

#define UNUSED(x) (void)(x)

void on_message_create(
    struct discord *client,
    const struct discord_user *bot,
    const struct discord_message *msg)
{
    // make sure bot doesn't echoes other bots
    if (msg->author->bot)
    return;

    struct discord_create_message_params params = {
        .content = msg->content
    };

    struct discord_message_reference msg_ref;
    discord_message_reference_init(&msg_ref);
    if(msg->referenced_message) {
        msg_ref.message_id = msg->referenced_message->id;
        msg_ref.channel_id = msg->channel_id;
        msg_ref.guild_id = msg->guild_id;

        params.message_reference = &msg_ref;
    }

    discord_create_message(client, msg->channel_id, &params, NULL);
}

int main(int argc, char** argv)
{
    const char *config_file = NULL;
    struct discord *client = NULL;

    if (argc > 1) {
        config_file = argv[1];
    }
    else {
        config_file = "bot.config";
    }

    discord_global_init();

    client = discord_config_init(config_file);
    assert(NULL != client);

    discord_set_on_message_create(client, &on_message_create);
    discord_run(client);

    discord_cleanup(client);

    discord_global_cleanup();
    return 0;
}
