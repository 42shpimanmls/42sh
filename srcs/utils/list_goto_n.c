#include "abstract_list.h"
#include <stdbool.h>

bool		list_goto_n(t_abstract_list **list, t_uint n)
{
	while ((*list) && n > 0)
	{
		(*list) = (*list)->next;
		n--;
	}
	if (!(*list))
		return (false);
	return (true);
}
