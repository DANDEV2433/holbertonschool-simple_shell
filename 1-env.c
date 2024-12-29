#include <stdio.h>
#include "main.h"
/**
 * main - a program that prints the address of env and environ
 * @ac: the number of arguments passed to the program
 * @av: an array of strings representing the arguments
 * @env: an array of strings representing the environment variables
 * Return: 0
*/
int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	printf("%p\n", (void *)env);
	printf("%p\n", (void *)environ);

	return (0);
}
