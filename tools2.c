#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * split_line - function to read a line
 * @line: line to read
 * Return: the list of args
 */
char **split_line(char *line)
{
	int capacity = 10;
	char **args = malloc(sizeof(char *) * capacity);
	char *token = strtok(line, " ");
	int arg_count = 0;

	if (!args)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	while (token != NULL)
	{
		if (arg_count >= capacity)
		{
			fprintf(stderr, "Erreur: trop d'arguments (max %d)\n", capacity);
			exit(EXIT_FAILURE);
		}
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
		extern  char **environ;
		char **env = environ;

		while (*env)/* Goes through the environment varibales */
		{
			printf("%s\n", *env); /* Print each environment variable */
			env++;
		}
	}
}
