#include "main.h"

void extract_external_commands(char **str)
{
    int fd = open("command.txt",O_RDONLY);
    int i = 0,j = 0;
    char ch;
    int ret;
    str[i] = malloc(25 * sizeof(char));
    while((ret = read(fd,&ch,1)) > 0 && ch != EOF)    // here i am extracting extrnal commands from file  to the array
    {
        
        if(ch == '\n')
        {
            str[i][j] = '\0';
            i++;
            j = 0;
            str[i] = malloc(25 * sizeof(char));
        }
        else
        {
            str[i][j] = ch;
            j++;
        }
    }
     close(fd);
}