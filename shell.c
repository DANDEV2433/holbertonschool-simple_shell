#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	char *input = NULL;/*Pointeur pour stocker l'entrée utilisateur*/
	size_t len = 0;/*Taille de l'entrée utilisateur*/
	char *argv[2];/*Tableau de chaînes de caractères pour passer les arguments à execve.1er commande, 2ème fin des arguments(NULL)*/
	pid_t pid;/*Variable ID processus enfant*/
	int status;/*Variable pour stocker la terminaison procassus enfant*/
	
	while (1)
	{
		printf("$ ");
		fflush(stdout);/*Vide le buffer de sortie pour s'assurer que le prompt est affiché immédiatement*/
		if (getline(&input, &len, stdin) == -1)/*Lit une ligne de l'entrée standard et stocke la chaîne dans input. getline alloue dynamiquement de la mémoire.*/
		{
		perror("error");
		free(input);
            	continue;
		}

		input[strcspn(input, "\n")] = '\0';/*cherche "\n" dans input et le remplace par '\0'*/
	       	if (strcmp(input, "") == 0) /* vérifie si input est vide*/
	       	{
		      	continue;
	       	}

	       	argv[0] = strtok(input, " ");/*diviser la chaîne en tokens avec les délimiteurs*/
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
    		if (execve(argv[0], argv, NULL) == -1)
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
		free(input);
		return(0);
}
