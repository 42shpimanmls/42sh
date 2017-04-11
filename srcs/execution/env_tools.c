#include "libft.h"
#include "shell_env.h"
#include "env_tools.h"

char	**tabify(t_variable *env)
{
	int	i;
	int	len;
	char	**tenv;

	len = lstsize(env);
	tenv = (char**)memalloc_or_die(sizeof(char*) * (len + 1));
	i = -1;
	while (++i < len)
	{
		tenv[i] = ft_strjoinf(env->name, ft_strjoin("=", env->value), 2);
		env = env->next;
	}
	tenv[i] = NULL;
	return (tenv);
}

int	lstsize(t_variable *env)
{
	int	i;

	i = 1;
	while (1)
	{
		i++;
		env = env->next; 
		if (env->next == NULL)
			break ;
	}
	return (i);
}


/*
** Browse env var
*/

char    *get_tenv(char **env, char *var)
{
	int     i;

	i = -1;
	while (env[++i] != NULL)
		if (ft_strcmp(env[i], var) == 61)
			return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}
