#include <libft.h>
#include "shell_env.h"
#include "abstract_list.h"

char	*get_variable(char *var)
{
	t_variable	*env;

	env = get_shell_env()->variables;
	while (env->next != NULL)
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

static size_t	get_number_of_exported()
{
	t_variable	*e;
	size_t		size;

	e = get_shell_env()->variables;
	size = 0;
	while (e->next)
	{
		if (e->exported == true)
			size++;
		e = e->next;
	}
	return (size);
}

static size_t	add_to_tab(t_variable *e, char **envp, size_t i)
{
	if (!e || !envp)
		return (i);
	while (e->next)
	{
		if (e->exported == true)
		{
			envp[i] = ft_strjoinf(e->name, ft_strjoin("=", e->value), 2);
			i++;
			envp[i] = NULL;
		}
		e = e->next;
	}
	return (i);
}

char	**get_variables_for_execution(t_variable *assignments)
{
	t_variable	*e;
	char		**envp;
	size_t		size;
	size_t		i;

	size = get_number_of_exported();
	if (assignments)
		size += list_count((t_abstract_list *)assignments);
	if (!size)
		return (NULL);
	e = get_shell_env()->variables;
	envp = memalloc_or_die(sizeof(char *) * (size + 1));
	i = 0;
	i = add_to_tab(e, envp, i);
	i = add_to_tab(assignments, envp, i);
	return (envp);
}
