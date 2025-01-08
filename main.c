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
	exit(0);
}

/**
 * find_command - Search for a command in the PATH.
 * @command: Command to find.
 * Return: The full path of the command or NULL if not found.
 */
char *find_command(char *command)
{
	char *path_env = getenv("PATH");
	char *path_env_copy = strdup(path_env);
	char *path = strtok(path_env_copy, ":");
	static char full_path[MAX_PATH_LEN];

	/* Command is already an absolute path or executable in current dir */
	if (command[0] == '/' || access(command, X_OK) == 0)
	{
	free(path_env_copy);
	return (command);
	}

	while (path)
	{
	snprintf(full_path, MAX_PATH_LEN, "%s/%s", path, command);
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
 */
void execute_command(char *argv[], char *command_path)
{
	pid_t pid = fork();

	if (pid == 0) /* Child process */
	{
	if (execve(command_path, argv, NULL) == -1)
	{
	perror("error");
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
 * main - Simple shell.
 * Return: 0 on success.
 */
int main(void)
{
	char *line = NULL, *command, *argv[100];
	size_t len = 0;
	int i;

	signal(SIGINT, handle_sigint); /* Handle Ctrl+C */

	while (1)
	{
	printf(PROMPT);
	if (getline(&line, &len, stdin) == -1)
	{
	free(line);
	break;
	}
	line[strcspn(line, "\n")] = '\0'; /* Remove newline */
	if (line[0] == '\0')
	continue; /* Ignore empty input */

	/* Parse the command and arguments */
	i = 0;
	argv[i] = strtok(line, " ");
	while (argv[i] != NULL)
	argv[++i] = strtok(NULL, " ");

	command = find_command(argv[0]);
	if (!command)
	{
	fprintf(stderr, "%s: command not found\n", argv[0]);
	}
	else
	{
	/* Execute the command */
	execute_command(argv, command);
	}
	}

	free(line);
	return (0);
}

