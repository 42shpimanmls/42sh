#include <stdbool.h>

bool			is_posix_blank(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}
