#include "main.h"

int check_ps1(char *input)
{
    char temp[4] = {'\0'};
    
    //copy first three characters
    strncpy(temp, input, 3);
    temp[3] = '\0'; 

    //check for PS1
    if (strcmp(temp, "PS1") == 0) 
    {
        //If PS1 present ,Check space is present or not, if not return 1
        if (strchr(input, ' ') == NULL)
            return 1;
    }
    return 0;
}