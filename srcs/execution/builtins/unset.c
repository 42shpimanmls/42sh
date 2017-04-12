# include "builtin_def.h"
# include <libft.h>
# include "shell_env.h"
# include "init/init.h"
# include "utils.h"

# define USAGE 			"Usage: unset [-fv] name...\n"

// -v check no delete on overwrite, is a variable
// -f check if a fonction and delete
// nothing delete.

int				unset_as(t_variable **env, char *name)
{
	if (env && ft_strlen(name) > 0)
	{
		if (pop_variable_by_name(env, name) == STATUS_SUCCESS)
		{
			return (STATUS_SUCCESS);
		}
	}
	return (STATUS_FAILURE);
}

BUILTIN_RET		builtin_unset(BUILTIN_ARGS)
{
	t_variable	**env;
	char		*opt;
	size_t		i;

	env = &get_shell_env()->variables;
	opt = get_options_core(argc, argv);

	if (argc > 1)
	{
		if (ft_strchr(opt, 'v'))
		{

		}
		else if (ft_strchr(opt, 'f'))
		{

		}
		else
		{
			i = 0;
			while (argv[++i])
			{
				unset_as(env, argv[i]);
			}
		}
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	free(opt);
	return (STATUS_SUCCESS);
}
