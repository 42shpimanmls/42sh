#ifndef ABSTRACT_LIST_H
#define ABSTRACT_LIST_H

#include <stdlib.h>

typedef struct	s_abstract_list
{
	struct s_abstract_list	*next;
}				t_abstract_list;

size_t list_count(t_abstract_list *list);
void	list_push_back(t_abstract_list **list_addr, t_abstract_list *elem);
void	list_goto_last(t_abstract_list **list);

#endif
