#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Fonction pour lire une ligne depuis l'entrée standard
char *read_line(void)
{
    char *line = NULL;
    size_t len = 0;

    if (getline(&line, &len, stdin) == -1)
    {
        free(line);
        return NULL;
    }

    // Supprimer le saut de ligne final
    line[strcspn(line, "\n")] = '\0';
    return line;
}

// Fonction pour découper une ligne en arguments
char **split_line(char *line)
{
    char **args = NULL;
    char *token = strtok(line, " ");
    int arg_count = 0;

    while (token != NULL)
    {
        args = realloc(args, sizeof(char *) * (arg_count + 1));
        if (!args)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        args[arg_count++] = token;
        token = strtok(NULL, " ");
    }

    args = realloc(args, sizeof(char *) * (arg_count + 1));
    if (!args)
    {
        perror("realloc");
        exit(EXIT_FAILURE);
    }
    args[arg_count] = NULL;
    return args;
}

// Fonction pour exécuter une commande
void execute_command(char **args)
{
    pid_t pid = fork();

    if (pid == -1)
    {
        perror("fork");
        return;
    }

    if (pid == 0)
    {
        // Processus enfant
        if (execvp(args[0], args) == -1)
        {
            perror(args[0]);
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        // Processus parent
        int status;
        waitpid(pid, &status, 0);
    }
}

// Fonction principale
int main(void)
{
    char *line;
    char **args;

    while (1)
    {
        printf("$ ");
        line = read_line();
        if (!line)
        {
            printf("\n");
            break;
        }

        if (strcmp(line, "") == 0)
        {
            free(line);
            continue;
        }

        args = split_line(line);
        if (args[0] != NULL)
            execute_command(args);

        free(args);
        free(line);
    }

    return 0;
}

