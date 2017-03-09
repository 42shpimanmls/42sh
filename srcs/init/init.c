#include <global.h>

t_global	*ft_init(char **env)
{
	t_global	*global;

	global = (t_global *)malloc(sizeof(t_global));
	ft_bzero(global, sizeof(t_global));
	
	global->env = ft_tabdup(env);
	return (global);
}
