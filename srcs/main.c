#include <global.h>
#include <init.h>

int main(int ac, char **av, char **env)
{
	t_global	*global;

	(void)ac;
	(void)av;
	global = ft_init(env);
	ft_puttab(global->env);
	//READ HISTORY
	return (EXIT_SUCCESS);
}
