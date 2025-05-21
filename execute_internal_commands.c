#include "main.h"
extern stop_list *head;
extern int stop_count;
extern int bg_flag;
extern char bg_buffer[20];
int fg_flag = 0;
void execute_internal_commands(char *input_string)
{
    if(!strncmp(input_string,"exit",4))
        exit(0);
    
    else if(!strcmp(input_string,"pwd"))
    {
        char buffer[100];
        getcwd(buffer,100);
        printf("%s\n",buffer);
    }
    else if(!strncmp(input_string,"cd",2))
    {
        char *space;
        if((space = strchr(input_string,' '))!= NULL)
        chdir(space+1);
    }
    else if(!strcmp(input_string,"echo $?"))
    {
        int status;
        printf("%d\n",WEXITSTATUS(status));
    }
    else if(!strcmp(input_string,"echo $$"))
    {
        printf("%d\n",getpid());
    }
    else if(!strcmp(input_string,"echo $SHELL"))
    {
        char *temp = getenv("SHELL");
        printf("%s\n",temp);
    }
    else if(!strcmp(input_string,"jobs"))
    {
        print_list(head);
    }
    else if(!strcmp(input_string,"fg"))
    {
        if(head ==  NULL)
        {
            printf("minishell: fg: current: no such job\n");
        }
        else
        {
            stop_list *stop_cmd = get_command_fg_bg(head);
            printf("%s\n",stop_cmd ->command);
            kill(stop_cmd ->pid,SIGCONT);

            int status;
            waitpid(stop_cmd->pid, &status, WUNTRACED);
            stop_count--;
            delete_at_last(&head);
            fg_flag = 1;
        }
    }
    else if(!strcmp(input_string,"bg"))
    {
        bg_flag = 0;
        if(head == NULL)
            printf("bg: current: no such job\n");
        else
        {
            stop_list *stop_cmd = get_command_fg_bg(head);
            printf("[%d]+ %s &\n",stop_count,stop_cmd -> command);
            strcpy(bg_buffer,stop_cmd ->command);
            kill(stop_cmd -> pid,SIGCONT);
            waitpid(stop_cmd->pid,NULL,__W_CONTINUED);
            delete_at_last(&head);
        }
    }
}