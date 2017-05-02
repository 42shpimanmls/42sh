#include "builtins.h"

#include "utils.h"
#include <libft.h>

int		builtin_exit(int argc, char **argv)
{
	int	ret;

	if (argc > 1)
		ret = ft_atoi(argv[1]);
	else
		ret = get_last_exit_status();
	if (ret < 0)
	{
		ft_dprintf(STDERR_FILENO, "%s: wrong exit value: %d\n", SHNAME, ret);
		ret = 2;
	}
	else if (ret > 255)
	{
		ret = ret % 256;
	}
	exit(ret);
}
