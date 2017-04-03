#include <libft.h>

void	fatal_error(char const *str)
{
	ft_putstr_fd("42sh: fatal error: ", 2);
	ft_putendl_fd(str, 2);
	exit(42);
}
