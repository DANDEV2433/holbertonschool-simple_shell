#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
/**
 * main - execve,fork and wait example
 * Return: Always 0.
 */
int main(void)
{
	pid_t child_pid;
	char *argv[] = {"/bin/ls", "-l", "/tmp", NULL};
	int status;
	int exec_result;

	for (int i = 0; i < 5; i++)
	{
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error:");
			exit(EXIT_FAILURE);
		}
	if (child_pid == 0)
	{
		exec_result = execve(argv[0], argv, NULL);
		if (exec_result == -1)
		{
		perror("Error:");
		exit(EXIT_FAILURE);
		}
	}
	else
		{
		wait(&status);
		printf("child %d\n", i + 1);
		}
	}
	return (0);
}
