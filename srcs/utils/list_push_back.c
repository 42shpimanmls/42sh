#include "abstract_list.h"
# include <libft.h> //remove

void list_push_back(t_abstract_list **list, t_abstract_list *new)
{
	t_abstract_list *tmp;

	if (*list == NULL)
		*list = new;
	else
	{
		tmp = *list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void list_push_at_pos(size_t pos, t_abstract_list **list, t_abstract_list *new)
{
	(void)pos;
	t_abstract_list	*lst;
	// t_abstract_list	**addr;
	size_t			i;

	if (*list == NULL)
		*list = new;
	else
	{
		lst = *list;
		if (pos == 0)
		{
			// insert at first position !!!!!!!!!!!!!!!!!!!!!!!!!!
			// new->next = *list;
			// *list = new;
		}
		else if (pos == 1)
		{
			new->next = *list;
			*list = new;
		}
		else if (pos > 1)
		{
			i = 3;
			while (lst->next && i <= pos)
			{
				i++;
				lst = lst->next;
			}
			new->next = lst->next;
			lst->next = new;
		}
	}
}

void list_pop_at_pos(size_t pos, t_abstract_list **list)
{
	t_abstract_list	*lst;
	t_abstract_list	**addr;
	size_t		i;

	lst = *list;
	addr = list;
	i = 0;
	while (lst)
	{
		if (i == pos)
		{
			*addr = lst->next;
			return ;
		}
		addr = &(*addr)->next;
		lst = *addr;
		i++;
	}
}
