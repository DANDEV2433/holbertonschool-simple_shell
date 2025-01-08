#ifndef MAIN_H
#define MAIN_H

#include <sys/types.h>

extern char **environ;
extern char *input;


/**
* struct pid_s - Structure pour représenter un processus.
* @pid: Identifiant du processus (PID)
*/
typedef struct pid_s
{
	int pid;
} pid_s;

char *_getenv(const char *name);
char *get_input(void);
void handle_command(char *argv[], char *command_path);
char *build_full_path(char *directory, char *command);
char *find_command_in_path(char *argv[], char *path_env);
char *parse_find(char *global_input, char *argv[]);

#endif
