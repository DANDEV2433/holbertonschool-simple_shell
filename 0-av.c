#include <stdio.h>
#include "main.h"

int main(int ac, char **av)
{
	(void)ac;

	while (av != NULL)
	{
		printf("%s\n", *av);
		av++;
	}
	return (0);
}