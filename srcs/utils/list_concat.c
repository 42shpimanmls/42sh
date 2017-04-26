#include "abstract_list.h"

void	list_concat(t_abstract_list **dst, t_abstract_list *src)
{
	while (*dst != NULL)
		dst = &(*dst)->next;
	*dst = src;
}
