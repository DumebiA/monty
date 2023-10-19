#include "main.h"

global_var var_global;

/**
 * main - driver function monty
 * @ac: int num of arguments
 * @av: opcode file
 * Return: 0
 */
int main(int ac, char **av)
{
	stack_t *st;

	st = NULL;
	if (ac != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	read_file(av[1], &st);

	free_dlistint(st);
	return (0);
}
