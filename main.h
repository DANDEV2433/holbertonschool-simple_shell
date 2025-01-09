#ifndef MAIN_H
#define MAIN_H

extern char **environ;

typedef struct pid_s
{
	int pid;
}pid_s;

void handle_sigint(int sig);
char *find_command(char *command);
void execute_command(char *argv[], char *command_path, char *program_name);
int handle_exit(char *line);
void handle_env(char *args[]);
char **split_line(char *line);
void process_input(char *argv[]);

#endif
