#include <stdio.h>
#include <stdlib.h>
/**
 * main - fonction qui affiche $ et affiche la ligne d'entrée
 * Return: 0 ou -1
*/
int main(void)
{
	char *line = NULL;/** pointer pour stocker la ligne lue */
	size_t len = 0;/** taille du tampon */

	printf("$ ");
	if (getline(&line, &len, stdin) != -1)
	/**
	 *  line stock l'adresse du tampon ou la ligne lue sera sauvegardée
	 *  len représente la taille du tampon pointé par line
	 *  stdin est utilisé pour lire des entrées depuis le clavier
	*/
	{
		printf("Vous avez écrit : %s", line);
	}
	free(line);
	return (0);
}
