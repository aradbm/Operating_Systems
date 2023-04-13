#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>

int child_pid;
#define MAX_PIPES 5 // program can hold up to 5 pipes!
void sigint_handler(int signum)
{
	killpg(child_pid, SIGINT);
}
int main()
{
	int n_pipes;
	char command[1024];
	char **commands = NULL;
	char *token;
	char temp_output[2048];
	printf("Hello to my custom shell! Enter a command: \n");
	while (1)
	{
		printf("$ ");
		fgets(command, 1024, stdin);
		if (command[strlen(command) - 1] == '\n')
			command[strlen(command) - 1] = '\0'; // remove newline
		if (strcmp(command, "exit") == 0)
			return 0;

		n_pipes = 0;
		token = strtok(command, "|");
		commands = malloc(sizeof(char *));
		while (token != NULL)
		{
			commands = realloc(commands, (n_pipes + 1) * sizeof(char *));
			commands[n_pipes] = token;
			if (commands[n_pipes][strlen(commands[n_pipes]) - 1] == '\n')
				commands[n_pipes][strlen(commands[n_pipes]) - 1] = '\0'; // remove newline
			token = strtok(NULL, "|");
			n_pipes++;
		}
		// now i have commands[i] with commands to execute
		// i need to open pipes in the number of [i+1][i]
		int pipes[MAX_PIPES + 1][2];
		int pids[MAX_PIPES];
		int i;
		for (i = 0; i < n_pipes + 1; i++) // Creating pipes for comunication:
		{
			if (pipe(pipes[i]) == -1)
			{
				printf("Error 1\n");
				return 1;
			}
		}
		for (i = 0; i < n_pipes; i++) // Creating the child proccesses to execute commands
		{
			pids[i] = fork();
			if (pids[i] == -1)
			{
				printf("Error 2\n");
				return 1;
			}
			if (pids[i] == 0)
			{
				// Child process
				for (size_t j = 0; j < n_pipes + 1; j++)
				{
					if (i != j)
						close(pipes[j][0]);
					if (i + 1 != j)
						close(pipes[j][1]);
				}
				// execute commands[i] with knowing the temp_output in mind!
				return 0;
			}
		}
		for (i = 0; i < n_pipes; i++)
			wait(NULL);
	}
	return 0;
}