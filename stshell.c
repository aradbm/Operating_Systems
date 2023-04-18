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
#define MAX_PIPES 10 // program can hold up to 10 pipes!

void sigint_handler(int signum)
{
	printf("\nCtrl+C pressed. Please enter a command.\n");
	fflush(stdout);
}

int main()
{
	int n_pipes;
	char command[1024];
	char **commands = NULL;
	char *token;
	char temp_output[4096] = {0};
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
				if (i == 0) // first child process
				{
					// Set stdout to the write end of the first pipe
					dup2(pipes[i][1], STDOUT_FILENO);

					// Close the read end of the first pipe
					close(pipes[i][0]);
				}
				else if (i == n_pipes)
				{
					// Parent process
					signal(SIGINT, sigint_handler);

					for (size_t j = 0; j < n_pipes + 1; j++)
					{
						close(pipes[j][1]);
					}

					// read from the read end of the pipe
					int bytes_read = read(pipes[n_pipes][0], temp_output, sizeof(temp_output));
					char *temp = malloc(sizeof(char) * (bytes_read + 1));
					strncpy(temp, temp_output, bytes_read);
					temp[bytes_read] = '\0';
					strcpy(temp_output, temp);
					free(temp);

					// Clean the buffer
					while (read(pipes[n_pipes][0], temp_output, sizeof(temp_output)) > 0)
					{
						// do nothing
					}

					// close the read end of the pipe
					close(pipes[n_pipes][0]);

					// print the output
					printf("%s", temp_output);

					// wait for the child processes to finish
					for (size_t j = 0; j < n_pipes; j++)
					{
						waitpid(pids[j], NULL, 0);
					}
					free(commands);
					free(token);
				}
			}
		}
	}
}
