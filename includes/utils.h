#ifndef UTILS_H
#define UTILS_H

# include <stdlib.h>

void						print_non_ascii_str(char const *str);
void						print_non_ascii_char(char c);
void						event_callback_test(void);
void						*memalloc_or_die(size_t size);

/*struct s_abstract_list
{
	struct s_abstract_list	*next;
}

struct s_abstract_list
{
	struct s_abstract_list	*next;
	struct s_abstract_list	*prev;
}


size_t count_list(s_abstract_list *it);*/

#endif
