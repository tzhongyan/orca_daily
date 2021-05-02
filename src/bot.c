#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #include <signal.h>

#include "orca/discord.h"
#include "orca-pep.h"

#define UNUSED(x) (void)(x)

static Discord *client = NULL;

static void
on_message_create(Discord *client, const DiscordUser *bot, const DiscordMessage *msg)
{
    UNUSED(bot);

    // make sure bot doesn't echoes other bots
    if (msg->author->bot) {
        return;
    }

    struct discord_create_message_params params = {
        .content = msg->content
    };

    DiscordMessageReference msg_ref;
    discord_message_reference_init(&msg_ref);
    if(msg->referenced_message) {
        msg_ref.message_id = msg->referenced_message->id;
        msg_ref.channel_id = msg->channel_id;
        msg_ref.guild_id = msg->guild_id;

        params.message_reference = &msg_ref;
    }

    discord_create_message(client, msg->channel_id, &params, NULL);
}

// static void
// startup_message(Discord *client, const DiscordUser* bot)
// {
//     UNUSED(bot);
//     struct discord_create_message_params params = {
//         .content = "Hello!"
//     };
//     discord_create_message(client, msg->channel_id, &params, NULL);
// }


// static void
// signal_handler(int signum)
// {
//     switch (signum) {
//         case SIGINT:
//         case SIGTERM:
//             discord_gateway_shutdown(client);
//             // exit(0);
//             break;
//         case SIGHUP:
//             /* TODO: reset logfile */
//             break;
//         case SIGQUIT:
//             exit(127);
//            break;
//         default:
//             /* Ignore */
//             break;
//     }
// }

// static void
// setup_signal_handlers(void)
// {
//     struct sigaction act;

//     act.sa_handler = signal_handler;
//     sigemptyset(&act.sa_mask);
//     act.sa_flags = 0;
//     sigaction(SIGINT, &act, NULL);
//     sigaction(SIGTERM, &act, NULL);
//     sigaction(SIGQUIT, &act, NULL);
//     sigaction(SIGHUP, &act, NULL);
//     sigaction(SIGPIPE, &act, NULL);
// }

int
main(int argc, char** argv)
{
    const char *config_file = NULL;

    if (argc > 1) {
        config_file = argv[1];
    }
    else {
        config_file = "bot.config";
    }

    /* Setup sigact */
    // setup_signal_handlers();

    discord_global_init();

    client = discord_config_init(config_file);
    assert(NULL != client);

    discord_set_on_message_create(client, &on_message_create);
    // discord_set_on_ready(client, &startup_message);

    discord_run(client);

    discord_cleanup(client);

    discord_global_cleanup();
    return 0;
}
