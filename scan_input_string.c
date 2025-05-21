#include "main.h"
pid_t child;
char *external_commands[200];
extern int bg_flag;
extern int stop_count;
extern stop_list *head;
extern stop_list *finished;
char bg_buffer[20];
extern int fg_flag;
void scan_input(char *prompt, char *input_string)
{
    signal(SIGINT,signal_handler_sigint); 
    signal(SIGTSTP,signal_handler_sigtstp);
    signal(SIGCHLD,signal_handler_sigtstp);
    extract_external_commands(external_commands);
    int status;
    while(1)
    {
        printf(ANSI_COLOR_BLUE"%s"ANSI_COLOR_RESET,prompt);

        fgets(input_string,100,stdin);
        char *temp = strchr(input_string,'\n');
        if(temp != NULL)
            *temp = '\0'; 
        if(strlen(input_string) == 0)
            continue;
        //Check for PS1
        int ret = check_ps1(input_string);
        if(ret)
        {
            char *alt_prompt = strchr(input_string,'=');
            strcpy(prompt,alt_prompt+1);    
        }
        else
        {
            char *cmd = get_command(input_string);
            int command_type = check_command_type(cmd);
            if(bg_flag == 1)
		    {

                // stop_list *finished = get_command_fg_bg(head);
                printf("[%d]+ Done \t\t %s\n",stop_count,bg_buffer);
                stop_count--;
                bg_flag = 0;
		    }
            if(command_type == EXTERNAL)
            {
                child = fork();

                //execute external command in the child process
                if(child == 0)
                {   signal(SIGINT,SIG_DFL);
                    signal(SIGTSTP,SIG_DFL);
                    signal(SIGCHLD,SIG_DFL);
                    execute_external_commands(input_string);
                }
                else
                {
                    waitpid(child,&status,WUNTRACED);
                    child = 0;
                }
            }
            else if(command_type == BUILTIN)
            {
                //Execute builtin command
                execute_internal_commands(input_string);
            }
            else
            {
                printf("NOT A VALID COMMAND\n");
            }
        }
    }
}

