#ifndef MAIN_H
#define MAIN_H

typedef struct pid_s
{
	int pid;
}pid_s;

void handle_sigint(int sig);
char *find_command(char *command);
void execute_command(char *argv[], char *command_path);

#endif
