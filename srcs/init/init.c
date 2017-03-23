#include "shell_env.h"
#include "init/init.h"
#include "read_input/editor/editor.h"
#include "abstract_list.h"
#include "history/history.h"
#include "errors.h"

static void	init_variables_list(t_shell_env *shell_env)
{
	extern char	**environ;
	char		**line;
	t_variable	*var;
	size_t		i;

	i = -1;
	while (environ[++i])
	{
		line = ft_strsplit(environ[i], '=');
		if (line && ft_tablen(line) == 2 &&
			ft_strlen(line[0]) > 0 && ft_strlen(line[1]) > 0)
		{
			var = create_variable(line[0], line[1], true);
			list_push_back((t_abstract_list**)&shell_env->variables\
				, (t_abstract_list*)var);
		}
		ft_freetabchar(line);
	}
}

void	init(int ac, char **av)
{
	t_shell_env		*shell_env;

	set_error(NO_ERROR);
	shell_env = get_shell_env();
	ft_bzero(shell_env, sizeof(t_shell_env));
	init_variables_list(shell_env);
	parse_options(ac, av, shell_env);
	load_history(shell_env, HISTFILE, 0);
	shell_env->should_run = true;
}
