#include "key.h"

bool input_is_digit(char *arg)
{
	bool is_digit = true;
	size_t len = strlen(arg);

	for (size_t i = 0; i < len; i++)
	{
		if (!isdigit(arg[i]))
			is_digit = false;
	}

	return is_digit;
}