#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "init/init.h"  // replace by envHelper

BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS)
{
	t_variable	**env;
	size_t		i;

	env = &get_shell_env()->variables;
	if (argc > 1)
	{
		i = 0;
		while (argv[++i])
		{
			pop_variable_by_name(env, argv[i]);
		}
	}
	else
	{
		ft_printf("Usage: unsetenv <key> ...\n");
	}
	return (STATUS_SUCCESS);
}
