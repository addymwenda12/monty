#include "monty.h"

/**
 * _isdigit - checks if a string is a digit
 * @str: string to check
 * 
 * Return: 1 if string is a string, 0 otherwise
*/
int _isdigit(char *str)
{
	int i = 0;

	if (str == NULL)
	{
		return (0);
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
	}

	return (1);
}
