#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

#define MAX_ARGS 100
#define PROMPT ":) "

/**
 * split_line - function to read a line
 * @line: line to read
 * Return: the list of args
 */
char **split_line(char *line)
{
	char **args = malloc(sizeof(char *) * MAX_ARGS);
	char *token;
	int arg_count = 0;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	token = strtok(line, " ");
	while (token && arg_count < MAX_ARGS - 1)
	{
		args[arg_count++] = token;
		token = strtok(NULL, " ");
	}

	args[arg_count] = NULL;
	return (args);
}

/**
 * handle_env - handle environment
 * @args: arguments
 */
void handle_env(char *args[])
{
	/* Check if the command is 'env'*/
	if (args[0] != NULL && strcmp(args[0], "env") == 0)
	{
		char **env = environ;

		while (*env)/* Goes through the environment varibales */
		{
			printf("%s\n", *env); /* Print each environment variable */
			env++;
		}
	}
}

/**
 * handle_sigint - Handles the SIGINT signal (Ctrl+C).
 * @sig: The signal number.
 */
void handle_sigint(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	printf(PROMPT);
	fflush(stdout);
}

/**
 *_getenv - gets the value of an environment variable
 * @name: the name of environment variable
 * Return: the value of variable or NULL
 */
char *_getenv(const char *name)
{
	int i;
	size_t len = strlen(name);

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], name, len) == 0 && environ[i][len] == '=')
		/**
		* Compare len/environ[i] with name to see if =, check next character is =.
		*/
			return (environ[i] + len + 1);
			/**
			* returns pointer to environment variable value, after =.
			*/
	}
	return (NULL);
}
