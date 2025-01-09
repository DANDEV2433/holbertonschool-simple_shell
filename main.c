#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include "main.h"

#define PROMPT ":) "
#define MAX_PATH_LEN 1024

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
}

/**
 * find_command - Search for a command in the PATH.
 * @command: Command to find.
 * Return: The full path of the command or NULL if not found.
 */
char *find_command(char *command)
{
	char *path_env = getenv("PATH");
	char *path_env_copy, *path;
	static char full_path[MAX_PATH_LEN];

	if (!path_env)
	{
	fprintf(stderr, "Error: PATH not set\n");
	return (NULL);
	}
	/* Command is already an absolute path or executable in current dir */
	if (command[0] == '/' || access(command, X_OK) == 0)
	{
	return (command);
	}
	path_env_copy = malloc(strlen(path_env) + 1);/*Allocate memory for a copy*/
	if (!path_env_copy)
	{
	perror("malloc");
	return (NULL);
	}
	strcpy(path_env_copy, path_env); /*copy string PATH in path_env_copy*/

	path = strtok(path_env_copy, ":");
	while (path)
	{
	sprintf(full_path, "%s/%s", path, command);
	if (access(full_path, X_OK) == 0)
	{
	free(path_env_copy);
	return (full_path);
	}
	path = strtok(NULL, ":");
	}

	free(path_env_copy);
	return (NULL);
}

/**
 * execute_command - Execute a command.
 * @argv: Array of command and arguments.
 * @command_path: Full path of the command.
 * @program_name: name of program.
 */
void execute_command(char *argv[], char *command_path, char *program_name)
{
	pid_t pid = fork();

	if (pid == 0) /* Child process */
	{
	if (execve(command_path, argv, environ) == -1)
	{
	fprintf(stderr, "%s: 1: %s: not found\n", program_name, argv[0]);
	exit(EXIT_FAILURE);
	}
	}
	else if (pid < 0) /* Fork error */
	{
	perror("fork");
	}
	else /* Parent process */
	{
	wait(NULL);
	}
}
/**
 * handle_exit - Handles the exit command.
 * @line: The line containing the command.
 * Return: 1 if 'exit' was detected, 0 otherwise.
 */
int handle_exit(char *line)
{
	if (strcmp(line, "exit") == 0)
	{
	free(line);  /* Free the allocated memory */
	exit(0);     /* Exit the program with success */
	}
	return (0);  /* Return 0 if it's not an 'exit' command */
}

/**
 * main - Simple shell.
 * @argc: Argument count.
 * @argv: an array of command-line arguments.
 * description: Entry point of the simple shell program
 * Return: 0 on success.
 */
int main(int argc __attribute__((unused)), char *argv[])
{
	signal(SIGINT, handle_sigint);
	process_input(argv);
	return (0);
}

void process_input(char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	char *args[100];
	char *command = NULL;
	int i = 0;

	while (1)
	{
		if (isatty(STDIN_FILENO))
			printf(PROMPT);

		if (getline(&line, &len, stdin) == -1)
		{
			if (isatty(STDIN_FILENO))
				printf("\n");
			break;
		}

		line[strcspn(line, "\n")] = '\0';
		if (handle_exit(line) || line[0] == '\0')
			continue;

		args[i] = strtok(line, " ");
		while (args[i] != NULL && i < 99)
			args[++i] = strtok(NULL, " ");
		args[i] = NULL;

		if (args[0] == NULL)
			continue;

		command = find_command(args[0]);
		if (!command)
			fprintf(stderr, "%s: 1: %: not found\n", argv[0], args[0]);
		else
			execute_command(args, command, argv[0]);
	}
	free(line);
}
