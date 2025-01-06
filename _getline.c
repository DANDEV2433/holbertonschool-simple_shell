#include <stdio.h>
#include <stdlib.h>

// Simple shell 0.1

int  main(void)
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	while (1)
	{
		printf("$ ");
		nread = getline(&line, &len, stdin);
		if (nread == -1)
		{
			printf("\n");
			break;
		}

		if (strcmp(line, "") == 0)
			continue;

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			continue;
		}

		if (pid == 0)
		{
			if (execlp(line, line, NULL) == -1)
			{
				perror(line);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}

		printf("%s", line);
	}
	free(line);
	return (0);
}
