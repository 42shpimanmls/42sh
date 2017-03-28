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

char					*get_variable(char *var);
void					set_variable(char const *var, char const *val);
// void					set_variable_as(t_variable *env, char const *var, char const *val);
void					display_variables(void);
char					**get_variables_for_execution(t_variable *assignments);

t_variable				*create_variable(char *name, char *value
															, bool exported);
void					delete_variable(t_variable **var);
void					delete_all_variables(t_variable **var);

#endif
