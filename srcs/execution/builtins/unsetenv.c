#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "init/init.h"  // replace by envHelper

BUILTIN_RET 		builtin_unsetenv(BUILTIN_ARGS)
{
	t_variable	**env;
	size_t		i;

	env = &get_shell_env()->variables;	
	if (argc > 0)
	{
		i = -1;
		while (argv[++i])
		{
			pop_variable_by_name(env, argv[0]);
		}
	}
	else
	{
		ft_printf("Usage: unsetenv <key> ...\n");
	}
}
