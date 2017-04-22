#include "shell_env.h"
#include "init.h"

static void	set_shlvl(void)
{
	char	*tmp;
	int 	shlvl;

	tmp = get_variable("SHLVL");
	shlvl = ft_atoi(tmp);
	ft_strdel(&tmp);
	tmp = ft_itoa(shlvl + 1);
	set_variable("SHLVL", tmp, false);
	ft_strdel(&tmp);
}

void		set_default_variables(void)
{
	char	*tmp;

	tmp = ft_itoa(getpid());
	set_variable("$", tmp, false);
	ft_strdel(&tmp);
	set_variable("?", "0", false);
	set_variable("SHELL", SHNAME, false);
	set_shlvl();
	set_variable("PWD", getcwd(NULL, 0), false);
}
