#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t child_pid;
	int status;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return (1);
	}
	if (child_pid == 0)
	{
		printf("Wait for m, wait for me\n");
		sleep(3);
	}
	else
	{
		wait(&status);
		printfd("Oh, it's all better now\n");
	}
	return (0);
}
