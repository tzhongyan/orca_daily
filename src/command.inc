/**
 * Macro for including all commands.
 * So that we can add it on !!help
 *
 * Usage: COMMAND(cmd, "desc")
 *   - cmd: the command itself
 *   - desc: the description of the command to be included in help
 * 
 * Make sure we have on_command_##CMD defined.
 */

#ifndef COMMAND /* Prevent accidental inclusion */
#define COMMAND(CMD, DESC)
#endif

COMMAND(help, "Shows help")
COMMAND(echo, "Echo for what you are saying")

#undef COMMAND
