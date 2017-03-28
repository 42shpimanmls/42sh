#ifndef VARIABLE_H
# define VARIABLE_H

# include <stdbool.h>

char					*get_variable(char *var);
void					set_variable(char const *var, char const *val);
void					display_variables(void);
char					**get_variables_for_execution(void);

typedef struct			s_variable
{
	struct s_variable	*next;
	char				*name;
	char				*value;
	bool				exported;
}						t_variable;

t_variable				*create_variable(char *name, char *value
															, bool exported);
void					delete_variable(t_variable **var);
void					delete_all_variables(t_variable **var);

#endif
