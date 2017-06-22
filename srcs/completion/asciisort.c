#include "completion.h"

t_strlist  **getmin(t_strlist **lst)
{
	t_strlist **ret;

	ret = lst;
	while (*lst)
	{
		if (ft_strcmp((*ret)->str, (*lst)->str) > 0)
			ret = lst;
		lst = &(*lst)->next;
	}
	return (ret);
}

void    asciisort(t_strlist **lst)
{
	char		*tmp;
	t_strlist	**min;

	while (*lst)
	{
		min = getmin(lst);
		tmp = (*lst)->str;
		(*lst)->str = (*min)->str;
		(*min)->str = tmp;
		lst = &(*lst)->next;
	}
}
