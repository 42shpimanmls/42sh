# include "builtin_def.h"
# include <libft.h>
# include <signal.h>
# include "shell_env.h"
# include "abstract_list.h"
# include "init/init.h"

# define FORBIDDEN_CHAR	"Is forbidden to use the character '='\n"
# define USAGE 			"Usage: setenv <key> <value>\n"

BUILTIN_RET		builtin_setenv(BUILTIN_ARGS)
{
	t_variable	**env;

	env = &get_shell_env()->variables;

	if (argc == 3)
	{
		if (ft_strchr(argv[2], '='))
		{
			ft_dprintf(STDERR_FILENO, FORBIDDEN_CHAR);
			return (STATUS_FAILURE);
		}
		if (setenv_as(env, argv[1], argv[2]) == STATUS_SUCCESS)
			return (STATUS_SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_FAILURE);
}

int			setenv_as(t_variable **env, char *name, char*value)
{
	if (env && ft_strlen(name) > 0)
	{
		if (variable_exist(*env, name))
		{
			if (variable_is_overwritable(*env, name))
				unsetenv_as(env, name);
			else
				return (STATUS_SUCCESS);
		}
		list_push_back((t_abstract_list**)&env,
			(t_abstract_list*)create_variable(name, value, true, true));
		return (STATUS_SUCCESS);
	}
	return (STATUS_FAILURE);
}
