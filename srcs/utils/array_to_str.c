#include <libft.h>
#include "utils.h"

char	*array_to_str(char **array)
{
	char	*str;
	char	*tmp;
	size_t	i;

	i = 0;
	str = NULL;
	if (array)
	{
		while (array[i])
		{
			if (str)
			{
				tmp = ft_strdup(str);
				ft_strdel(&str);
				str_add_space(&tmp);
			}
			else
				tmp = ft_strnew(1);
			str = ft_strjoin(tmp, array[i]);
			ft_strdel(&tmp);
			i++;
		}
		return (str);
	}
	else
		return (NULL);
}