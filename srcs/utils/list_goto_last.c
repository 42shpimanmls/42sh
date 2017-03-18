#include "abstract_list.h"

t_abstract_list const	*list_get_last_const(t_abstract_list const *list)
{
	while (list && list->next)
		list = list->next;
	return (list);
}
