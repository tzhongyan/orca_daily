#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
// #include <signal.h>

#include "orca/discord.h"
#include "orca-pep.h"
#include "utils.h"

#define UNUSED(x) (void)(x)
#define COMMAND_PREFIX "!!"

static Discord *client = NULL;

/**
 * Echo for what you are saying, probably for testing if the bot is still
 * alive.
 */
static void
on_command_echo(Discord *client, const DiscordUser *bot, 
                const DiscordMessage *msg)
{
    DiscordMessageReference msg_ref;
    UNUSED(bot);

    /* make sure bot doesn't echoes other bots */
    if (msg->author->bot) {
        return;
    }

    DiscordCreateMessageParams params = {
        .content = msg->content
    };

    discord_message_reference_init(&msg_ref);

    if(msg->referenced_message) {
        msg_ref.message_id = msg->referenced_message->id;
        msg_ref.channel_id = msg->channel_id;
        msg_ref.guild_id = msg->guild_id;

        params.message_reference = &msg_ref;
    }

    discord_create_message(client, msg->channel_id, &params, NULL);
}


/**
 * Show the list of help messages
 */
static void
on_command_help(Discord *client, const DiscordUser *bot, const
                DiscordMessage *msg)
{
    DiscordMessageReference msg_ref;
    char *reply_message = NULL;
    UNUSED(bot);

    /* make sure bot doesn't echoes other bots */
    if (msg->author->bot) {
        return;
    }

    if (strlen(msg->content) == 0) {
        const char *command_header = "Commands available:\n```";
        const char *command_footer = 
            "```\n Enter `"COMMAND_PREFIX"help [command]`for its description.";

        char *p_msg = NULL;

        str_append(&p_msg, command_header);

        /* list out the available commands when they don't specify anything */
        #define COMMAND(CMD, DESC) \
            str_append(&p_msg, COMMAND_PREFIX""#CMD", ");
        #include "command.inc"

        /* Truncate the last comma space and copy to q */
        str_truncate(p_msg, strlen(p_msg) - 2);

        /* Markdown closing and further help */
        str_append(&p_msg, command_footer);
        str_append(&reply_message, p_msg);
        free(p_msg);
    }
    /* if there is msg->content for `help`, search for its description */
#define COMMAND(CMD, DESC) \
    else if (strcmp(#CMD, msg->content) == 0) { \
        str_append(&reply_message, DESC); \
    }
#include "command.inc"
    else {
        /* strlen("Unknown command ``") = 18, plus '\0' became 19 */
        reply_message = (char*)malloc(sizeof(char) * (strlen(msg->content) + 19));
        sprintf(reply_message, "Unknown command `%s`", msg->content);
    }


    DiscordCreateMessageParams params = {
        .content = reply_message
    };

    discord_message_reference_init(&msg_ref);

    if(msg->referenced_message) {
        msg_ref.message_id = msg->referenced_message->id;
        msg_ref.channel_id = msg->channel_id;
        msg_ref.guild_id = msg->guild_id;

        params.message_reference = &msg_ref;
    }

    discord_create_message(client, msg->channel_id, &params, NULL);

    free(reply_message);
}

/**
 * Prints startup message on stdout.
 */
static void
startup_message(Discord *client, const DiscordUser* bot)
{
    UNUSED(client);
    UNUSED(bot);
    printf("\n\nBot succesfully connected to Discord as %s#%s!\n\n",
        bot->username, bot->discriminator);
}


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

    discord_global_init();

    client = discord_config_init(config_file);
    assert(NULL != client);

    discord_set_prefix(client, COMMAND_PREFIX);

    #define COMMAND(CMD,DESC) \
        discord_set_on_command(client, #CMD, &on_command_##CMD);
    #include "command.inc"
    // discord_set_on_command(client, "echo", &on_command_echo);
    discord_set_on_ready(client, &startup_message);

    discord_run(client);

    discord_cleanup(client);

    discord_global_cleanup();
    return 0;
}
