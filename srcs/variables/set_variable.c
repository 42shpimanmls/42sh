#include <libft.h>
#include "shell_env.h"

void			set_variable(char const *var, char const *val)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env->next != NULL)
	{
		if (ft_strcmp(env->name, var) == 0)
		{
			free(env->value);
			env->value = ft_strdup(val);
			break ;
		}
		env = env->next;
	}
}
