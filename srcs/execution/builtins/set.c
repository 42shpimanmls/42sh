# include "builtin_def.h"
# include <libft.h>
# include <signal.h>
# include "shell_env.h"
# include "abstract_list.h"
# include "init/init.h"

# define FORBIDDEN_CHAR	"Is forbidden to use the character '='\n"
# define USAGE 			"Usage: set <key> <value>\n"

BUILTIN_RET		builtin_set(BUILTIN_ARGS)
{
	t_variable	**env;

	env = &get_shell_env()->variables;
	if (argc == 1)
	{
		display_variables(false);
	}
	else if (argc == 3)
	{
		if (ft_strchr(argv[2], '='))
		{
			ft_dprintf(STDERR_FILENO, FORBIDDEN_CHAR);
			return (STATUS_FAILURE);
		}
		if (setenv_as(env, argv[1], argv[2], false) == STATUS_SUCCESS)
			return (STATUS_SUCCESS);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_FAILURE);
}

