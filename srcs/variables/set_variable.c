#include <libft.h>
#include "shell_env.h"

void			set_variable(char const *var, char const *val, bool overwrite)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env != NULL)
	{
		if (ft_strcmp(env->name, var) == 0)
		{
			free(env->value);
			env->value = ft_strdup(val);
			return ;
		}
		if (env->next == NULL)
			break ;
		env = env->next;
	}
	env->next = create_variable(var, val, false, overwrite);
}
