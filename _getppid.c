#include <unistd.h>
#include <stdio.h>

int main()
{
	pid_t parent_pid = getppid();
	printf("Le PID du processus parent est : %d\n", get_ppid());
	return (0);
}
