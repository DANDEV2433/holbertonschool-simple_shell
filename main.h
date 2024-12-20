#ifndef MAIN_H
#define MAIN_H
#include <sys/types.h>


struct typedef pid_s
{
	struct pid_s int;
}pid_t;

int main(int ac, char **av);
int main(void);
int main(int ac, char **av, char **env);
#endif
