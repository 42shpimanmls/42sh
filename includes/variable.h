#ifndef VARIABLE_H
# define VARIABLE_H

# include <stdbool.h>

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	bool				exported;
}						t_variable;

#endif
