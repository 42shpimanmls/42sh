#include <libft.h>
#include <stdbool.h>

bool		str_is_digits(char const *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str += 1;
	}
	return (true);
}
