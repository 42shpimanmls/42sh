#include "strlist.h"
#include <libft.h>
#include "abstract_list.h"

char		*strlist_to_str(t_strlist const *list)
{
	char	*result;

	result = NULL;
	while (list != NULL)
	{
		result = ft_strjoinf(result, list->str, 1);
		list = list->next;
	}
	return (result);
}

char		*strlist_to_str_until(t_strlist const *list
														, t_strlist const *end)
{
	char	*result;

	result = NULL;
	while (list != NULL && list->next != end)
	{
		result = ft_strjoinf(result, list->str, 1);
		list = list->next;
	}
	return (result);
}

t_strlist	*strlist_construct(char const *str)
{
	t_strlist	*result;

	result = memalloc_or_die(sizeof(t_strlist));
	result->str = ft_strdup(str);
	result->next = NULL;
	return (result);
}
