#include <libft.h>

void	str_add_space(char **str)
{
	char	*tmp;

	tmp = ft_strjoin(*str, " ");
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
}

void	str_join_with_space(char **str, char *to_join)
{
	char	*tmp;

	str_add_space(str);
	tmp = ft_strjoin(*str, to_join);
	ft_strdel(str);
	*str = ft_strdup(tmp);
	ft_strdel(&tmp);
}
