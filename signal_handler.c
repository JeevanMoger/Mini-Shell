#include "main.h"

extern pid_t child;
int stop_count = 0;
stop_list *head;
extern char input_string[100];
int bg_flag;
stop_list *finished;
void signal_handler_sigint(int signum)
{
    if(child == 0)
    {
        printf("\n");
        printf(ANSI_COLOR_BLUE"MINISHELL$ "ANSI_COLOR_RESET);
        fflush(stdout);
    }
}

void signal_handler_sigtstp(int signum)
{
    if(signum == SIGTSTP)
    {
        if(child == 0)
        {
            printf("\n");
            printf(ANSI_COLOR_BLUE"MINISHELL$ "ANSI_COLOR_RESET);
            fflush(stdout);
        }
        else
        {
            ++stop_count;
            printf("\n[%d] stopped        %s\n",stop_count,input_string);
            insert_at_last(&head);           
        }
    }
    if(signum == SIGCHLD)
    {
        pid_t pid = waitpid(-1,NULL,WNOHANG);
        if(pid > 0)
        {
            stop_list *finished = get_command_fg_bg(head);
            if(finished != NULL)
            {
                bg_flag = 1;
            }
            
        }
    }
}