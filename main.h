#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>


typedef struct pid_s
{
	int pid;
}pid_s;

extern char **environ;

void execute_command(char *argv[]);
char *_getenv(const char *name);
char *get_input(void);
char *parse_find(char *input, char *argv[]);
void handle_command(char *argv[], char *command_path);

#endif
