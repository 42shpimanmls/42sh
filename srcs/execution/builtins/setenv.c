#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "abstract_list.h"

#include "init/init.h"  // replace by envHelper

BUILTIN_RET		builtin_setenv(BUILTIN_ARGS)
{
	t_variable	**env;

	env = &get_shell_env()->variables;

	if (argc == 3)
	{
		setenv_as(env, argv[1], argv[2]);
	}
	else
	{
		ft_printf("Usage: setenv <key> <value>\n");
	}
	return (STATUS_SUCCESS);
}

void			setenv_as(t_variable **env, char *name, char*value)
{
	if (env && ft_strlen(name) > 0)
	{
		if (check_if_variable_exist(*env, name))
		{
			unsetenv_as(env, name);
		}
		list_push_back((t_abstract_list**)&env,
			(t_abstract_list*)create_variable(name, value, true));
	}
}
