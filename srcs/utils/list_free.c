#include "abstract_list.h"

void	list_free(t_abstract_list **list)
{
	if ((*list) && (*list)->next)
		list_free(&(*list)->next);
	free(*list);
	*list = NULL;
}
