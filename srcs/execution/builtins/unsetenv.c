#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "init/init.h"

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
			unsetenv_as(env, argv[i]);
		}
		return (STATUS_SUCCESS);
	}
	else
	{
		ft_printf("Usage: unsetenv <key> ...\n");
	}
	return (STATUS_FAILURE);
}

void	unsetenv_as(t_variable **env, char *name)
{
	if (env && ft_strlen(name) > 0)
		pop_variable_by_name(env, name);
}
