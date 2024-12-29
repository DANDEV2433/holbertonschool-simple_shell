#include <stdio.h>
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
 * main - prints value of environment variable using _getenv
 * Return: 0
*/
int main(void)
{
	char *value;

	value = _getenv("HOME");

	if (value)
	{
	printf("HOME: %s\n", value);
	}
	else
	{
	printf("HOME not found\n");
	}
	return (0);
}
