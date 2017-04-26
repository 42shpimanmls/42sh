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

char		**strlist_to_strarray(t_strlist const *list)
{
	char		**result;
	char		**it;
	size_t		array_size;

	array_size = list_count((t_abstract_list const*)list);
	result = memalloc_or_die(sizeof(char*) * (array_size + 1));
	it = result;
	while (list != NULL)
	{
		*it = ft_strdup(list->str);
		it++;
		list = list->next;
	}
	result[array_size] = NULL;
	return (result);
}

void		strlist_delete(t_strlist **strlist_addr)
{
	t_strlist	*it;
	t_strlist	*next;

	it = *strlist_addr;
	while (it != NULL)
	{
		next = it->next;
		free(it->str);
		free(it);
		it = next;
	}
	*strlist_addr = NULL;
}

void		strlist_append(t_strlist **strlist_addr, char const *str)
{
	t_strlist	*it;
	t_strlist	*new_elem;

	new_elem = strlist_construct(str);
	if (*strlist_addr == NULL)
	{
		*strlist_addr = new_elem;
		return ;
	}
	it = *strlist_addr;
	while (it->next != NULL)
		it = it->next;
	it->next = new_elem;
}
