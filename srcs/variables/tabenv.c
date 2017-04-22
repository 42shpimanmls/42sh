#include "libft.h"
#include "tabenv.h"

/*
** Browse env var
*/

char	*get_tenv(char **env, char *var)
{
	int	i;

	i = -1;
	if (env != NULL)
		while (env[++i] != NULL)
			if (ft_strcmp(env[i], var) == 61)
				return (ft_strchr(env[i], '=') + 1);
	return (NULL);
}
