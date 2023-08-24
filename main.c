#include "monty.h"

/**
 * parse_and_execute - parses the line and executes the opcodes
 * @line: line from the bytecode file
 * @stack: double pointer to the head of the stack
 * @line_number: line number
 * 
 * Return: void
 */
void parse_and_execute(char *line, stack_t **stack, unsigned int line_number)
{
	char *opcode, *n_str;
	size_t leading_whitespace = strspn(line, " \t");

	line += leading_whitespace;

	opcode = strtok(line, "\n\t\r ");
	if (opcode == NULL || opcode[0] == '#')
		return;
	if (strcmp(opcode, "push") == 0)
	{
		n_str = strtok(NULL, "\n\t\r ");
		if (n_str == NULL || _isdigit(n_str) == 0)
		{
			fprintf(stderr, "L%d: usage push integer\n", line_number);
			exit(EXIT_FAILURE);
		}
		push(stack, atoi(n_str));
	}
	else if (strcmp(opcode, "pall") == 0)
	{
		pall(stack, line_number);
	}
	else
	{
		fprintf(stderr, "L%d: unknown instruction %s\n", line_number, opcode);
		exit(EXIT_FAILURE);
	}
}

/**
 * main - entry point for Monty interpreter
 * @argc: argument count
 * @argv: argument vector
 * 
 * Return: EXIT_SUCCESS on success, EXIT_FAILURE on failure
*/
int main(int argc, char *argv[])
{
	FILE *file;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	unsigned int line_number = 0;

	stack_t *stack = NULL;

	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}

	file = fopen(argv[1], "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
	}

	while ((read = getline(&line, &len, file)) != -1)
	{
		line_number++;
		parse_and_execute(line, &stack, line_number);
	}

	free(line);
	fclose(file);
	return (EXIT_SUCCESS);
}
