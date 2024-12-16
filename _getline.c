#include <stdio.h>

ssize_t getline(char **ptr, size_t *n, FILE *stream)
{
	if (ptr == NULL)
		ptr = malloc(sizeof(char)
