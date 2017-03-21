#include "abstract_list.h"

void	list_push_back(t_abstract_list **list, t_abstract_list *new)
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
