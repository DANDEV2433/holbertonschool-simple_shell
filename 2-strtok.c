#include <stdio.h>
#include <string.h>
/**
* main - function strtok
* Return: void
*/

int main(void)
{
	char phrase[] = "la fonction strtok";
	char *token;

	token = strtok(phrase, " ");

	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	return (0);
}
