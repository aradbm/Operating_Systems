#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "stdio.h"
#include "errno.h"
#include "stdlib.h"
#include "unistd.h"
#include <string.h>
#include <signal.h>
int child_pid;

void sigint_handler(int signum)
{
	kill(child_pid, SIGINT);
}
int main()
{
	int i;
	char *argv[10];
	char command[1024];
	char *token;

	printf("Hello to my custom shell! Enter a command: \n");
	while (1)
	{
		printf("$ ");
		fgets(command, 1024, stdin);
		command[strlen(command) - 1] = '\0'; // replace \n with \0

		/* parse command line */
		i = 0;
		token = strtok(command, " ");
		while (token != NULL)
		{
			argv[i] = token;
			token = strtok(NULL, " ");
			i++;
		}
		argv[i] = NULL;

		/* Is command empty */
		if (argv[0] == NULL)
			continue;
		int pid = fork();
		if (pid == 0)
		{
			// in child
			execvp(argv[0], argv);
		}
		else
		{
			// in parent
			int estatus;
			child_pid = pid;
			signal(SIGINT, sigint_handler);
			wait(&estatus);

			if (WIFEXITED(estatus))
			{
				int statusCode = WIFEXITED(estatus);
				if (statusCode != 0)
				{
					printf("Program return status code: %d", statusCode);
				}
			}
		}
		printf("\n");
	}
}

// for (i = 0; commands[i] != NULL; i++) // execute each command in order
// {
// 	if (argv[0] == NULL)
// 		continue;
// 	printf("%s\n", commands[i]);
// }
// printf("%d\n", i);
/*
commands = realloc(commands, (i + 1) * sizeof(char *));

		int *pids = malloc(sizeof(int) * i);
		int **pipes = malloc(i * sizeof(int *));
		for (int j = 0; j < i; j++)
		{
			pipes[j] = malloc(2 * sizeof(int));
		}
		for (int j = 0; j < i; j++)
		{
			if (pipe(pipes[j]) == -1)
			{
				printf("Error creating pipe!\n");
				return 1;
			}
		}
		for (int k = 0; k < i; k++)
		{
			pids[k] = fork();
			if (pids[k] == -1)
			{
				printf("Error creating child process!\n");
				return 2;
			}
			if (pids[k] == 0)
			{
				// child process
				for (int x = 0; x < i; x++)
				{
					if (k != x)
						close(pipes[x][0]);
					if (k + 1 != x)
						close(pipes[x][1]);
				}
				char buffer[1024];
				if (read(pipes[k][0], buffer, sizeof(buffer)) == -1)
				{
					printf("Error reading from pipe!\n");
					return 3;
				}
				// actions on the input
				if (write(pipes[k + 1][1], &buffer, sizeof(buffer)) == -1)
				{
					printf("Error writing to pipe!\n");
					return 4;
				}
				close(pipes[k][0]);
				close(pipes[k + 1][1]);
				exit(0);
			}
		}

		// parent process
		for (int j = 0; j < i; j++)
		{
			close(pipes[j][0]);
			close(pipes[j][1]);
		}

		for (size_t j = 0; j < i; j++)
		{
			wait(NULL);
		}
		for (int j = 0; j < i; j++)
		{
			free(pipes[j]);
		}
		free(pipes);
		free(pids);
		*/