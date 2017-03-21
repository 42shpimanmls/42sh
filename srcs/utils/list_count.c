#include "abstract_list.h"

size_t	list_count(t_abstract_list *list)
{
	size_t	n;

	n = 0;
	while (list)
	{
		n++;
		list = list->next;
	}
	return (n);
}
