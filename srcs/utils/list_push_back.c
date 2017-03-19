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

void list_push_back_at_pos(size_t pos, t_abstract_list **list, t_abstract_list *new)
{
	(void)pos;
	t_abstract_list	*lst;
	// t_abstract_list	**addr;
	size_t			i;

	ft_dprintf(2, "pos   : %d\n", pos);
	ft_dprintf(2, "---------------------------------\n");


	if (*list == NULL)
		*list = new;
	else
	{
		// lst = *list;
		// addr = list;
		if (pos == 0)
		{
			// addr = &(*addr)->next;
			// lst = new;
			// // lst = lst->next;
		}
		else if (pos == 1)
		{
			new->next = *list;
			*list = new;
		}
		else if (pos > 1)
		{
			i = 3;
			lst = *list;
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

void list_pop_back_at_pos(size_t pos, t_abstract_list **list)
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
