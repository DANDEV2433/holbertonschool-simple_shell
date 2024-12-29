#include <stdio.h>
#include "main.h"
/**
 * main - prints the environment using the global variable environ
 * Return: 0
 */
int main(void)
{
	unsigned int i;

	i = 0;
	while (environ[i] != NULL)
{
	printf("%s\n", environ[i]);
	i++;
}
return (0);
}
