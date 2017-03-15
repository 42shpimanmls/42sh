#include "builtin_def.h"
#include <libft.h>
#include "shell_env.h"
#include "abstract_list.h"

#include "init/init.h"  // replace by envHelper

BUILTIN_RET 		builtin_setenv(BUILTIN_ARGS)
{
	t_variable	**env;

	env = &get_shell_env()->variables;

	if (argc == 0)
	{
		print_variable(*env);
	}
	else if (argc == 2)
	{
		if (ft_strlen(argv[0]) > 0)
		{
			if (check_if_variable_exist(*env, argv[0]))
			{
				builtin_unsetenv(1, (char *[]){argv[0], NULL});
			}
			list_push_back((t_abstract_list**)env, 
				(t_abstract_list*)create_variable(argv[0], argv[1], true));
		}
	}
	else
	{
		ft_printf("Usage: setenv <key> <value>\n");
	}
}
