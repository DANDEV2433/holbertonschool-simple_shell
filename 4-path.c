#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char *directory;
	struct Node *next;
} Node;

Node* create_node(const char *directory)
{
	Node *new_node = (Node *)malloc(sizeof(Node));
	if (!new_node)
	{
		perror("Erreur d'allocation de mémoire");
		exit(EXIT_FAILURE);
	}
	new_node->directory = strdup(directory);
	if (!new_node->directory)
	{
		perror("Erreur d'allocation de mémoire pour le répertoire");
		free(new_node);
		exit(EXIT_FAILURE);
	}
	new_node->next = NULL;
	return new_node;
}

Node* build_path_list()
{
	char *path_env = getenv("PATH");
	if (!path_env)
	{
		printf("La variable d'environnement PATH est vide ou non définie.\n");
		return NULL;
	}

	char *path_copy = strdup(path_env);
	if (!path_copy)
	{
		perror("Erreur lors de la duplication de PATH");
		exit(EXIT_FAILURE);
	}

	Node *head = NULL, *current = NULL;
	char *directory = strtok(path_copy, delimiter);

	while (directory != NULL)
	{
		Node *new_node = create_node(directory);
		if (head == NULL)
			head = new_node;
		else
			current->next = new_node;
		current = new_node;
		directory = strtok(NULL, delimiter);
	}

	free(path_copy);
	return head;
}

void print_list(Node *head)
{
	Node *current = head;
	while (current != NULL)
	{
		printf("%s\n", current->directory);
		current = current->next;
	}
}

void free_list(Node *head)
{
	Node *current = head;
	while (current != NULL)
	{
		Node *temp = current;
		current = current->next;
		free(temp->directory);
		free(temp);
	}
}
