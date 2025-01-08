#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_path_directories()
{
	char *path_env = getenv("PATH");

	if (path_env == NULL)
	{
		printf("La variable d'environnement PATH est vide ou non d√finie.\n");
		return;
	}

	char *path_copy = strdup(path_env);
	if (path_copy == NULL)
	{
		perror("Erreur lors de la duplication de PATH");
		return;
	}

	char *directory = strtok(path_copy, delimiter);
	while (directory != NULL)
	{
		printf("%s\n", directory);
		directory = strtok(NULL, delimiter);
	}
	free(path_copy);
}

