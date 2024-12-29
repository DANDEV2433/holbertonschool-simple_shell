#ifndef MAIN_H
#define MAIN_H
#include <sys/types.h>


typedef struct pid_s
{
	int pid;
}pid_s;

void execute_command(char *argv[]);
extern char **environ;

#endif
