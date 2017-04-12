# include <stdbool.h>
# include <libft.h>

bool is_an_argument(char *arg)
{
	if (arg && ft_strlen(arg) >= 2)
	{
		if (arg[0] == '-')
			return (true);
	}
	return (false);
}
