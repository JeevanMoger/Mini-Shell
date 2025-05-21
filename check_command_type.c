#include "main.h"
extern char *external_commands[200];

int check_command_type(char *command)
{
    //store the builtin commands
    char *builtins[] = {"echo", "printf", "read", "cd", "pwd", "pushd", "popd", "dirs", "let", "eval",
        "set", "unset", "export", "declare", "typeset", "readonly", "getopts", "source",
        "exit", "exec", "shopt", "caller", "true", "type", "hash", "bind", "help","jobs","fg","bg", NULL};
    
    // check if the input command is an builtin command
    for(int i = 0; builtins[i] != NULL ; i++)
    {
        if(!(strcmp(command,builtins[i])))
            return BUILTIN;
    }

    // check if the input command is an external command
    for(int i = 0; external_commands[i] != NULL ; i++)
    {
        if(!(strcmp(command,external_commands[i])))
            return EXTERNAL;
    }
    // If not builtin or external command return no command
    return NO_COMMAND;
}