#include "main.h"

char *get_command(char *input_string)
{
    char temp[100];
    strcpy(temp,input_string);
    char *cmd = malloc(20);
    strtok(temp," ");
    strcpy(cmd,temp);
    return cmd;
}