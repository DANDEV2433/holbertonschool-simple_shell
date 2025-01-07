#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "main.h"

/**
* handle_sigint - Handles the SIGINT signal (Ctrl+C).
* @sig: The signal received, but not used here.
*/
void handle_sigint(int sig)
{
	(void)sig; /* Évite les avertissements */
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
}
/**
* parse_find - parse the input string into arguments, finds the command in PATH
* @argv: array of strings to store arguments
* @input: the input string
* Return: the path of the command or NULL
*/
char *parse_find(char *input, char *argv[])
{
	int i = 0;
	char *path_env;

	argv[i] = strtok(input, " ");
	while (argv[i] != NULL)
	{
	i++;
	argv[i] = strtok(NULL, " ");
	}

	if (argv[0][0] == '/')/*Si le chemin absolu est fourni*/
	{
	if (access(argv[0], X_OK) == 0)
	{
	return (strdup(argv[0]));/*Retourne le chemin complet*/
	}
	else
	{
	perror("Command not found");
	return (NULL);
	}
	}
	path_env = _getenv("PATH");/*La valeur de la variable d'environnement PATH*/
	if (!path_env)/*Si PATH n'est pas défini*/
	{
		return (NULL);
	}
	return (find_command_in_path(argv, path_env));
}
/**
 * main - Shell program input loop.
 * Return: 0.
 */
int main(void)
{
	char *argv[1000];/* 1ère commande, 2ème fin des arguments(NULL)*/
	char *command_path;
	char *input = NULL;

	signal(SIGINT, handle_sigint);

	while (1)
	{
	input = get_input();/*Demande d'entrée à l'utilisateur*/
	if (input == NULL)/*Si l'entrée est NULL (échec de getline)*/
	{
	free(input);
	continue;
	}
	if (strcmp(input, "") == 0)/*Si l'entrée est vide*/
	{
	free(input);
	continue;
	}
	/*Recherche du chemin de la commande*/
	command_path = parse_find(input, argv);
	if (command_path == NULL)
	{
	printf("Command not found: %s\n", argv[0]);
	free(input);
	continue;
	}

	argv[0] = command_path;/*Remplace la commande par son chemin absolu*/
	handle_command(argv, command_path);
	free(command_path);
	free(input);
	}
	return (0);
}
