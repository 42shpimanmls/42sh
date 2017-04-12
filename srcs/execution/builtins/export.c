# include "builtin_def.h"
# include <libft.h>
# include <signal.h>
# include "shell_env.h"
# include "abstract_list.h"
# include "init/init.h"
# include "utils.h"

# define USAGE	"Usage: export [-p] name[=word]...\n"

void 			export_classic(t_variable **env, char **argv, char *opt)
{
	char	**tab;
	size_t	i;

	i = 0;
	while (argv[++i])
	{
		if (!is_an_argument(argv[i]) && ft_strchr(argv[i], '='))
		{
			tab = ft_strsplit(argv[i], '=');
			if (ft_tablen(tab) >= 1)
			{
				setenv_as(env, tab[0], tab[1], true);
				if (ft_strchr(opt, 'p'))
					ft_dprintf(STDOUT_FILENO, "export %s=%s\n", tab[0], tab[1]);
			}
			ft_freetabchar(tab);
		}
		else
		{
			set_variable_for_export(*env, argv[i]);
			if (ft_strchr(opt, 'p'))
				ft_dprintf(STDOUT_FILENO, "export %s\n", argv[i]);
		}
	}
}

BUILTIN_RET		builtin_export(BUILTIN_ARGS)
{
	t_variable	**env;
	char		*opt;

	env = &get_shell_env()->variables;
	opt = get_options_core(argc, argv);

	if (argc == 1)
	{
		display_variables(true);
	}
	else if (argc >= 2)
	{
		export_classic(env, argv, opt);
	}
	else
	{
		ft_dprintf(STDERR_FILENO, USAGE);
	}
	return (STATUS_SUCCESS);
}

