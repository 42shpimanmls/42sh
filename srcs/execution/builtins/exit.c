#include "builtins.h"

#include "utils.h"
#include <libft.h>

int		builtin_exit(int argc, char **argv)
{
	t_uchar	ret;

	if (argc > 1)
		ret = ft_atoi(argv[1]);
	else
		ret = get_last_exit_status();
	exit(ret);
}
