#include "main.h"

void execute_external_commands(char *input_string)
{
	char *vector[20] = {0};
	char *token = strtok(input_string," ");
	int i = 0;

	//convert the input string into a argument vector
	while(token != NULL)
	{
		vector[i] = malloc(10);
		strcpy(vector[i],token);
		token= strtok(NULL," ");
		i++;
	}
	//check pipe is present or not
	int index = 1;
	int pos[10];
	pos[0] = 0;
	for(int i = 0 ; vector[i] != NULL ; i++)
	{
		if(strcmp(vector[i],"|") == 0)
		{
			pos[index++] = i+1;
			vector[i] = NULL;
		}
	}

	if(index == 1)
	{
		execvp(vector[0],vector);
		wait(NULL);
	}
	else if (index > 1)
	{
		int backup_stdout = dup(1);
		int backup_stdin = dup(0);
		int fd[2];
		for(int i = 0; i < index ; i++)
		{
			pipe(fd);
			int pid = fork();
			if(pid == 0)
			{
				close(fd[0]);
				if(i == index - 1)
					dup2(backup_stdout,1);
				else
					dup2(fd[1],1);
				execvp(vector[pos[i]],vector + pos[i]);
				printf("EXEC FAILED\n");
			}
			else if(pid > 0)
			{
				close(fd[1]);
				dup2(fd[0],0);
				close(fd[0]);
				wait(0);
			}
			else
			{
				perror("fork");
			}
		}
		dup2(backup_stdout,1);
		dup2(backup_stdin,0);
	}
	//free the memory occupied by the vector
	for(int i = 0 ; vector[i] != NULL ; i++)
	{
		free(vector[i]);
	}

}