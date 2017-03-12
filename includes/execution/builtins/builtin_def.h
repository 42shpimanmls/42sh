#ifndef BUILTIN_DEF_H
# define BUILTIN_DEF_H

# include "bool.h"
# include "event_callbacks.h"

typedef enum				e_builtin_id
{
	EXIT_BUID = 0
}							t_builtin_id;

typedef struct				s_builtin_def
{
	t_builtin_id const			id;
	char const *const			name;
	t_builtin const				builtin;
}							t_builtin_def;

# define BUILTIN_DEF_COUNT 1

t_builtin_def const			*get_builtin_defs(void);
t_builtin_def const			*get_matching_builtin(char const *str);

void								print_builtin_def(
	t_builtin_def const *def);
void								print_builtin_defs(void);



#endif
