#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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

		char **args = NULL;
		int arg_count = 0;
		char *token = strtok(line, " ");

		while (token != NULL)
		{
			args = realloc(args, sizeof(char *) * (arg_count + 1));
			if (!args)
			{
				perror("realloc");
				exit(EXIT_FAILURE);
			}
			args[arg_count++] = token;
			token = strtok(NULL, " ");
		}

		args = realloc(args, sizeof(char *) * (arg_count + 1));
		args[arg_count] = NULL;

		pid_t pid = fork();
		if (pid == -1)
		{
			perror("fork");
			free(args);
			continue;
		}

		if (pid == 0)
		{
			if (execlp(line, line, NULL) == -1)
			{
				perror(line);
				free(args);
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			int status;
			waitpid(pid, &status, 0);
		}

		free(args)
		printf("%s", line);
	}
	free(line);
	return (0);
}
