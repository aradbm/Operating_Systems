#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
int child_pid = 0;
void sigint_handler(int signum)
{
	if (child_pid != 0)
	{
		kill(child_pid, signum);
	}
	else
	{
		printf("\nCtrl+C pressed. Please enter a command or write exit to get out. \n$ ");
		fflush(stdout);
	}
}
static void pipeline(char ***commands)
{
	int num_commands = 0;
	while (commands[num_commands] != NULL)
	{
		num_commands++;
	}

	int fd[2];
	int in = 0;
	pid_t pid;
	for (int i = 0; i < num_commands; i++)
	{
		pipe(fd); // create pipe for output from current command to next

		pid = fork();
		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			// child process
			if (i < num_commands - 1)
			{
				// if not last command, redirect stdout to pipe write end
				if (dup2(fd[1], STDOUT_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if (i > 0)
			{
				// if not first command, redirect stdin to pipe read end
				if (dup2(in, STDIN_FILENO) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			// close all pipe file descriptors (not needed in child)
			close(fd[0]);
			close(fd[1]);
			if (execvp(commands[i][0], commands[i]) < 0)
			{
				perror("execvp");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			// parent process
			waitpid(pid, NULL, 0);
			// close write end of pipe (not needed in parent)
			close(fd[1]);
			in = fd[0]; // set input for next command to read end of current pipe
		}
	}
}

int main()
{
	signal(SIGINT, sigint_handler);
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
		char ***args = malloc(n_pipes * sizeof(char **));
		for (int i = 0; i < n_pipes; i++)
		{
			args[i] = malloc(sizeof(char *));
			token = strtok(commands[i], " ");
			int j = 0;
			while (token != NULL)
			{
				args[i] = realloc(args[i], (j + 1) * sizeof(char *));
				args[i][j] = token;
				token = strtok(NULL, " ");
				j++;
			}
			args[i] = realloc(args[i], (j + 1) * sizeof(char *));
			args[i][j] = NULL;
		}
		args = realloc(args, (n_pipes + 1) * sizeof(char **));
		args[n_pipes] = NULL;

		pipeline(args);
		for (int i = 0; i < n_pipes; i++)
		{
			free(args[i]);
		}
		free(args);
		free(commands);
	}
}