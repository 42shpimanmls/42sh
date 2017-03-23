#ifndef VARIABLE_H
# define VARIABLE_H

# include <stdbool.h>

char					*get_variable(char *var);
void					display_variables(void);

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	bool				exported;
}						t_variable;

t_variable				*create_variable(char *name, char *value
															, bool exported);

#endif
