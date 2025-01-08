#include <stdio.h>
#include <unistd.h>

int main(void)
{
	char *path = "/bin/ls";
	char *argv[] = { "ls", "-l", "/usr/", NULL};
	//char *envp[] = { "PATH=", "TERM=xterm-256color", NULL };

	printf("Before execve\n");
	if (execve(argv[0], argv, NULL) == -1)
		perror("Error:");
	printf("After execve\n");
	return (0);
}
