#include <libft.h>
#include "shell_env.h"

char	*get_variable(char *var)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env)
	{
		if (ft_strcmp(env->name, var) == 0)
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	display_variables(void)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env->next != NULL)
	{
		if (env->exported == 1)
			ft_printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
}
