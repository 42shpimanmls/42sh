#include "shell_env.h"

static void	init_variables_list(t_shell_env	*shell_env)
{
	extern char **environ;
	ft_puttab(environ);
	(void)shell_env;
}

void	init()
{
	t_shell_env		*shell_env;

	shell_env = get_shell_env();
	ft_bzero(shell_env, sizeof(shell_env));
	init_variables_list(shell_env);
	//init_history(shell_env);
	//READ HISTORY
}
