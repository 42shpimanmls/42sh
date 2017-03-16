#include <stdbool.h>
#include <libft.h>

bool		is_substitution_start(char const *s)
{
	if (s && *s == '`')
		return (true);
	return (false);
}

char const	*find_substitution_end(char const *str)
{
	while (*str)
	{
		if (*str == '`')
			return (str);
		str++;
	}
	ft_putendl_fd("42sh: syntax error: missing backquote end\n", 2);
	exit(1);
}
