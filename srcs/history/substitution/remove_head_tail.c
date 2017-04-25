#include "history_substitutions.h"

/*
**	removes *str's trailing pathname component
**	i.e. what is after last slash
*/

void	remove_tail(char **str, char c)
{
	size_t	i;
	char	*tmp;

	i = ft_strlen(*str);
	while (i > 0 && (*str)[i] != c)
		i--;
	if (i > 0)
	{
		tmp = ft_strsub(*str, 0, i);
		ft_strdel(str);
		*str = ft_strdup(tmp);
		ft_strdel(&tmp);
	}
}

/*
**	removes *str's head
**	i.e. what is before last slash
*/

void	remove_head(char **str, char c)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while ((tmp = ft_strchr(*str, c)))
	{
		i = tmp - *str;
		if (str[i])
		{
			tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i);
			ft_strdel(str);
			*str = ft_strdup(tmp);
			ft_strdel(&tmp);
		}
	}
}
