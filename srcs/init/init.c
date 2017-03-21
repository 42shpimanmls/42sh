#include "shell_env.h"
#include "init/init.h"
// #include "execution/builtins/builtins.h"  //remove
#include "abstract_list.h"
#include "history.h"

static void	init_variables_list(t_shell_env	*shell_env)
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

	shell_env = get_shell_env();
	ft_bzero(shell_env, sizeof(t_shell_env));
	parse_options(ac, av, shell_env);
	init_variables_list(shell_env);

	load_history(shell_env, HISTFILE);

	// ////////////TEST SETENV UNSETENV /////////////
	// ft_printf("Before env---------\n");
	// print_variable(shell_env->variables);
	// ft_printf("-------------------\n");

	// char* argv[] = {"PROGNAME", "TEST", "testvar", NULL};
	// builtin_setenv(ft_tablen(argv), argv);

	// char* argv2[] = {"PROGNAME", "PATH", NULL};
	// builtin_unsetenv(ft_tablen(argv), argv2);

	// ft_printf("After env---------\n");
	// print_variable(shell_env->variables);
	// ft_printf("-------------------\n");
	// ////////////     ///////////     /////////////

	//init_history(shell_env);
	//READ HISTORY
	shell_env->should_run = true;
}
