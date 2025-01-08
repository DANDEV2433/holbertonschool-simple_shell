#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "main.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: the name of environment variable
 * Return: the value of variable or NULL
 */
char *_getenv(const char *name)
{
	return (getenv(name));
}

/**
 * get_input - displays the shell prompt and reads the input from the user
 * Return: the input string
 */
char *get_input(void)
{
	size_t len = 0;
	char *input = NULL;

	printf(":) ");
	fflush(stdout);
	if (getline(&input, &len, stdin) == -1)
	{
	perror("error");
	free(input);
	return (NULL);
	}
	input[strcspn(input, "\n")] = '\0';
	return (input);
}

/**
 * build_full_path - builds the full path for a command
 * @directory: directory to add to the command
 * @command: the command itself
 * Return: the full path to the command
 */
char *build_full_path(char *directory, char *command)
{
	char *full_path = malloc(1024);

	if (full_path == NULL)
	{
	perror("malloc failed");
	return (NULL);
	}

	snprintf(full_path, 1024, "%s/%s", directory, command);/*Const chem1 complet*/
	return (full_path);
}

/**
 * find_command_in_path - finds a command in the directories specified in PATH
 * @argv: array to store command and arguments
 * @path_env: the PATH environment variable
 * Return: the full path of the command or NULL if not found
 */
char *find_command_in_path(char *argv[], char *path_env)
{
	char *path_copy = strdup(path_env);
	char *directory = strtok(path_copy, ":");
	char *full_path;

	if (path_copy == NULL)
	{
	return (NULL);
	}
	while (directory != NULL)
	{
	full_path = build_full_path(directory, argv[0]);
	if (full_path == NULL)
	{
	free(path_copy);
	return (NULL);
	}
	if (access(full_path, X_OK) == 0)/*Vérifie si le fichier est exécutable*/
	{
	free(path_copy);
	return (full_path);/*Retourne chemin complet si la commande est trouvée*/
	}
	free(full_path);
	directory = strtok(NULL, ":");
	}

	free(path_copy);
	return (NULL);
}
/**
 * handle_command - handles the execution of the command
 * @argv: array of strings representing the command and its arguments
 * @command_path: the full path of the command
 */
void handle_command(char *argv[], char *command_path)
{
	int status;
	pid_t pid = fork();

	if (pid == -1)
	{
	perror("error");
	exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
	if (execve(command_path, argv, environ) == -1)
	{
	perror("error");
	exit(EXIT_FAILURE);
	}
	}
	else
	{
	wait(&status);
	}
}

