#include "main.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * read_file - reads a bytecode file and runs commands
 * @filename: pathname to file
 * @stack: pointer to the top of the stack
 */

void read_file(char *filename, stack_t **stack)
{
    char *line = NULL;
    size_t i = 0;
    int line_count = 1;
    instruct_func s;
    int check;

    var_global.file = fopen(filename, "r");

    if (var_global.file == NULL)
    {
        fprintf(stderr, "Error: Can't open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    while (fgets(var_global.buffer, i, var_global.file) != NULL)
    {
        line = par_se(var_global.buffer, stack, line_count);
        if (line == NULL || line[0] == '#')
        {
            line_count++;
            continue;
        }
        s = get_func(line);
        if (s == NULL)
        {
            fprintf(stderr, "L%d: unknown instruction %s\n", line_count, line);
            exit(EXIT_FAILURE);
        }
        s(stack, line_count);
        line_count++;
    }
    free(var_global.buffer);
    check = fclose(var_global.file);
    if (check == -1)
        exit(-1);
}


/**
 * get_func -  checks opcode and returns the correct function
 * @s: the opcode
 * Return: returns a functions, or NULL on failure
 */
instruct_func get_func(char *s)
{
	int n;

	instruction_t inst[] = {
		{"push", _push},
		{"pall", _pall},
		{"pint", _pint},
		{"pop", _pop},
		{"swap", _swap},
		{"add", _add},
		{"nop", _nop},
		{"sub", _sub},
		{"mul", _mul},
		{"div", _div},
		{"mod", _mod},
		{"pchar", _pchar},
		{"pstr", _pstr},
		{"rotl", _rotl},
		{"rotr", _rotr},
		{NULL, NULL},
	};

	n = 0;
	while (inst[n].f != NULL && strcmp(inst[n].opcode, s) != 0)
	{
		n++;
	}

	return (inst[n].f);
}

/**
 * is_num - checks if a string is a number
 * @c: string being passed
 * Return: returns 1 if string is a number, 0 otherwise
 */
int is_num(char *c)
{
	unsigned int n;

	if (c == NULL)
		return (0);
	n = 0;
	while (c[n])
	{
		if (c[0] == '-')
		{
			n++;
			continue;
		}
		if (!isdigit(c[n]))
			return (0);
		n++;
	}
	return (1);
}

/**
 * par_se - parses a line for an opcode and arguments
 * @l: the line to be parsed
 * @s: pointer to the head of the stack
 * @ln: the current line number
 * Return: returns the opcode or null on failure
 */
char *par_se(char *l, stack_t **s, unsigned int ln)
{
	char *op, *c, *arg;
	(void)s;

	c = "push";
	op = strtok(l, "\n ");
	if (op == NULL)
		return (NULL);

	if (strcmp(op, c) == 0)
	{
		arg = strtok(NULL, "\n ");
		if (is_num(arg) == 1 && arg != NULL)
		{
			var_global.push_arg = atoi(arg);
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", ln);
			exit(EXIT_FAILURE);
		}
	}
	return (op);
}
