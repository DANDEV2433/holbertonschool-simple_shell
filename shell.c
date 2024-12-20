#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
/**
* execute_command - exécute la commande dans le processus enfant
* @argv: chaînes de caractères représentant la commande et ses arguments
*/
void execute_command(char *argv[])
{
	if (execve(argv[0], argv, NULL) == -1)
	{
	perror("error");
	exit(EXIT_FAILURE);
	}
}
/**
* main - fonction qui exécute un super simple shell
* Return: void
*/
int main(void)
{
	char *input = NULL;/*Pointeur pour stocker l'entrée utilisateur*/
	size_t len = 0;/*Taille de l'entrée utilisateur*/
	char *argv[2];/*1er commande, 2ème fin des arguments(NULL)*/
	pid_t pid;/*Variable ID processus enfant*/
	int status;/*Variable pour stocker la terminaison procassus enfant*/

	while (1)
	{
		printf("$ ");
		fflush(stdout);/*s'assure que $ est affiché*/
		if (getline(&input, &len, stdin) == -1)/*stock la str dans input*/
		{
			perror("error");
			free(input);
			continue;
		}
		input[strcspn(input, "\n")] = '\0';
		if (strcmp(input, "") == 0)
			continue;
		argv[0] = strtok(input, " ");/*divise la chaîne en tokens*/
		argv[1] = NULL;/*fin du tab*/
		pid = fork();
		if (pid == -1)
		{
			perror("error");
			free(input);
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
		execute_command(argv);
		}
		else
		{
			wait(&status);
		}
	}
		free(input);
		return (0);
}
