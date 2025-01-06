#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

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
		{
	/**
	* Compare len/environ[i] avec name voir si =, check caractère suivant est =
	*/
			return (environ[i] + len + 1);
	/**
	* retourne pointeur vers valeur variable environnement, après le =
	*/
		}
	}
return (NULL);
}
/**
 * get_input - displays the shell prompt and reads the input from the user
 *
 * Return: the input string
 */
char *get_input(void)
{
	char *input = NULL;
	size_t len = 0;

	printf("$ ");
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
 * parse_find - parse the input string into arguments,finds the command in PATH
 * @argv: array of strings to store arguments
 * @input: the input string
 * Return: the path of the command or NULL
 */
char *parse_find(char *input, char *argv[])
{
	int i = 0;

	argv[i] = strtok(input, " ");
	while (argv[i] != NULL)
	{
	i++;
	argv[i] = strtok(NULL, " ");
	}
	if (argv[0][0] == '/')
	{
		if (access(argv[0], X_OK) == 0)
		{
		return (strdup(argv[0]));
		return (NULL);
		}
	}
	char *path_env = _getenv("PATH"); /*la valeur variable d'environnement PATH*/

	if (!path_env)/*Si PATH n'est pas défini*/
		return (NULL);

	char *path_copy = strdup(path_env); /*Dupliquez path_env /modif l'original*/
	char *directory = strtok(path_copy, ":"); /*Divisez path_copy en répo*/
	char *full_path = malloc(1024); /*mémoire pour le chemin complet*/

	while (directory && full_path) /*Parcourez chaque répertoire*/
	{
		sprintf(full_path, "%s/%s", directory, argv[0]);/*Construit chemin complet*/
		if (access(full_path, X_OK) == 0)/*Vérifiez si le fichier est exécutable*/
		{
			free(path_copy);
			return (full_path);/*Retourne chemin complet si la commande est trouvée*/
		}
		directory = strtok(NULL, ":");/*diviser path_copy en répertoire*/
	}
	free(path_copy);
	free(full_path);
	return (NULL);
}
/**
* handle_command - handles the execution of the command
* @argv: array of strings representing the command and its arguments
* @command_path: the full path of the command
*/
void handle_command(char *argv[], char *command_path)
{
	pid_t pid = fork();

	if (pid == -1)
	{
	perror("error");
	free(command_path);
	exit(EXIT_FAILURE);
	}
	if (pid == 0)
	{
	if (execve(argv[0], argv, environ) == -1)
	{
		perror("error");
		exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		wait(&status);
		free(command_path);
	}
}
/**
* main - a function that executes a super simple shell
* description: super simple shell
* Return: 0
*/
int main(void)
{
	char *input = NULL;/*Pointeur pour stocker l'entrée utilisateur*/
	char *argv[1000];/*1er commande, 2ème fin des arguments(NULL)*/
	char *command_path;

	while (1)
	{
		input = get_input();
		if (input == NULL)
		continue;
		if (strcmp(input, "") == 0)
		{
			free(input);
			continue;
		}
		command_path = parse_find(input, argv);
		if (command_path == NULL)
		{
			printf("Command not found: %s\n", argv[0]);
			free(input);
			continue;
		}
		argv[0] = command_path;
		handle_command(argv, command_path);
		free(input);
	}
	return (0);
}
