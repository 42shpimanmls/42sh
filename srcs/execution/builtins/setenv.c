#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "abstract_list.h"

#include "init/init.h"  // replace by envHelper

BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS)
{
	t_variable	**env;

	env = &get_shell_env()->variables;

	if (argc == 3)
	{
		builtin_setenv_as(env, 3, (char *[]){argv[0], argv[1], argv[2], NULL});
	}
	else
	{
		ft_printf("Usage: setenv <key> <value>\n");
	}
	return (STATUS_SUCCESS);
}

BUILTIN_RET 		builtin_setenv_as(t_variable **env, BUILTIN_ARGS)
{
	if (argc == 3 && ft_strlen(argv[1]) > 0)
	{
		if (check_if_variable_exist(*env, argv[1]))
		{
			builtin_unsetenv_as(env, 2,(char *[]){argv[0], argv[1], NULL});
		}
		list_push_back((t_abstract_list**)&env,
			(t_abstract_list*)create_variable(argv[1], argv[2], true));
	}
	return (STATUS_SUCCESS);
}
