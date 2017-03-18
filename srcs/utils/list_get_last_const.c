#include "abstract_list.h"

void	list_goto_last(t_abstract_list **list)
{
	while ((*list) && (*list)->next)
		(*list) = (*list)->next;
}
